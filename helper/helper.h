#ifndef HELPER_H
#define HELPER_H

#include <QWidget>
#include <QDialog>
#include <QTextBrowser>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QtCore5Compat/QTextCodec>

QT_BEGIN_NAMESPACE
namespace Ui { class helper; }
QT_END_NAMESPACE

class helper : public QWidget
{
    Q_OBJECT

public:
    helper(QWidget *parent = nullptr);
    ~helper();

private:
    Ui::helper *ui;
    void DisplayTheoryFile();   // - Вывести HTML файл на экран
};
#endif // HELPER_H
