#include <iostream>
#include <mysqlx/xdevapi.h>

using std::cout;
using std::endl;
using namespace ::mysqlx;

int main() {
    try {
        // Connect to MySQL server using X DevAPI (X Protocol, port 33060)
        Session sess("mysqlx://root:12345678@localhost");

        // Create or use a schema
        sess.sql("DROP SCHEMA IF EXISTS test").execute();
        sess.sql("CREATE SCHEMA test").execute();
        Schema db = sess.getSchema("test", true);

        cout << "\n--- Relational Table Operations ---" << endl;

        // Create a table
        sess.sql("CREATE TABLE test.employees_table ("
            "id INT PRIMARY KEY AUTO_INCREMENT, "
            "name VARCHAR(50), "
            "department VARCHAR(50))").execute();

        // Insert data using SQL
        sess.sql("INSERT INTO test.employees_table (name, department) "
            "VALUES ('Alice Brown', 'HR')").execute();

        // Query table using X DevAPI
        RowResult rows = sess.sql("SELECT id, name, department FROM test.employees_table "
            "WHERE department = ?")
            .bind("HR")
            .execute();

        cout << "\nEmployees in HR (from table):" << endl;
        while (Row row = rows.fetchOne()) {
            cout << "ID: " << row[0].get<int>()
                 << ", Name: " << row[1].get<string>()
                 << ", Dept: " << row[2].get<string>() << endl;
        }

        cout << "\n--- Document Store (NoSQL) Operations ---" << endl;

        // Create a collection
        Collection coll = db.createCollection("employees");

        // Add JSON documents
        coll.add(R"({"name": "John Doe", "department": "Engineering", "age": 30})").execute();
        coll.add(R"({"name": "Jane Smith", "department": "Marketing", "age": 28})").execute();
        cout << "Added 2 documents to employees collection." << endl;

        // Read documents
        DocResult docs = coll.find("department = :dept")
            .bind("dept", "Engineering")
            .execute();
        cout << "\nEmployees in Engineering:" << endl;
        while (DbDoc doc = docs.fetchOne()) {
            cout << "Name: " << doc["name"].get<string>()
                 << ", Age: " << doc["age"].get<int>() << endl;
        }

        // Update a document
        coll.modify("name = :name")
            .set("age", 31)
            .bind("name", "John Doe")
            .execute();
        cout << "\nUpdated John Doe's age." << endl;

        // Delete a document
        coll.remove("name = :name")
            .bind("name", "Jane Smith")
            .execute();
        cout << "Removed Jane Smith from collection." << endl;

        // Verify remaining documents
        docs = coll.find().execute();
        cout << "\nRemaining documents:" << endl;
        while (DbDoc doc = docs.fetchOne()) {
            cout << "Name: " << doc["name"].get<string>()
                 << ", Dept: " << doc["department"].get<string>() << endl;
        }

        // Clean up schema
        sess.sql("DROP SCHEMA test").execute();
        cout << "\nCleaned up schema." << endl;
    } catch (const mysqlx::Error &e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "Demo completed successfully." << endl;
    return 0;
}

// g++ -o xapi mysql-xapi.cc -I/usr/local/mysql-connector-c++-9.0.0/include/ -L/usr/local/mysql-connector-c++-9.0.0/lib64/ -lmysqlcppconn8.2 -Wl,-rpath,/usr/local/mysql-connector-c++-9.0.0/lib64/