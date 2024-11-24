#include "Editor.h"
#include <fstream>
#include <sstream>
#include <iostream>

Editor::Editor() : textBuffer("") {}

Editor::~Editor() {}

void Editor::openFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        textBuffer = buffer.str();
        file.close();
    } else {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
    }
}

void Editor::saveFile(const std::string& filePath) {
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << textBuffer;
        file.close();
    } else {
        std::cerr << "Error: Could not save file " << filePath << std::endl;
    }
}

void Editor::setText(const std::string& text) {
    textBuffer = text;
}

std::string Editor::getText() const {
    return textBuffer;
}
