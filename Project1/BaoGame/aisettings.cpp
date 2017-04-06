#include "aisettings.h"
#include "ui_aisettings.h"

AISettings::AISettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AISettings)
{
    ui->setupUi(this);
     this->setStyleSheet("background-image: url(table.jpg);");
}

AISettings::~AISettings()
{
    delete ui;
}

void AISettings::setGame(Game*game, QWidget *tblWidget)
{
    myGame = game;
    myTblWidget = tblWidget;
}

void AISettings::on_btnCancel_clicked()
{
    this->close();
}

void AISettings::on_btnGo_clicked()
{
    if (myGame->isPvAI())
    {
        myGame->initPvsAI(myTblWidget, ui->sedPlyDepth1->value());
    }
    else
    {
        this->close();
        myGame->initAIvsAI(myTblWidget, ui->sedPlyDepth1->value(), ui->sedPlyDepth2->value());
    }
    this->close();
}
