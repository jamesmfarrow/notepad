#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //set text edit widget (central) to take up all screen space
    this->setCentralWidget(ui->textEdit);
    setWindowTitle(appname);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    //check if current has been modified - ask to save/discard
    if(ui->textEdit->document()->isModified()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Test", "Save file ?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            on_actionSave_as_triggered();
          }
    }
    //clear document/set new window tile
    ui->textEdit->document()->clear();
    currentFile = "";
    setWindowTitle(appname + currentFile);
}

void MainWindow::on_actionOPen_triggered()
{
    //set 'filename' string to name of file to open
    QString filename = QFileDialog::getOpenFileName((this), "Open the file");
    //object for reading/writing files
    QFile file(filename);
    //currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Can not open file " + file.errorString());
        return;
    }
    setWindowTitle(appname + filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename); //object for reading/writing files
        if(!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Can not save file " + file.errorString());
            return;
        }
    //currentFile = filename;
    setWindowTitle(appname + filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    dirty = false;
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPaperName("Photosmart 5520");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this, "Warning", "Can not access printer");
        return;
    }
    ui->textEdit->print(&printer);
}

void MainWindow::save() {

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "File not saved\n\nSave file ?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
              on_actionSave_as_triggered();
      }
}

void MainWindow::on_actionExit_triggered()
{
    if(ui->textEdit->document()->isEmpty()) QApplication::quit();
    else if(ui->textEdit->document()->isModified()) { std::cout << "mofified" << std::endl; save(); QApplication::quit(); }
    else if(dirty && !(ui->textEdit->document()->isModified())) { std::cout << "dirty&&" << std::endl; QApplication::quit(); }
    else if(dirty) { std::cout << "dirty" << std::endl; save(); QApplication::quit(); }

    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
