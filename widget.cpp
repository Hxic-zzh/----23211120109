#include "widget.h"
#include "ui_widget.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ok_bnt_clicked()
{
    // 从 QLineEdit 获取 t0 的值
    QString t0Text = ui->t0_lineEdit->text();
    bool ok;
    double t0 = t0Text.toDouble(&ok);

    if (!ok) {
        qDebug() << "Invalid input for t0";
        return; // 如果输入无效，直接返回
    }

    int rowCount = ui->tableWidget->rowCount();

    // 清空数组，防止每次点击按钮时重复添加数据
    temperatureArray.clear();
    elongationArray.clear();
    dertaTemperature.clear();

    for (int row = 0; row < rowCount; ++row) {
        // 获取温度（在第1列）
        QTableWidgetItem *tempItem = ui->tableWidget->item(row, 0);
        QString tempData = tempItem ? tempItem->text() : "";
        double temperature = tempData.toDouble();  // 转换为 double
        temperatureArray.append(temperature);

        // 获取伸长量（在第2列）
        QTableWidgetItem *elongationItem = ui->tableWidget->item(row, 1);
        QString elongationData = elongationItem ? elongationItem->text() : "";
        double elongation = elongationData.toDouble();  // 转换为 double
        elongationArray.append(elongation);
    }

    // 计算 dertaTemperature
    for (int i = 0; i < temperatureArray.size(); ++i) {
        double temp = temperatureArray[i];
        dertaTemperature.append(temp - t0);
    }

    // 创建折线系列
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < dertaTemperature.size(); ++i) {
        series->append(dertaTemperature[i], elongationArray[i]);
    }

    // 创建图表并添加系列
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Elongation vs. Derta Temperature");

    // 创建图表视图
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 将 QChartView 设置为 Graphics View 的视图
    ui->graphicsView->setViewport(chartView);


    // 将 dertaTemperature 数组转换为字符串
    QStringList dertaTemperatureStrings;
    for (double value : dertaTemperature) {
        dertaTemperatureStrings << QString::number(value);
    }
    QString dertaTemperatureText = dertaTemperatureStrings.join(", ");

    // 在 QLineEdit 中显示 dertaTemperature
    ui->message_lineEdit01->setText(dertaTemperatureText);

    for(int i = 0;i < elongationArray.size();i++)
    {
        sum_y += elongationArray[i];
    }
    avg_y = sum_y / elongationArray.size();

    for(int i = 0;i < dertaTemperature.size();i++)
    {
        sum_x += dertaTemperature[i];
    }
    avg_x = sum_x / dertaTemperature.size();
    k = avg_y / avg_x;

    QString KString = QString::number(k);
    ui->message_lineEdit02->setText(KString);

    alpha = k / l0;
    QString alphaString = QString::number(alpha, 'e', 6);  // 'e' 表示科学计数法，6 表示保留6位小数
    ui->message_lineEdit03->setText(alphaString);



}

void Widget::on_pushButton_clicked()
{
    QString metalName = ui->message_lineEdit04->text().trimmed();
    if (metalName == "金") {
        biao_zhun = 14.7e-6;
    } else if (metalName == "银") {
        biao_zhun = 18.9e-6;
    } else if (metalName == "铜") {
        biao_zhun = 16.66e-6;
    } else if (metalName == "铁") {
        biao_zhun = 12e-6;
    } else if (metalName == "铝") {
        biao_zhun = 22.2e-6;
    } else if (metalName == "铅") {
        biao_zhun = 27.6e-6;
    } else {
        QString bao_cuo = "错啦，检查检查！";
        ui->message_lineEdit05->setText(bao_cuo);
    }

    derta_alpha = fabs(alpha - biao_zhun);
    QString Dtalpha = QString::number(derta_alpha, 'e', 6);
    ui->message_lineEdit06->setText(Dtalpha);

    e_e = derta_alpha / biao_zhun * 100;
    QString xiang_dui_zhi = QString::number(e_e);
    xiang_dui_zhi += '%';
    ui->message_lineEdit07->setText(xiang_dui_zhi);

}

