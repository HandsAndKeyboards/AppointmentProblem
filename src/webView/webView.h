#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QMainWindow>

namespace Ui { class WebView; }

class WebView : public QMainWindow
{
Q_OBJECT

public:
	/// конструктор класса
	explicit WebView(QWidget * parent = nullptr);
	/// деструктор класса
	~WebView();

private:
    Ui::WebView * ui;
	
	/// вывод на экран главного файла с теорией
	void displaySource();

private slots:
	/// переход к предыдущей странице истории
	void on_prevPageButton_clicked();
	/// переход к следующей странице истории
	void on_nextPageButton_clicked();
	/**
	 * @brief изменена URL
	 * @details включение и отключение кнопок перемщения по истории
	 */
    void urlChanged();
};

#endif // WEBVIEW_H
