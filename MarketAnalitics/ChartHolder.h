
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

	QChartView *ChartView;
	QChart *Chart;
	QDateTimeAxis *AxisX;
	QValueAxis *AxisY;
	QLineSeries *Series;

	QChart *LinearChart;
	QLineSeries *LinearSeries;
	QValueAxis *LinearAxisY;
	QDateTimeAxis *LinearAxisX;

	bool LinearParametersAplied;
	double LinearFunctionParameterA;
	double LinearFunctionParameterB;
	
	void AddLinearChart(std::vector<std::pair< double, double > > &data);

public:
	ChartHolder(QWidget *Parent = 0);
	~ChartHolder();

	void ApplyLinearFunctionParameters(double linearFunctionParameterA, double linearFunctionParameterB);
	void CreateChart(std::vector<std::pair< double, double > > data, QString name);
	
};


#endif // CHARTHOLDER_H

