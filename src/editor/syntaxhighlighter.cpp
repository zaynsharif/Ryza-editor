#include "syntaxhighlighter.h"
#include <QRegularExpression>

// Constructor
SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {}

// Set language rules dynamically
void SyntaxHighlighter::setLanguage(const QString &language) {
    if (language == "cpp") {
        setCppRules();
    } else if (language == "python") {
        setPythonRules();
    } else {
        clearRules(); // Clear rules if language is unsupported
    }
    rehighlight();
}

// Set theme (dark or light)
void SyntaxHighlighter::setTheme(const QString &theme) {
    if (theme == "dark") {
        keywordFormat.setForeground(Qt::cyan);
        stringFormat.setForeground(Qt::green);
        commentFormat.setForeground(Qt::gray);
    } else if (theme == "light") {
        keywordFormat.setForeground(Qt::blue);
        stringFormat.setForeground(Qt::darkGreen);
        commentFormat.setForeground(Qt::darkGray);
    }
    rehighlight();
}

// Highlighting logic
void SyntaxHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Multiline comment highlighting
    setMultilineCommentHighlighting(text);
}

void SyntaxHighlighter::setCppRules() {
    clearRules();

    // Keyword formatting
    keywordFormat.setFontWeight(QFont::Bold);
    keywordFormat.setForeground(Qt::darkBlue);
    QStringList keywordPatterns = {
        "\\bclass\\b", "\\bconst\\b", "\\bint\\b", "\\bfloat\\b", "\\bif\\b",
        "\\belse\\b", "\\breturn\\b", "\\bvoid\\b", "\\bwhile\\b", "\\bfor\\b"
    };

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // String formatting
    stringFormat.setForeground(Qt::darkGreen);
    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression("\".*\""); // Double-quoted strings
    stringRule.format = stringFormat;
    highlightingRules.append(stringRule);

    // Comment formatting
    commentFormat.setForeground(Qt::darkGray);
    HighlightingRule singleLineCommentRule;
    singleLineCommentRule.pattern = QRegularExpression("//[^\n]*");
    singleLineCommentRule.format = commentFormat;
    highlightingRules.append(singleLineCommentRule);

    multilineCommentFormat.setForeground(Qt::darkGray);
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void SyntaxHighlighter::setPythonRules() {
    clearRules();

    // Keyword formatting
    keywordFormat.setFontWeight(QFont::Bold);
    keywordFormat.setForeground(Qt::darkMagenta);
    QStringList keywordPatterns = {
        "\\bdef\\b", "\\bclass\\b", "\\bimport\\b", "\\bfrom\\b", "\\bif\\b",
        "\\belif\\b", "\\belse\\b", "\\breturn\\b", "\\bfor\\b", "\\bwhile\\b"
    };

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // String formatting
    stringFormat.setForeground(Qt::darkYellow);
    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression("\".*\"|'.*'"); // Double-quoted and single-quoted strings
    stringRule.format = stringFormat;
    highlightingRules.append(stringRule);

    // Comment formatting
    commentFormat.setForeground(Qt::darkGray);
    HighlightingRule singleLineCommentRule;
    singleLineCommentRule.pattern = QRegularExpression("#[^\n]*");
    singleLineCommentRule.format = commentFormat;
    highlightingRules.append(singleLineCommentRule);
}

void SyntaxHighlighter::setMultilineCommentHighlighting(const QString &text) {
    setCurrentBlockState(0);

    int startIndex = (previousBlockState() != 1) ? text.indexOf(commentStartExpression) : 0;

    while (startIndex >= 0) {
        QRegularExpressionMatch endMatch = commentEndExpression.match(text, startIndex);
        int endIndex = endMatch.hasMatch() ? endMatch.capturedStart() : -1;
        int commentLength = (endIndex == -1) ? text.length() - startIndex : endIndex - startIndex + endMatch.capturedLength();

        setFormat(startIndex, commentLength, multilineCommentFormat);
        startIndex = (endIndex == -1) ? -1 : text.indexOf(commentStartExpression, endIndex + 1);
    }

    if (startIndex >= 0) {
        setCurrentBlockState(1);
    }
}

void SyntaxHighlighter::clearRules() {
    highlightingRules.clear();
}
