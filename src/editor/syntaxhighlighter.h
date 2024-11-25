#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit SyntaxHighlighter(QTextDocument *parent = nullptr);

    // Set language for syntax highlighting
    void setLanguage(const QString &language);

    // Set theme for syntax highlighting (light/dark)
    void setTheme(const QString &theme);

protected:
    // Override the highlightBlock method to apply the highlighting
    void highlightBlock(const QString &text) override;

private:
    // Highlighting rules (keywords, comments, strings, etc.)
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    // List of syntax highlighting rules
    QVector<HighlightingRule> highlightingRules;

    // Formatting for various components (keywords, comments, strings)
    QTextCharFormat keywordFormat;
    QTextCharFormat stringFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat multilineCommentFormat;

    // Regular expressions for multi-line comments
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    // Method to set the rules for C++
    void setCppRules();

    // Method to set the rules for Python
    void setPythonRules();

    // Method to clear the existing rules
    void clearRules();

    // Method to handle multi-line comment highlighting
    void setMultilineCommentHighlighting(const QString &text);
};

#endif // SYNTAXHIGHLIGHTER_H
