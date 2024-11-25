#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>
#include <QSyntaxHighlighter>
#include <QTimer>
#include <QString>

class Editor : public QTextEdit {
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);         // Constructor
    ~Editor();                                 // Destructor

    void setHighlighter(QSyntaxHighlighter *highlighter); // Assign a syntax highlighter
    bool saveToFile(const QString &filePath);  // Save content to file
    bool loadFromFile(const QString &filePath); // Load content from file
    QString getFilePath() const;               // Get the file path associated with this editor
    void setFilePath(const QString &path);     // Set the file path

protected:
    void keyPressEvent(QKeyEvent *event) override; // Capture key events for features like auto-indent

private:
    QSyntaxHighlighter *highlighter;
    QString currentFilePath;                   // Stores the file path of the current document
    QTimer autoSaveTimer;                      // Timer for auto-saving

private slots:
    void autoSave();                           // Auto-save functionality
};

#endif // EDITOR_H
