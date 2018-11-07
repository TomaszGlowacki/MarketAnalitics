
#ifndef CHARTHOLDER_H
#define CHARTHOLDER_H

#include <QtCharts\QChart>
#include <QtCharts\QLineSeries>
#include <QtCharts\QChartView>
#include <QtCharts\QDateTimeAxis>
#include <QtCharts\QValueAxis>
#include <QtCore\QDateTime>

QT_CHARTS_USE_NAMESPACE

class ChartHolder
{
private:
	
	QWidget *Parent;

	QChartView *chartView;
	QChart *chart;
	QDateTimeAxis *axisX;
	QValueAxis *axisY;
	QLineSeries *series;

public:
	ChartHolder(QWidget *Parent);
	~ChartHolder();

	void CreateChart(std::vector<std::pair< double, double > > data, QString name);

};


#endif // CHARTHOLDER_H

