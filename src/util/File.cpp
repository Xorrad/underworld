#include "File.hpp"

#include <filesystem>

std::set<std::string> File::ListFiles(const std::string& dirPath, bool recursive) {
    std::set<std::string> files;
    if (std::filesystem::exists(dirPath)) {
        if (recursive) {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(dirPath))
                files.insert(entry.path().string());
        }
        else {
            for (const auto& entry : std::filesystem::directory_iterator(dirPath))
                files.insert(entry.path().string());
        }
    }
    return files;
}

std::string File::ReadLines(std::ifstream& file) {
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}