cmake_minimum_required(VERSION 3.12)
project(ReadXml)

# Set the paths for SQLite and TinyXML-2
set(SQLITE_PATH "C:/Users/khk07/OneDrive/Documents/GitHub/ReadXml/sqlite-dll-win64-x64-202401041713")
set(TINYXML2_PATH "C:/Users/khk07/OneDrive/Documents/GitHub/ReadXml/tinyxml2-master/tinyxml2-master")

# Include directories
include_directories("${SQLITE_PATH}")
include_directories("${TINYXML2_PATH}")

# Add the executable
add_executable(ReadXml main.cpp
        lib/pugiconfig.hpp
        "C:/Users/khk07/OneDrive/Documents/GitHub/ReadXml/tinyxml2-master/tinyxml2-master/tinyxml2.cpp")

# Link against SQLite
target_link_libraries(ReadXml "${SQLITE_PATH}/sqlite3.lib")
