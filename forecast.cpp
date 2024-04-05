//forecast.cpp
#include "forecast.h"
#include "ui_forecast.h"
#include <QDebug>
#include <cmath>
#include <QMatrix>
#include <QVector>
#include <QCalendarWidget>
#include "xinxi.h"



Forecast::Forecast(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Forecast)
{
    ui->setupUi(this);
    initChart();
    draw_chart(accountID);



}

Forecast::~Forecast()
{
    delete ui;
}

void Forecast::initChart()
{
    // 创建图表
    m_chart = new QChart();
    m_chart->setTitle("转账金额预测");

    // 创建轴
    m_axisX = new QValueAxis();
    m_axisX->setTitleText("时间");
    m_axisX->setRange(0, 60);
    m_axisX->setGridLineVisible(true);
    m_axisX->setTickCount(6);
    m_axisX->setMinorTickCount(5);
    m_chart->addAxis(m_axisX, Qt::AlignBottom);

    // 计算支出金额的最大值和最小值
    double minAmount = std::numeric_limits<double>::max();
    double maxAmount = std::numeric_limits<double>::min();
    for (const Statement &stmt : statements) {
        if (stmt.type == "转账") {
            double amount = stmt.money;
            if (amount < minAmount) {
                minAmount = amount;
            }
            if (amount > maxAmount) {
                maxAmount = amount;
            }
        }
    }

    // 创建Y轴并设置范围为支出金额的最大值和最小值
    m_axisY = new QValueAxis();
    m_axisY->setTitleText("金额");
    m_axisY->setRange(minAmount, maxAmount);
    m_axisY->setGridLineVisible(true);
    m_axisY->setTickCount(6);
    m_axisY->setMinorTickCount(1);
    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    // 创建折线序列
    m_lineSeries = new QLineSeries();
    m_lineSeries->setName("支出曲线");
    m_chart->addSeries(m_lineSeries);

    // 将折线序列与轴绑定
    m_lineSeries->attachAxis(m_axisX);
    m_lineSeries->attachAxis(m_axisY);

    // 设置抗锯齿
    ui->forecast_chart->setChart(m_chart);
    ui->forecast_chart->setRenderHint(QPainter::Antialiasing);

}

void Forecast::draw_chart(int card_ID)
{
    // 提取当前用户的历史交易记录数据
    QVector<QPointF> userPoints;
    for (const Statement &stmt : statements) {
        if (stmt.accountID == card_ID && stmt.type == "转账") {
            QDateTime time = QDateTime::fromString(stmt.time, "yyyy-MM-dd hh:mm:ss");
            //qDebug() << time <<"格式化";
            double days = time.daysTo(QDateTime::currentDateTime());
            userPoints.append(QPointF(days, stmt.money));
        }
    }

    // 使用 polyfit 函数拟合曲线
    //qDebug() << userPoints;
    QVector<QPointF> fittedPoints = polyfit(userPoints, 10);
    //qDebug() << fittedPoints;

    // 清空折线序列
    m_lineSeries->clear();

    // 将拟合曲线上的点添加到折线序列中
    for (const QPointF &point : fittedPoints) {
        //qDebug() << point;
        m_lineSeries->append(point);
        //qDebug() << m_lineSeries<<"m_lineSeries";
    }

    // 更新图表
    ui->forecast_chart->update();
}


