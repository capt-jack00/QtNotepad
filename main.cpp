//#include <iostream>
#include <QMainWindow>
#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

using namespace std;

int main(int argc, char **argv){
    QApplication app (argc, argv);

    QMainWindow mainWindow;
    QWidget centralWidget;
    QHBoxLayout layout;
    QMenuBar *menuBar = mainWindow.menuBar();
    QMenu *fileMenu = menuBar->addMenu("File");

    QTextEdit textEdit;

    layout.addWidget(&textEdit);


    QAction *saveAction = fileMenu->addAction("Save");
    QAction *saveAsAction = fileMenu->addAction("Save as");
    QAction *openAction = fileMenu->addAction("Open");
    QAction *exitAction = fileMenu->addAction("Exit");


    centralWidget.setLayout(&layout);
    mainWindow.setCentralWidget(&centralWidget);
    mainWindow.resize(800, 800);

    QObject::connect(saveAction, &QAction::triggered, [&]() {

    });

    QObject::connect(saveAsAction, &QAction::triggered, [&]() {
        QMessageBox fileSavedStatus;
        QString fileName = QFileDialog::getSaveFileName(&mainWindow, "Save file", "", "Text files (*.txt);;All files(*)");
        if(!fileName.isEmpty()){
            QFile file(fileName);

            if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                QTextStream out(&file);
                out << textEdit.toPlainText();
                file.close();

                fileSavedStatus.setText("Saved successfully!");
            }
            else{
                fileSavedStatus.setText("Something went wrong!");
            }
        }

        fileSavedStatus.exec();
    });

    QObject::connect(openAction, &QAction::triggered, [&]() {
        QString fileName = QFileDialog::getOpenFileName(&mainWindow, "Open file", "", "Text files (*.txt);;All files(*)");


    });

    QObject::connect(exitAction, &QAction::triggered, [&]() {
        app.exit();
    });

    mainWindow.show();
    return app.exec();
}
