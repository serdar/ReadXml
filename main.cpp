#include <iostream>
#include <filesystem>
#include "lib/pugixml.hpp"

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

int main() {
    // List out file names and contents in the specified folder
    listFilesInDirectory(".\\import");

    return 0;
}
