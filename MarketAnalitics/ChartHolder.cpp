
#include "ChartHolder.h"

ChartHolder::ChartHolder(QWidget *Parent)
{
	chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setGeometry(100, 100, 2000, 1000);
	chartView->setEnabled(true);
	chartView->setParent(Parent);
}

ChartHolder::~ChartHolder()
{
	delete( axisX );
	delete( axisY );
	delete( series );
	delete( chart );
	delete( chartView );
}

void ChartHolder::CreateChart(std::vector<std::pair< double, double > > data, QString name)
{
	series = new QLineSeries();
	QDateTime momentInTime;
	std::pair<double, double> pp;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		pp = data[i];
		momentInTime.setMSecsSinceEpoch(pp.first);
		series->append(momentInTime.toMSecsSinceEpoch(), pp.second);
	}

	QChart* chartToDelete = NULL;
	if (chartView->chart())
	{
		chartToDelete = chartView->chart();
	}

	chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(series);
	chart->setTitle(name);

	axisX = new QDateTimeAxis();
	axisX->setTickCount(10);
	axisX->setFormat("MMM yyyy");
	axisX->setTitleText("Date");
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	axisY = new QValueAxis();
	axisY->setLabelFormat("%i");
	axisY->setTitleText("Value");
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	chartView->setChart(chart);   // WHY ?!
	delete(chartToDelete);
};

