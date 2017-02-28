#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
     game.initialize(ui->wgtTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_label_3_linkActivated(const QString &link)
{

}



void MainWindow::on_btnRight_clicked()
{
    game.sendData(1);   //1 is for right
}

void MainWindow::on_btnLeft_clicked()
{
    game.sendData(0);   //0 is for right
}

void MainWindow::on_btn00_clicked()
{
     game.setCurData(0, 0);
}

void MainWindow::on_btn01_clicked()
{
        game.setCurData(0, 1);
}

void MainWindow::on_btn02_clicked()
{
    game.setCurData(0, 2);
}

void MainWindow::on_btn03_clicked()
{
    game.setCurData(0, 3);
}

void MainWindow::on_btn04_clicked()
{
    game.setCurData(0, 4);
}

void MainWindow::on_btn05_clicked()
{
    game.setCurData(0, 5);
}

void MainWindow::on_btn06_clicked()
{
    game.setCurData(0, 6);
}

void MainWindow::on_btn07_clicked()
{
    game.setCurData(0, 7);
}

void MainWindow::on_btn10_clicked()
{
    game.setCurData(1, 0);
}

void MainWindow::on_btn11_clicked()
{
    game.setCurData(1, 1);
}

void MainWindow::on_btn12_clicked()
{
    game.setCurData(1, 2);
    //highlight current and no one else;
}

void MainWindow::on_btn13_clicked()
{
    game.setCurData(1, 3);
}

void MainWindow::on_btn14_clicked()
{
    game.setCurData(1, 4);
}

void MainWindow::on_btn15_clicked()
{
    game.setCurData(1, 5);
}

void MainWindow::on_btn16_clicked()
{
    game.setCurData(1, 6);
}

void MainWindow::on_btn17_clicked()
{
    game.setCurData(1, 7);
}

void MainWindow::on_btn20_clicked()
{
    game.setCurData(2, 0);
}

void MainWindow::on_btn21_clicked()
{
    game.setCurData(2, 1);
}

void MainWindow::on_btn22_clicked()
{
    game.setCurData(2, 2);
}

void MainWindow::on_btn23_clicked()
{
    game.setCurData(2, 3);
}

void MainWindow::on_btn24_clicked()
{
    game.setCurData(2, 4);
}

void MainWindow::on_btn25_clicked()
{
    game.setCurData(2, 5);
}

void MainWindow::on_btn26_clicked()
{
    game.setCurData(2, 6);
}

void MainWindow::on_btn27_clicked()
{
    game.setCurData(2, 7);
}

void MainWindow::on_btn30_clicked()
{
    game.setCurData(3, 0);
}

void MainWindow::on_btn31_clicked()
{
    game.setCurData(3, 1);
}

void MainWindow::on_btn32_clicked()
{
    game.setCurData(3, 2);
}

void MainWindow::on_btn33_clicked()
{
    game.setCurData(3, 3);
}

void MainWindow::on_btn34_clicked()
{
    game.setCurData(3, 4);
}

void MainWindow::on_btn35_clicked()
{
    game.setCurData(3, 5);
}

void MainWindow::on_btn36_clicked()
{
    game.setCurData(3, 6);
}

void MainWindow::on_btn37_clicked()
{
    game.setCurData(3, 7);
}
