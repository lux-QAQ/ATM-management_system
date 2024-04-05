//forecast.h
#ifndef FORECAST_H
#define FORECAST_H

#include <QWidget>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QDateTime>
#include <QList>
#include <QDebug>
#include <QRandomGenerator>
#include <QMap>
#include <QVector>
#include <QPointF>
#include <QtMath>
#include "data.h"

QT_CHARTS_USE_NAMESPACE

    namespace Ui {
    class Forecast;
}

class Forecast : public QWidget
{
    Q_OBJECT

public:
    explicit Forecast(QWidget *parent = nullptr);
    QVector<QPointF> polyfit(const QVector<QPointF> &points, int degree);
    ~Forecast();
private slots:
    void on_forecastButton_clicked();
    void handleDateSelection(const QDate &selectedDate);

    void on_pushButton_clicked();

private:
    void initChart();
    double predictValue(int card_ID, const QDateTime &predictionTime);
    //void handleDateSelection(const QDate &selectedDate);
    void showCalendarDialog();
    void draw_chart(int card_ID);
    void adjustAxes();


private:

    Ui::Forecast *ui;
    QChart * m_chart = nullptr;
    QValueAxis * m_axisX = nullptr;
    QValueAxis * m_axisY = nullptr;
    QLineSeries * m_lineSeries = nullptr;

};

#endif // FORECAST_H
