#include "search.h"
#include <QTextCursor>

Search::Search(QTextEdit *editor) : editor(editor) {}

Search::~Search() {}

void Search::find(const QString &text, bool caseSensitive) {
    QTextDocument::FindFlags flags;
    if (caseSensitive)
        flags |= QTextDocument::FindCaseSensitively;

    QTextCursor cursor = editor->textCursor();
    cursor = editor->document()->find(text, cursor, flags);
    if (!cursor.isNull()) {
        editor->setTextCursor(cursor);
    }
}

void Search::replace(const QString &oldText, const QString &newText) {
    QTextCursor cursor = editor->textCursor();
    cursor = editor->document()->find(oldText, cursor);
    if (!cursor.isNull()) {
        cursor.insertText(newText);
    }
}
