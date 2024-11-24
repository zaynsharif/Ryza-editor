#include "FileManager.h"
#include <fstream>
#include <iostream>

bool FileManager::exists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

std::string FileManager::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return content;
    } else {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return "";
    }
}

bool FileManager::writeFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << content;
        file.close();
        return true;
    } else {
        std::cerr << "Error: Could not write to file " << filePath << std::endl;
        return false;
    }
}
