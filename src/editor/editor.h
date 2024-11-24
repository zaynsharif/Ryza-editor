#ifndef EDITOR_H
#define EDITOR_H

#include <string>

class Editor {
public:
    Editor();
    ~Editor();

    void openFile(const std::string& filePath);
    void saveFile(const std::string& filePath);
    void setText(const std::string& text);
    std::string getText() const;

private:
    std::string textBuffer;
};

#endif // EDITOR_H
