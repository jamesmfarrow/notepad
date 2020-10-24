#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //set text edit widget (central) to take up all screen space
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();//clears file
    ui->textEdit->setText(QString()); //clear text edit widget
}

void MainWindow::on_actionOPen_triggered()
{
    QString filename = QFileDialog::getOpenFileName((this), "Open the file");
    QFile file(filename); //object for reading/writing files
    //currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Can not open file " + file.errorString());
        return;
    }
    setWindowTitle(filename);
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
            //not_saved = true;
            return;
        }
    //currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    //not_saved = false;
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
        QApplication::quit();
      } else {
        QApplication::quit();
      }

}

void MainWindow::on_actionExit_triggered()
{
    //if(currentFile.isModified()) { std::cout << "modified" << std::endl; save();}
    //else
        if(currentFile.isEmpty()) { std::cout << "empty" << std::endl; QApplication::quit(); }

    else QApplication::quit();
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

bool MainWindow::on_textEdit_textChanged()
{
    return true;
}
