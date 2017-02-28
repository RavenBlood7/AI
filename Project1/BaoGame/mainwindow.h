#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_label_3_linkActivated(const QString &link);

    void on_btn12_clicked();

    void on_btnRight_clicked();

    void on_btnLeft_clicked();

    void on_btn00_clicked();

    void on_btn01_clicked();

    void on_btn02_clicked();

    void on_btn03_clicked();

    void on_btn04_clicked();

    void on_btn05_clicked();

    void on_btn06_clicked();

    void on_btn07_clicked();

    void on_btn10_clicked();

    void on_btn11_clicked();

    void on_btn13_clicked();

    void on_btn14_clicked();

    void on_btn15_clicked();

    void on_btn16_clicked();

    void on_btn17_clicked();

    void on_btn20_clicked();

    void on_btn21_clicked();

    void on_btn22_clicked();

    void on_btn23_clicked();

    void on_btn24_clicked();

    void on_btn25_clicked();

    void on_btn26_clicked();

    void on_btn27_clicked();

    void on_btn30_clicked();

    void on_btn31_clicked();

    void on_btn32_clicked();

    void on_btn33_clicked();

    void on_btn34_clicked();

    void on_btn35_clicked();

    void on_btn36_clicked();

    void on_btn37_clicked();

private:
    Ui::MainWindow *ui;
    Game game;
};

#endif // MAINWINDOW_H
