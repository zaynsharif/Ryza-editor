#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <QTextEdit>

class Search {
public:
    Search(QTextEdit *editor);
    ~Search();

    void find(const QString &text, bool caseSensitive);
    void replace(const QString &oldText, const QString &newText);

private:
    QTextEdit *editor;
};

#endif // SEARCH_H
