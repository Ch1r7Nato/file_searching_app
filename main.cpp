#include <iostream>
#include <string>
#include <filesystem>

const auto& ROOT_DIR = std::filesystem::current_path().root_path();

bool search_file(const std::string& filename, const std::string& dir = ROOT_DIR.string()) {
    std::error_code ec;
    for (const auto& entry : std::filesystem::directory_iterator(dir, ec)) {
        std::cout << entry.path() << std::endl;
        if (std::filesystem::is_directory(entry)) {
            if (search_file(filename, entry.path().string())) {
                return true;
            }
        } else if (std::filesystem::is_regular_file(entry) && entry.path().filename() == filename) {
            return true; // Found the file
        }
    }
    return false; // Not found in this directory
}

int main() {
    std::string filename;
    std::cout << "Enter the filename to search: ";
    std::cin >> filename;

    if (search_file(filename)) {
        std::cout << "File found!" << std::endl;
    } else {
        std::cout << "File not found." << std::endl;
    }
    return 0;
}
