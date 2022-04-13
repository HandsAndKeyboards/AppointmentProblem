#ifndef HELPER_H
#define HELPER_H

#include <QWidget>
#include <QtWebEngineWidgets>

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
};
#endif // HELPER_H
