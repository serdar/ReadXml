#include <iostream>
#include <filesystem>
#include "sqlite3.h"
#include "C:\Users\khk07\OneDrive\Documents\GitHub\ReadXml\tinyxml2-master\tinyxml2-master\tinyxml2.h"
#include "lib/pugixml.hpp"

// Define the database file path using a preprocessor macro
#define DATABASE_FILE_PATH "C:/Users/khk07/OneDrive/Documents/GitHub/ReadXml/cppDB/readData.db"

void listFilesInDirectory(const std::string& directory) {
    std::cout << "Listing files in the '" << directory << "' folder\n";

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        std::cout << "File: \"" << entry.path().filename().string() << "\"\n";

        // Read and display the contents of each XML file
        pugi::xml_document doc;
        if (doc.load_file(entry.path().string().c_str())) {
            std::cout << "Contents:\n";
            for (pugi::xml_node tool : doc.child("post").children()) {
                std::cout << "  " << tool.name() << ": " << tool.child_value() << "\n";
            }
        } else {
            std::cerr << "Failed to load XML file: " << entry.path().filename().string() << "\n";
        }

        std::cout << "\n";
    }
}
int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    // Iterate through columns and print values
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    }
    std::cout << std::endl;

    // Return successful
    return 0;
}

int createTable(sqlite3* db) {
    char* zErrMsg = 0;

    // Save SQL to create a table
    std::string sql = "CREATE TABLE IF NOT EXISTS posts (" \
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                      "NAME   TEXT    NOT NULL);";

    // Run the SQL (convert the string to a C-String with c_str())
    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    return rc;
}

int insertRow(sqlite3* db, const char* Title) {
    char* zErrMsg = 0;

    // Use parameters in the SQL query
    std::string sql = "INSERT INTO posts (ID, name) VALUES (NULL, '" + std::string(Title) + "')";

    int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    return rc;
}

int readXmlAndInsert(sqlite3* db, const char* xmlFilePath) {
    // Print debug information
    std::cout << "Attempting to load XML file: " << xmlFilePath << std::endl;

    // Initialize TinyXML-2
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError loadResult = doc.LoadFile(xmlFilePath);

    if (loadResult != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error loading XML file. Load result: " << loadResult << std::endl;
        return -1;
    }

    // Assume your XML structure has a root element with child elements containing data
    tinyxml2::XMLElement* root = doc.RootElement();
    if (!root) {
        std::cerr << "XML file is empty or has an invalid structure." << std::endl;
        return -1;
    }

    // Iterate over child elements and display data
    std::cout << "Displaying data from the XML file:" << std::endl;
    for (tinyxml2::XMLElement* elem = root->FirstChildElement("post"); elem != nullptr; elem = elem->NextSiblingElement("post")) {
        const char* title = elem->FirstChildElement("title")->GetText(); // Adjusted to extract title data

        // Display data from XML
        if (title) {
            std::cout << "Title: " << title << std::endl;
        }

        // Insert data into the database
        if (title) {
            int rc = insertRow(db, title);
            if (rc != SQLITE_OK) {
                std::cerr << "Error inserting row: " << sqlite3_errmsg(db) << std::endl;
                return rc;
            }
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    const char* xmlFilePath = R"(C:\Users\khk07\OneDrive\Documents\GitHub\ReadXml\cmake-build-debug\NewF.xml)"; // Provide the path to your XML file
     listFilesInDirectory(".\\import");
    const char* title = "somasdfasdfaf";



    // Initialize SQLite
    sqlite3* db;
    int rc = sqlite3_open(DATABASE_FILE_PATH, &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open SQLite database: " << sqlite3_errmsg(db) << std::endl;
        return rc;
    } else {
        // Create the table (uncomment if needed)
//        rc = createTable(db);
//        if (rc != SQLITE_OK) {
//            std::cerr << "Error creating table: " << sqlite3_errmsg(db) << std::endl;
//            sqlite3_close(db);
//            return rc;
//        }

        // Read XML file, display content, and insert data into the table
        rc = insertRow(db, title);
        if (rc != SQLITE_OK) {
            std::cerr << "Error reading XML and inserting data: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return rc;
        }

        // Close the SQLite database
        sqlite3_close(db);

        std::cout << "Done" << std::endl;

    }

    return 0;
}

