#include "editor.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QKeyEvent>

Editor::Editor(QWidget *parent)
    : QTextEdit(parent), highlighter(nullptr), currentFilePath("") {
    setFont(QFont("Courier", 12));  // Monospaced font
    setLineWrapMode(QTextEdit::NoWrap); // Disable line wrapping

    // Auto-save timer setup
    connect(&autoSaveTimer, &QTimer::timeout, this, &Editor::autoSave);
    autoSaveTimer.start(30000);  // Auto-save every 30 seconds
}

Editor::~Editor() {
    if (highlighter)
        delete highlighter;
}

void Editor::setHighlighter(QSyntaxHighlighter *highlighter) {
    this->highlighter = highlighter;
    if (this->highlighter)
        this->highlighter->setDocument(this->document());
}

bool Editor::saveToFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save file: " + file.errorString());
        return false;
    }
    QTextStream out(&file);
    out << this->toPlainText();
    file.close();
    currentFilePath = filePath;
    return true;
}

bool Editor::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
        return false;
    }
    QTextStream in(&file);
    this->setPlainText(in.readAll());
    file.close();
    currentFilePath = filePath;
    return true;
}

QString Editor::getFilePath() const {
    return currentFilePath;
}

void Editor::setFilePath(const QString &path) {
    currentFilePath = path;
}

void Editor::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Tab) {
        this->insertPlainText("    "); // Replace tab with spaces
    } else {
        QTextEdit::keyPressEvent(event);
    }
}

void Editor::autoSave() {
    if (!currentFilePath.isEmpty()) {
        saveToFile(currentFilePath);
    }
}