QVector<QPointF> Forecast::polyfit(const QVector<QPointF> &points, int degree)
{
    QVector<QPointF> fittedPoints;

    int n = points.size();
    if (n <= degree + 1) {
        // 数据点数量不足以拟合所需的多项式
        return fittedPoints;
    }

    // 构造矩阵 X 和 Y
    QVector<QVector<double>> X(n, QVector<double>(degree + 1));
    QVector<double> Y(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= degree; ++j) {
            X[i][j] = std::pow(points[i].x(), j);
        }
        Y[i] = points[i].y();
    }

    // 计算 X^T * X
    QVector<QVector<double>> XtX(degree + 1, QVector<double>(degree + 1));
    for (int i = 0; i <= degree; ++i) {
        for (int j = 0; j <= degree; ++j) {
            for (int k = 0; k < n; ++k) {
                XtX[i][j] += X[k][i] * X[k][j];
            }
        }
    }

    // 计算 X^T * Y
    QVector<double> XtY(degree + 1);
    for (int i = 0; i <= degree; ++i) {
        for (int j = 0; j < n; ++j) {
            XtY[i] += X[j][i] * Y[j];
        }
    }

    // 使用高斯消元法求解方程组
    QVector<double> coefficients(degree + 1);
    for (int i = degree; i >= 0; --i) {
        coefficients[i] = XtY[i];
        for (int j = i + 1; j <= degree; ++j) {
            coefficients[i] -= coefficients[j] * XtX[i][j];
        }
        coefficients[i] /= XtX[i][i];
    }

    // 根据多项式系数生成拟合曲线上的点
    double minX = points[0].x();
    double maxX = points[0].x();
    for (int i = 1; i < n; ++i) {
        if (points[i].x() < minX) minX = points[i].x();
        if (points[i].x() > maxX) maxX = points[i].x();
    }
    for (double x = minX; x <= maxX; x += 0.1) {
        double y = 0.0;
        for (int j = 0; j <= degree; ++j) {
            y += coefficients[j] * std::pow(x, j);
        }
        fittedPoints.append(QPointF(x, y));
    }

    return fittedPoints;
}

void Forecast::on_forecastButton_clicked()
{
    /*
    // 1. 获取lineEdit中的日期字符串
    QString dateString = ui->lineEdit->text();

    // 2. 将日期字符串转换为QDateTime对象
    QDateTime dateTime = QDateTime::fromString(dateString, "yyyy-MM-dd hh:mm:ss");

    // 3. 使用回归曲线计算预测值（假设predictValue()函数用于计算预测值）
    double prediction = predictValue(accountID,dateTime);

    // 4. 将预测值显示在resultlineEdit中
    ui->resultlineEdit->setText(QString::number(prediction));
*/
    Forecast::showCalendarDialog();
}

double Forecast::predictValue(int card_ID, const QDateTime &predictionTime)
{
    // 提取当前用户的历史交易记录数据
    QVector<QPointF> userPoints;
    for (const Statement &stmt : statements) {
        if (stmt.accountID == card_ID && stmt.type == "转账") {
            QDateTime time = QDateTime::fromString(stmt.time, "yyyy-MM-dd hh:mm:ss");
            double days = time.daysTo(predictionTime);
            userPoints.append(QPointF(days, stmt.money));
        }
    }

    // 使用 polyfit 函数拟合曲线
    QVector<QPointF> fittedPoints = polyfit(userPoints, 10);

    // 获取拟合曲线上与预测时间最接近的点的交易额作为预测值
    double closestValue = 0.0;
    double minDiff = std::numeric_limits<double>::max();
    for (const QPointF &point : fittedPoints) {
        double diff = std::abs(predictionTime.daysTo(QDateTime::fromMSecsSinceEpoch(point.x() * 24 * 3600 * 1000)));
        if (diff < minDiff) {
            closestValue = point.y();
            minDiff = diff;
        }
    }

    return closestValue;
}

// 在需要使用日期选择的地方调用此函数
void Forecast::showCalendarDialog()
{
    // 创建日期选择对话框
    QCalendarWidget *calendarWidget = new QCalendarWidget();
    calendarWidget->setWindowModality(Qt::WindowModal);

    // 连接日期选择信号到槽函数
    connect(calendarWidget, &QCalendarWidget::clicked, this, &Forecast::handleDateSelection);

    // 显示日期选择对话框
    calendarWidget->show();
}

// 处理用户选择日期的槽函数
void Forecast::handleDateSelection(const QDate &selectedDate)
{
    QDateTime predictionTime(selectedDate);

    // 在这里调用 predictValue 函数，并使用用户选择的日期作为参数
    double predictedValue = predictValue(accountID, predictionTime);

    // 在这里进行任何其他操作，例如显示预测的金额
    ui->resultlineEdit->setText(QString::number(predictedValue));
}

void Forecast::on_pushButton_clicked()
{
    xinxi *x=new xinxi;
    this->hide();
    x->show();
}

