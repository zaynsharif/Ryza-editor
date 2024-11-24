#include "GUI/MainWindow.h"
#include <iostream>

void testMainWindowShow() {
    MainWindow mainWindow;
    mainWindow.show();
    std::cout << "testMainWindowShow passed!" << std::endl;
}

int main() {
    testMainWindowShow();
    return 0;
}
