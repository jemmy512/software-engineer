#include <iostream>


/*
* version 1.0
* Batch is spliced into DataWarehouse & Database two levels
*/
template<typename DataWarehouse, typename DatabaseBatch>
class DataWarehouseBatch {
public:
    using DataWarehousePtr = std::shared_ptr<DataWarehouse>
    using DatabaseBatchPtr = std::shared_ptr<DatabaseBatch>
    using DataWarehouseBatchPtr = DataWarehouse<DataWarehouse, DatabaseBatch>;

    using DWOperation = std::functions<void(const IDataWarehousePtr&, const DatabaseBatchPtr&)>;
    using DWOperations = std::vector<DWOperation>

public:
    DataWarehouseBatch(std::string name, const DataWarehousePtr& dataWarehouse) { }

    void enqueue(const DWOperation& operation) {
        mOperation.emplace_back(operation);
    }

    ~DataWarehouseBatch() {
        mDataWarehouse->storeBatchAsync(mName, mOperations);
    }


    static void doBatch(const DataWarehouseBatchPtr& batch, const DataWarehousePtr& dataWarehouse, const DWOperation& operation) {
        if (operation) {
            if (batch) {
                batch->enqueue(operation);
            } else if (DataWarehouse) {
                operation(dataWarehouse, nullptr);
            }
        }
    }

private:
    std::string mName;
    DataWarehousePtr mDataWarehouse;
    DWOperations mOperations;
};

void IDBWarehouse::storeBatchAsync(std::string name, const PersistOperations& operations) {
    if (!operations.empty()) {
        ScopedBatch batch(name, mUseDB);

        for (auto op : operations) {
            op(shared_from_this(), batch.mBatch);
        }
    }
}

class ScopedBatch {
public:
    ScopedBatch(std::string name, const IDBWrapperPtr& db) {
        mBatch = std::make_shared<DatabaseBatch>(name, db);
    }

    ~ScopedBatch() {
        mBatch->apply();
        mBatch = nullptr;
    }

private:
    DatabaseBatchPtr mBatch;
}

struct ScoedTransaction {
public:
    ScopedTransaction(const std::string name, const DBWrapper* dbWrapper, bool doTransaction)
    :   mName(name),
        mDBWrapper(dbWrapper),
        mDoTransaction(doTransaction),
        mMutex()
    {
        if (mDoTransaction) {
            mMutext.lock();
            mDBWrapper->startTransation();
        }
    }

    ~ScopedTransaction() {
        if (mDoTransaction) {
            if (mIsSuccess) {
                mDBWrapper->commitTransaction();
            } else {
                mDBWrapper->rollbackTransaction();
            }

            mMutex.unlock();
        }
    }

private:
    std::string mName;
    DBWrapper* mDBWrapper;
    bool mDoTransaction;
    bool mIsSuccess;
    std::mutex mMutex;
};

template<typename DBWrapper>
class DatabaseBatch {
public:
    using DBOperation = std::function<void(const IDBWrapperPtr&, bool doTransaction)>;
    using DBOperations = std::vector<DBOperation>

public:
    DatabaseBatch(std::string name, const IDBWrapperPtr &dbWrapper) {

    }

    void enqueue(const DBOperation& operation) {
        mDBOperatios.push_back(operation);
    }

    DBOperations getOperations() {
        std::move(mOperations());
    }

    ~DatabaseBatch() {
        if (mDBWrapper) {
            mDBWrappe->creatDatabaseTask(
                "DatabaseBatch: " + mName,
                [name = mName, mDBWrapper, operations = getOperations()]() {
                    ScoptedTransaction transaction(mDBWrapper->get(), mName, true);

                    for (const auto& op : operations) {
                        if (!op(mDBWrapper, false)) {
                            return;
                        }
                    }

                    transactiosn.setSuccess();
                }
            );
        }
    }

    static void doBatch(const DatabaseBatchPtr& batch, const DBWrapperPtr& database, const DBOperations& operation) {
        if (operation) {
            if (batch) {
                batch->enqueue(operation);
            } else if (database) {
                database->createDatabaseTask("DatabaseBatch", [database, operation]() {
                    operation(database, true);
                });
            }
        }
    }

private:
    std::string mName;
    IDBWrapperPtr mDBWrapper;
    DBOperations mDBOperations;
};


// useage
void ConversationModel::saveConversationMessages() {
    const auto batch = std::make_shared<DataWarehouseBatch>(...);

    DataWarehouse::doBatch(batch, dataWarehouse, [messages](const IDBWarehousePtr& dataWarehouse, const DatabaseBatchPtr& batch) {
        dataWarehouse->storeMessages(messages, batch);
    });
}

void DataWarehouse::storeMessages(const Messages& messages, const DatabaseBatch& batch) {
    DatabaseBatch::doBatch(batch, mUserDB, [messages](const IDBWrapperPtr& database, bool doTransaction) {
        database->insertIntoDatabase(tableName, columns, argements, doTransaction);
    });
}