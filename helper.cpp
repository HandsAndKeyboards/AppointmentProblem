#include "helper.h"
#include "ui_helper.h"

helper::helper(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::helper)
{
    ui->setupUi(this);

    QWebEngineView *view  = new QWebEngineView(this);
    view->load("Helper.html");
    setCentralWidget(view);
}

helper::~helper()
{
    delete ui;
}

