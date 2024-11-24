#include "Editor/Editor.h"
#include <cassert>
#include <iostream>

void testEditorOpenFile() {
    Editor editor;
    editor.openFile("test.txt");
    assert(editor.getText() == "This is a test file.\n"); // Replace with expected content
    std::cout << "testEditorOpenFile passed!" << std::endl;
}

void testEditorSaveFile() {
    Editor editor;
    editor.setText("Sample content for save test.");
    editor.saveFile("test_output.txt");

    Editor verifyEditor;
    verifyEditor.openFile("test_output.txt");
    assert(verifyEditor.getText() == "Sample content for save test.");
    std::cout << "testEditorSaveFile passed!" << std::endl;
}

int main() {
    testEditorOpenFile();
    testEditorSaveFile();
    return 0;
}
