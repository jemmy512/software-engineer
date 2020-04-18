#include <iostream>
#include <variant>
#include <vector>

struct Column {
    using Columns = std::vector<Column>;
    Column(std::string name, std::string attr) : mName(name), mAttributes(attr) {}

    std::string mName;
    std::string mAttributes;
};

class Schema {
public:
    Schema(const std::string tableName, const Column::Columns& columns)
    :   mTableName(tableName), mColumns(columns)
    { }

    Schema(const std::string& tableName, Column::Columns&& columns)
    :   mTableName(tableName) {
        mColumns.swap(columns); // no move, copy, costrutor is called
    }

    std::string getTableSchema() const {

    }

    int fieldId(const std::string& columnName) const {
        size_t id = -1;

        for (; id < mColumns.size() && mColumns[id].mName != columnName; ++id);

        return static_cast<int>(id < mColumns.size() ? id : -1);
    }

    std::string getColumnSchema(const std::string& columnName) const {
        const auto id = fieldId(columnName);
        return mColumns[id].mName + " " + mColumns[id].mAttributes;
    }


private:
    std::string mTableName;
    std::vector<Column> mColumns;
};

class MessageTable : public Schema {
public:
    static constexpr const char* NameField = "Name";
    static constexpr const char* AddressField = "Address";
    static constexpr const char* AgeField = "Age";
    static constexpr const char* GradeField = "Grade";
    static constexpr const char* SexField = "Sex";

public:
    MessageTable() : Schema(
        "Message",
        {
            {"ID", "INT NOT NULL"},
            {NameField, "TEXT"},
            {AddressField, "TEXT"},
            {AgeField, "TEXT"},
            {GradeField, "TEXT"},
            {SexField, "TEXT"}
        }
    )
    { }
};

class DBType {
public:
    using String = std::string;
    using Int = int;
    using Float = float;
    using Blob = std::vector<char>;
    using TypeVariant = std::variant<String, Int, Float, Blob>;
    using QuryReult = DBType*;
    using DBTypes = std::vector<DBType>;

public:
    DBType(const String& val) : mData(val) {}
    DBType(const Int& val) : mData(val) {}
    DBType(const Blob& val) : mData(val) {}
    DBType(const Float& val) : mData(val) {}

    DBType& operator=(const DBType& other) {
        if (&other == this) {
            return *this;
        }

        const_cast<TypeVariant&>(mData) =  other.mData;
        return *this;
    }

    template<typename T>
    const T& getValue() const {
        if (const auto data = std::get_if<T>(&mData)) {
            return *data;
        }

        static T dummy{};
        return dummy;
    }

    template<typename T>
    bool holdsType() const {
        return std::holds_alternative<T>(mData);
    }

    bool operator<(const DBType& rhs) const {
        if (holdsType<Int>()) {
            return *std::get_if<Int>(&mData) < *std::get_if<Int>(&rhs.mData);
        } else if (holdsType<Float>()) {
            return *std::get_if<Float>(&mData) < *std::get_if<Int>(&rhs.mData);
        } else if (holdsType<String>()) {
            return *std::get_if<String>(&mData) < *std::get_if<String>(&rhs.mData);
        }

        return false;
    }

    bool operator<=(const DBType& rhs) const {
        if (holdsType<Int>()) {
            return *std::get_if<Int>(&mData) <= *std::get_if<Int>(&rhs.mData);
        } else if (holdsType<Float>()) {
            return *std::get_if<Float>(&mData) <= *std::get_if<Int>(&rhs.mData);
        } else if (holdsType<String>()) {
            return *std::get_if<String>(&mData) <= *std::get_if<String>(&rhs.mData);
        }

        return false;
    }

    bool operator>(const DBType& rhs) const {
        return !(operator<(rhs) || operator==(rhs));
    }

    bool operator>=(const DBType& rhs) const {
        return !operator<(rhs);
    }

