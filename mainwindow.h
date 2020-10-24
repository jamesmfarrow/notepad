#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDocument>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPushButton>
#include <iostream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT //base class handles events etc

public:
    MainWindow(QWidget *parent = nullptr); //by passing in nullptr we are stating that it has no parents
    ~MainWindow(); //destructor
    bool not_saved{true};

    void save();
    bool dirty{true};

private slots:
    void on_actionNew_triggered();

    void on_actionOPen_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::MainWindow *ui;
    QString appname{"Notepad\t"};
    QString currentFile{""};
};
#endif // MAINWINDOW_H
