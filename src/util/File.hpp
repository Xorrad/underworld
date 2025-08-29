#pragma once

namespace File {
    std::set<std::string> ListFiles(const std::string& dirPath, bool recursive = true);
    std::string ReadLines(std::ifstream& file);
}