    bool operator==(const DBType& rhs) const {
        if (holdsType<Int>()) {
            return *std::get_if<Int>(&mData) == *std::get_if<Int>(&rhs.mData);
        } else if (holdsType<Float>()) {
            return *std::get_if<Float>(&mData) == *std::get_if<Int>(&rhs.mData);
        } else if (holdsType<String>()) {
            return *std::get_if<String>(&mData) == *std::get_if<String>(&rhs.mData);
        }

        return false;
    }

    bool operator!=(const DBType& rhs) const {
        return !operator==(rhs);
    }

private:
    const TypeVariant mData;
};

using QueryResult = DBType*;
class QueryResults {
public:
    class Iterator {
    public:
        Iterator(QueryResults& results, size_t offset)
        :  mResults(results), mOffset(offset)
        { }

        Iterator& operator++() {
            mOffset += mResults.mColumnNames.size();
            return *this;
        }

        QueryResult operator*() const {
            return &mResults.mResults[mOffset];
        }

        bool operator==(const Iterator& rhs) const {
            auto left = mResults.empty() ? nullptr : &mResults.mResults[0];
            auto right = rhs.mResults.empty() ? nullptr : &rhs.mResults.mResults[0];

            return left == right && mOffset == rhs.mOffset;
        }

        bool operator!=(const Iterator& rhs) const {
            return !operator==(rhs);
        }

    private:
        size_t mOffset{0};
        QueryResults& mResults;
    };

    QueryResults(const DBType::DBTypes&& results, std::vector<std::string>&& columns)
    :   mResults(results), mColumnNames(columns)
    { }

    bool empty() {
        return mColumnNames.empty() || mResults.empty();
    }

    size_t size() const {
        return mColumnNames.empty() || mResults.empty() ? 0 : mResults.size() / mColumnNames.size();
    }

    int columnSize() const {
        return mColumnNames.size();
    }

    const std::string& columnName(int index) const {
        return mColumnNames[index];
    }

    QueryResult front() {
        return &mResults[0];
    }

    Iterator begin() {
        return {*this, 0};
    }

    Iterator end() {
        return {*this, mResults.size()};
    }

    const DBType& operator[](int index) const {
        return mResults[index];
    }

    int getIndex(const std::string& name) const {
        int index = -1;

        for (auto i = 0; i < mColumnNames.size(); ++i) {
            if (mColumnNames[i] == name) {
                index = i;
                break;
            }
        }

        return index;
    }

    template<typename T>
    const T& getResult(int index) const {
        return mResults[index].getValue<T>();
    }

    template<typename T>
    const T& getResult(const std::string& name) {
        return getResult<T>(getIndex(name));
    }

private:
    int mPosition{0};
    std::vector<DBType> mResults;
    std::vector<std::string> mColumnNames;
};


#define Print(x) std::cout << (x) << std::endl;

int main() {
    std::vector<std::string> columnName{"Name", "Address", "Age", "Grade", "Sex"};
    DBType::DBTypes data{{"Jie"}, {"China"}, {22}, (float){90.5}, {"Man"}};
    QueryResults results{std::move(data), std::move(columnName)};

    auto nameIndex = results.getIndex("Name");
    auto addressIndex = results.getIndex("Address");
    auto ageIndex = results.getIndex("Age");
    auto gradeIndex = results.getIndex("Grade");
    auto sexIndex = results.getIndex("Sex");

    Print(nameIndex);
    Print(addressIndex);
    Print(ageIndex);
    Print(gradeIndex);
    Print(sexIndex);


    // auto name = results.getResult<DBType::String>(nameIndex);
    // auto address = results.getResult<DBType::String>(addressIndex);
    // auto age = results.getResult<DBType::Int>(ageIndex);
    // auto grad = results.getResult<DBType::Float>(gradeIndex);
    // auto sex = results.getResult<DBType::Int>(sexIndex);

    auto name = results.getResult<DBType::String>(MessageTable::NameField);
    auto address = results.getResult<DBType::String>(MessageTable::AddressField);
    auto age = results.getResult<DBType::Int>(MessageTable::AgeField);
    auto grad = results.getResult<DBType::Float>(MessageTable::GradeField);
    auto sex = results.getResult<DBType::Int>(MessageTable::SexField);

    Print(name);
    Print(address);
    Print(grad);
    Print(sex);

}