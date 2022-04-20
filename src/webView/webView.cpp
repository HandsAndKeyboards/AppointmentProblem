#include <QFileInfo>
#include <QWebEngineHistory>

#include "WebView.h"
#include "ui_WebView.h"
#include "../common/constants.h"

/** **************************************************** PUBLIC **************************************************** **/

/// конструктор класса
WebView::WebView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WebView)
{
    ui->setupUi(this);
	setWindowTitle("Теория");

    displaySource();

    ui->prevPageButton->setEnabled(false);
    ui->nextPageButton->setEnabled(false);

    connect(ui->webView, &QWebEngineView::urlChanged, this, &WebView::urlChanged);
}

/// деструктор класса
WebView::~WebView()
{
    delete ui;
}

/** **************************************************** PRIVATE *************************************************** **/

/// вывод на экран главного файла с теорией
void WebView::displaySource()
{
    ui->webView->load(QUrl(ReferencePath));
}

/** ***************************************************** SLOTS **************************************************** **/

/// переход к предыдущей странице истории
void WebView::on_prevPageButton_clicked()
{
    ui->webView->back();
}

/// переход к следующей странице истории
void WebView::on_nextPageButton_clicked()
{
    ui->webView->forward();
}

/**
 * @brief изменена URL
 * @details включение и отключение кнопок перемщения по истории
 */
void WebView::urlChanged()
{
    /*
     * если мы НЕ можем идти вперед, отключаем кнопку перехода вперед
     * иначе - включаем нопку перехода на следующую страницу
     */
    if (!ui->webView->history()->canGoForward()) { ui->nextPageButton->setEnabled(false); }
    else { if (!ui->nextPageButton->isEnabled()) { ui->nextPageButton->setEnabled(true); } }

    /*
     * если мы НЕ можем идти назад, отключаем кнопку перехода назад
     * иначе - включаем нопку перехода на предыдущую страницу
     */
    if (!ui->webView->history()->canGoBack()) { ui->prevPageButton->setEnabled(false); }
    else { if (!ui->prevPageButton->isEnabled()) { ui->prevPageButton->setEnabled(true); } }
}



