#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void show();

private slots:
    void addNewTab();
    void closeTab(int index);

private:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
};

#endif // MAINWINDOW_H
