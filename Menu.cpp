#include <iostream>
#include <stdlib.h>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// Function to display the menu
void displayMenu(sql::Statement* stmt) {
    try {
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM Dish WHERE Availability = 1");
        cout << "Menu:" << endl;
        while (res->next()) {
            cout << res->getInt("DishID") << ". " << res->getString("DishName") << " - $"
                << res->getDouble("Price") << endl;
        }
        delete res;
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

// Function to search by category
void searchByCategory(sql::Statement* stmt) {
    cout << "1. Search by Category ID" << endl;
    cout << "2. Search by Category Name" << endl;

    cout << "Enter your choice (1-2): ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        int categoryID;
        cout << "Enter category ID: ";
        cin >> categoryID;

        try {
            string query = "SELECT * FROM Dish WHERE CategoryID = " + to_string(categoryID) + " AND Availability = 1";
            sql::ResultSet* res = stmt->executeQuery(query);
            cout << "Dishes in Category ID " << categoryID << ":" << endl;
            while (res->next()) {
                cout << res->getInt("DishID") << ". " << res->getString("DishName") << " - $"
                    << res->getDouble("Price") << endl;
            }
            delete res;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
        break;
    }
    case 2: {
        string categoryName;
        cout << "Enter category name: ";
        cin.ignore(); 
        getline(cin, categoryName);

        try {
            string query = "SELECT * FROM Dish WHERE CategoryID = (SELECT CategoryID FROM Category WHERE CategoryName = '" + categoryName + "') AND Availability = 1";
            sql::ResultSet* res = stmt->executeQuery(query);
            cout << "Dishes in Category " << categoryName << ":" << endl;
            while (res->next()) {
                cout << res->getInt("DishID") << ". " << res->getString("DishName") << " - $"
                    << res->getDouble("Price") << endl;
            }
            delete res;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
        break;
    }
    default:
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }
}

// Function to search by origin
void searchByOrigin(sql::Statement* stmt) {
    cout << "1. Search by Origin ID" << endl;
    cout << "2. Search by Origin Name" << endl;

    cout << "Enter your choice (1-2): ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        int originID;
        cout << "Enter origin ID: ";
        cin >> originID;

        try {
            string query = "SELECT * FROM Dish WHERE DishID IN (SELECT DishID FROM DishOrigin WHERE OriginID = " + to_string(originID) + ") AND Availability = 1";
            sql::ResultSet* res = stmt->executeQuery(query);
            cout << "Dishes from Origin ID " << originID << ":" << endl;
            while (res->next()) {
                cout << res->getInt("DishID") << ". " << res->getString("DishName") << " - $"
                    << res->getDouble("Price") << endl;
            }
            delete res;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
        break;
    }
    case 2: {
        string originName;
        cout << "Enter origin name: ";
        cin.ignore(); 
        getline(cin, originName);

        try {
            string query = "SELECT * FROM Dish WHERE DishID IN (SELECT DishID FROM DishOrigin WHERE OriginID = (SELECT OriginID FROM Origin WHERE OriginName = '" + originName + "')) AND Availability = 1";
            sql::ResultSet* res = stmt->executeQuery(query);
            cout << "Dishes from Origin " << originName << ":" << endl;
            while (res->next()) {
                cout << res->getInt("DishID") << ". " << res->getString("DishName") << " - $"
                    << res->getDouble("Price") << endl;
            }
            delete res;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
        break;
    }
    default:
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }
}

// Function to display dish details
void displayDishDetails(sql::Statement* stmt) {
    cout << "1. Search by Dish ID" << endl;
    cout << "2. Search by Dish Name" << endl;

    cout << "Enter your choice (1-2): ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        int dishID;
        cout << "Enter dish ID: ";
        cin >> dishID;

        try {
            string query = "SELECT * FROM Dish WHERE DishID = " + to_string(dishID) + " AND Availability = 1";
            sql::ResultSet* res = stmt->executeQuery(query);
            if (res->next()) {
                cout << "Details for " << res->getString("DishName") << ":" << endl;
                cout << "Name: " << res->getString("DishName") << endl;
                cout << "Price: $" << res->getDouble("Price") << endl;
                cout << "Availability: " << (res->getInt("Availability") == 1 ? "Available" : "Not Available") << endl;
                cout << "Time Availability: " << res->getString("TimeAvailability") << endl;

                cout << "Ingredients:" << endl;
                string ingredientQuery = "SELECT * FROM Ingredient WHERE IngredientID IN (SELECT IngredientID FROM DishIngredient WHERE DishID = " + to_string(dishID) + ")";
                sql::ResultSet* ingredientRes = stmt->executeQuery(ingredientQuery);
                while (ingredientRes->next()) {
                    cout << "- " << ingredientRes->getString("IngredientName") << " ("
                        << ingredientRes->getDouble("Quantity") << " " << ingredientRes->getString("CountingUnit") << ")" << endl;
                }
                delete ingredientRes;
            }
            else {
                cout << "Dish with ID " << dishID << " not found or not available." << endl;
            }
            delete res;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
        break;
    }
    case 2: {
        string dishName;
        cout << "Enter dish name: ";
        cin.ignore(); 
        getline(cin, dishName);

        try {
            string query = "SELECT * FROM Dish WHERE DishName = '" + dishName + "' AND Availability = 1";
            sql::ResultSet* res = stmt->executeQuery(query);
            if (res->next()) {
                cout << "Details for " << res->getString("DishName") << ":" << endl;
                cout << "Name: " << res->getString("DishName") << endl;
                cout << "Price: $" << res->getDouble("Price") << endl;
                cout << "Availability: " << (res->getInt("Availability") == 1 ? "Available" : "Not Available") << endl;
                cout << "Time Availability: " << res->getString("TimeAvailability") << endl;

                cout << "Ingredients:" << endl;
                int dishID = res->getInt("DishID");
                string ingredientQuery = "SELECT * FROM Ingredient WHERE IngredientID IN (SELECT IngredientID FROM DishIngredient WHERE DishID = " + to_string(dishID) + ")";
                sql::ResultSet* ingredientRes = stmt->executeQuery(ingredientQuery);
                while (ingredientRes->next()) {
                    cout << "- " << ingredientRes->getString("IngredientName") << " ("
                        << ingredientRes->getDouble("Quantity") << " " << ingredientRes->getString("CountingUnit") << ")" << endl;
                }
                delete ingredientRes;
            }
            else {
                cout << "Dish with name " << dishName << " not found or not available." << endl;
            }
            delete res;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
        break;
    }
    default:
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }
}

// Function to display ingredient details
void displayIngredientDetails(sql::Statement* stmt) {
    cout << "1. Search by Ingredient ID" << endl;
    cout << "2. Search by Ingredient Name" << endl;

    cout << "Enter your choice (1-2): ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        int ingredientID;
        cout << "Enter ingredient ID: ";
        cin >> ingredientID;

        try {
            string query = "SELECT * FROM Ingredient WHERE IngredientID = " + to_string(ingredientID);
            sql::ResultSet* res = stmt->executeQuery(query);
            if (res->next()) {
                cout << "Details for " << res->getString("IngredientName") << ":" << endl;
                cout << "Name: " << res->getString("IngredientName") << endl;
                cout << "Quantity: " << res->getDouble("Quantity") << " " << res->getString("CountingUnit") << endl;
                cout << "Import Date: " << res->getString("ImportDate") << endl;
                cout << "Expired Date: " << res->getString("ExpiredDate") << endl;
            }
            else {
                cout << "Ingredient with ID " << ingredientID << " not found." << endl;
            }
            delete res;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
        break;
    }
    case 2: {
        string ingredientName;
        cout << "Enter ingredient name: ";
        cin.ignore(); 
        getline(cin, ingredientName);

        try {
            string query = "SELECT * FROM Ingredient WHERE IngredientName = '" + ingredientName + "'";
            sql::ResultSet* res = stmt->executeQuery(query);
            if (res->next()) {
                cout << "Details for " << res->getString("IngredientName") << ":" << endl;
                cout << "Name: " << res->getString("IngredientName") << endl;
                cout << "Quantity: " << res->getDouble("Quantity") << " " << res->getString("CountingUnit") << endl;
                cout << "Import Date: " << res->getString("ImportDate") << endl;
                cout << "Expired Date: " << res->getString("ExpiredDate") << endl;
            }
            else {
                cout << "Ingredient with name " << ingredientName << " not found." << endl;
            }
            delete res;
        }
        catch (sql::SQLException& e) {
            cerr << "SQL Error: " << e.what() << endl;
        }
        break;
    }
    default:
        cout << "Invalid choice. Please enter 1 or 2." << endl;
    }
}

int main() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
        con->setSchema("emenu");

        sql::Statement* stmt = con->createStatement();

        while (true) {
            cout << "\n1. Display Menu" << endl;
            cout << "2. Search Menu by Category" << endl;
            cout << "3. Search Menu by Origin" << endl;
            cout << "4. Display Dish Details" << endl;
            cout << "5. Display Ingredient Details" << endl;
            cout << "6. Exit" << endl;

            cout << "Enter your choice (1-6): ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                displayMenu(stmt);
                break;
            case 2:
                searchByCategory(stmt);
                break;
            case 3:
                searchByOrigin(stmt);
                break;
            case 4:
                displayDishDetails(stmt);
                break;
            case 5:
                displayIngredientDetails(stmt);
                break;
            case 6:
                delete stmt;
                delete con;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            }
        }

    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }

    return 0;
}
