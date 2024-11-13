#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_ok_bnt_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    QVector<double> temperatureArray;
    QVector<double> elongationArray;
    QVector<double> dertaTemperature;
    double t0,k,sum_y,sum_x,avg_y,avg_x;
    const double l0 = 400.0;
    double alpha,derta_alpha;
    double biao_zhun,e_e;

};
#endif // WIDGET_H
