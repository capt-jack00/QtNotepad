//#include <iostream>
#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>
#include <QTextEdit>

int main(int argc, char **argv){
    QApplication app (argc, argv);

    QMainWindow mainWindow;
    QWidget centralWidget;
    QHBoxLayout layout;

    QTextEdit textEdit;

    layout.addWidget(&textEdit);

    centralWidget.setLayout(&layout);
    mainWindow.setCentralWidget(&centralWidget);

    //textEdit.display();
    mainWindow.show();
    return app.exec();
}
