#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <string>

class SyntaxHighlighter {
public:
    SyntaxHighlighter();
    ~SyntaxHighlighter();

    std::string highlight(const std::string& text);
};

#endif // SYNTAXHIGHLIGHTER_H
