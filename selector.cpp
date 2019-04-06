#include "selector.h"
#include "ui_selector.h"

selector::selector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selector)
{
    ui->setupUi(this);
}

selector::~selector()
{
    delete ui;
}
