#include <iostream>
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
#include <QFileInfo>

using namespace std;

int main(int argc, char **argv){
    QApplication app (argc, argv);

    QMainWindow mainWindow;
    QWidget centralWidget;
    QHBoxLayout layout;
    QMenuBar *menuBar = mainWindow.menuBar();
    QMenu *fileMenu = menuBar->addMenu("File");
    QString globalFileName;

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
        //QFileInfo fileInfo(globalFileName);
        QFile filePath = globalFileName;
        if(filePath.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&filePath);
            out << textEdit.toPlainText();
            filePath.close();
        }
        else{
            cout << "something went wrong";
        }

    });
    //TODO: Open button needs fixing

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
        fileName = globalFileName;
    });

    QObject::connect(openAction, &QAction::triggered, [&]() {
        QMessageBox fileOpenedStatus;
        QString fileName = QFileDialog::getOpenFileName(&mainWindow, "Open file", "", "Text files (*.txt);;All files(*)");
        if(!fileName.isEmpty()){
            QFile file(fileName);

            if(file.open(QIODevice::ReadOnly)){
                QTextStream in(&file);
                QString fileContent = in.readAll();
                textEdit.setPlainText(fileContent);
            }
            else{
                fileOpenedStatus.setText("Something went wrong!");
                fileOpenedStatus.exec();
            }
        }
        fileName = globalFileName;

    });

    QObject::connect(exitAction, &QAction::triggered, [&]() {
        app.exit();
    });

    mainWindow.show();
    return app.exec();
}
