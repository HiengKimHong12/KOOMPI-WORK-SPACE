#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "writer.h"
#include "ui_writer.h"
#include "QDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_doccumenttoolButton_clicked()
{
    writer *dialog = new writer(this);
    dialog->show();

}
