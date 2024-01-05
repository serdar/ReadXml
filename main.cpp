#include <iostream>
#include "lib/pugixml.hpp"

void readFile () {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("import/file.xml");

    for (pugi::xml_node tool: doc.child("post").children())
    {
        std::cout << tool.name() << ": " << tool.child_value() <<"\n";
    }
}

int main() {

    // 1 - Modify readFile to pass in the filename
    // 2 - List out file names in the "import" folder
    // 3 - Loop through file names in (1) and call readFile
    std::cout << "Reading file" << "\n";
    readFile();
    return 0;
}
