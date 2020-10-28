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
#include <QFont>
#include <QFontDialog>
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

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_textEdit_textChanged();

    void selectFont();

    //void setFontBold(bool bold);

    void setFontUnderline(bool underline);

    void setFontItalic(bool italic);

    //void on_actionSelect_Font_changed();

    void on_actionBold_2_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    QString appname{"Notepad\t"};
    QString currentFile{""};
};
#endif // MAINWINDOW_H
