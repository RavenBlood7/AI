#ifndef AISETTINGS_H
#define AISETTINGS_H

#include <QWidget>
#include "game.h"

namespace Ui {
class AISettings;
}

class AISettings : public QWidget
{
    Q_OBJECT
public:
    explicit AISettings(QWidget *parent = 0);
    ~AISettings();

    void setGame(Game*game, QWidget *tblWidget);

private slots:
    void on_btnCancel_clicked();

    void on_btnGo_clicked();

private:
    Ui::AISettings *ui;
    Game* myGame;
    QWidget* myTblWidget;
};

#endif // AISETTINGS_H
