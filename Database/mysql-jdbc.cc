#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

using namespace std;
using namespace sql;

int main() {
    try {
        // Initialize the MySQL driver
        mysql::MySQL_Driver *driver = mysql::get_mysql_driver_instance();

        // Create a connection
        Connection *con = driver->connect("tcp://localhost:3306", "root", "12345678");

        // Create a statement for setup
        Statement *stmt = con->createStatement();

        // Drop and create the test schema
        stmt->execute("DROP SCHEMA IF EXISTS test");
        stmt->execute("CREATE SCHEMA test");

        con->setSchema("test");

        // Create employees table
        stmt->execute(
            "CREATE TABLE employees ("
            "id INT PRIMARY KEY AUTO_INCREMENT, "
            "name VARCHAR(50) NOT NULL, "
            "department VARCHAR(50), "
            "salary DECIMAL(10,2))"
        );
        delete stmt;

        // --- CREATE: Insert employees ---
        PreparedStatement *pstmt = con->prepareStatement(
            "INSERT INTO employees (name, department, salary) VALUES (?, ?, ?)"
        );
        // Insert employee 1
        pstmt->setString(1, "John Doe");
        pstmt->setString(2, "Engineering");
        pstmt->setDouble(3, 75000.00);
        pstmt->executeUpdate();

        // Insert employee 2
        pstmt->setString(1, "Jane Smith");
        pstmt->setString(2, "Marketing");
        pstmt->setDouble(3, 65000.00);
        pstmt->executeUpdate();

        cout << "Created 2 employees." << endl;
        delete pstmt;

        // --- READ: Query employees ---
        pstmt = con->prepareStatement("SELECT id, name, department, salary FROM employees");
        ResultSet *res = pstmt->executeQuery();

        cout << "\nReading employees:" << endl;
        while (res->next()) {
            cout << "ID: " << res->getInt("id")
                 << ", Name: " << res->getString("name")
                 << ", Department: " << res->getString("department")
                 << ", Salary: $" << res->getDouble("salary") << endl;
        }
        delete res;
        delete pstmt;

        // --- UPDATE: Modify an employee's department ---
        pstmt = con->prepareStatement(
            "UPDATE employees SET department = ? WHERE name = ?"
        );
        pstmt->setString(1, "Research");
        pstmt->setString(2, "John Doe");
        pstmt->executeUpdate();
        cout << "\nUpdated John Doe's department to Research." << endl;
        delete pstmt;

        // --- READ: Verify update ---
        pstmt = con->prepareStatement("SELECT id, name, department FROM employees WHERE name = ?");
        pstmt->setString(1, "John Doe");
        res = pstmt->executeQuery();

        if (res->next()) {
            cout << "\nVerified update:" << endl;
            cout << "ID: " << res->getInt("id")
                 << ", Name: " << res->getString("name")
                 << ", Department: " << res->getString("department") << endl;
        }
        delete res;
        delete pstmt;

        // --- DELETE: Remove an employee ---
        pstmt = con->prepareStatement("DELETE FROM employees WHERE name = ?");
        pstmt->setString(1, "Jane Smith");
        pstmt->executeUpdate();
        cout << "\nDeleted Jane Smith." << endl;
        delete pstmt;

        // --- READ: Final state ---
        pstmt = con->prepareStatement("SELECT id, name, department FROM employees");
        res = pstmt->executeQuery();

        cout << "\nFinal employees:" << endl;
        while (res->next()) {
            cout << "ID: " << res->getInt("id")
                 << ", Name: " << res->getString("name")
                 << ", Department: " << res->getString("department") << endl;
        }
        delete res;
        delete pstmt;

        // Clean up
        stmt = con->createStatement();
        stmt->execute("DROP SCHEMA test");
        cout << "\nCleaned up schema." << endl;
        delete stmt;
        delete con;
    } catch (SQLException &e) {
        cout << "SQL Error: " << e.what() << " (Code: " << e.getErrorCode() << ")" << endl;
        return 1;
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "Demo completed successfully." << endl;
    return 0;
}

// g++ -o jdbc mysql-jdbc.cc -I/usr/local/mysql-connector-c++-9.0.0/include/jdbc -L/usr/local/mysql-connector-c++-9.0.0/lib64/ -lmysqlcppconn -Wl,-rpath,/usr/local/mysql-connector-c++-9.0.0/lib64/