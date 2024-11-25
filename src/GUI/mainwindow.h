#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTextEdit>
#include <QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();         // Constructor
    ~MainWindow();        // Destructor

    void show();          // Show the main window

private slots:
    void addNewTab();     // Slot to add a new tab
    void closeTab(int index); // Slot to close a specific tab

private:
    QWidget *centralWidget; // Main central widget
    QTabWidget *tabWidget;  // Tab widget for managing multiple tabs
};

#endif // MAINWINDOW_H
