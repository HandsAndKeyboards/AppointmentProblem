#include "helper.h"
#include "ui_helper.h"

helper::helper(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::helper)
{
    ui->setupUi(this);

    DisplayTheoryFile();
}

void helper::DisplayTheoryFile()
{
    // - Загружаем файл
    QString TheoryFile_PATH = "E:/Helper/helper/Helper.html";
    QFile TheoryFile(TheoryFile_PATH);

    // - Если с файлом что-то случилось (например пользователь удалил), то вызвать окно с ошибкой
    if(!TheoryFile.open(QIODevice::ReadOnly))
        QMessageBox::information(0, "info", TheoryFile.errorString());

    // - Читаем весь файл и выводим в TextBox
    qDebug() << QDir::currentPath();
    const QString Theory = TheoryFile.readAll();
    ui -> HelpDisplayBox -> setOpenExternalLinks(true);
    ui -> HelpDisplayBox -> setHtml(Theory);
}

helper::~helper()
{
    delete ui;
}

