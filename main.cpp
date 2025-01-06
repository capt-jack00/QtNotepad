//#include <iostream>
#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>

int main(int argc, char **argv){
    QApplication app (argc, argv);

    QMainWindow mainWindow;
    QWidget centralWidget;
    QHBoxLayout layout;
    QMenuBar *menuBar = mainWindow.menuBar();
    QMenu *fileMenu = menuBar->addMenu("File");
    QAction fileSave;

    QTextEdit textEdit;

    layout.addWidget(&textEdit);

    fileMenu->addAction("Save");
    fileMenu->addAction("Save as");
    fileMenu->addAction("Open");
    fileMenu->addAction("Exit");


    centralWidget.setLayout(&layout);
    mainWindow.setCentralWidget(&centralWidget);
    mainWindow.resize(800, 800);




    mainWindow.show();
    return app.exec();
}
