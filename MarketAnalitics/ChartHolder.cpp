
#include "ChartHolder.h"

ChartHolder::ChartHolder(QWidget *Parent)
{
	RatioX = 1.0;
	RatioY = 1.0;
	ChartView = new QChartView(Chart);
	ChartView->setRenderHint(QPainter::Antialiasing);
	ChartView->setGeometry(100, 100, 2000, 1000);
	ChartView->setEnabled(true);
	ChartView->setParent(Parent);
	LinearParametersAplied = false;
}

ChartHolder::~ChartHolder()
{
	delete( AxisX );
	delete( AxisY );
	delete( Series );
	delete( Chart );
	delete( ChartView );
}

QChartView* ChartHolder::GetWidgetOfChart()
{
	return ChartView;
}

void ChartHolder::SetRatio(double ratioX, double ratioY)
{
	RatioX = ratioX;
	RatioY = ratioY;
}

void ChartHolder::CreateChartView()
{
	ChartView->setGeometry(100 * RatioX, 100 * RatioY, 2000 * RatioX, 1000 * RatioY);
}

void ChartHolder::ApplyLinearFunctionParameters(double linearFunctionParameterA, double linearFunctionParameterB)
{
	LinearFunctionParameterA = linearFunctionParameterA;
	LinearFunctionParameterB = linearFunctionParameterB;
	LinearParametersAplied = true;
}

void ChartHolder::CreateChart(std::vector<std::pair< double, double > > data, QString name)
{
	if (data.size() == 0) return;  // no need to create chart if there is no data

	Series = new QLineSeries();
	QDateTime momentInTime;
	std::pair<double, double> tempPair;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		tempPair = data[i];
		momentInTime.setMSecsSinceEpoch(tempPair.first);
		Series->append(momentInTime.toMSecsSinceEpoch(), tempPair.second);
	}

	QChart* chartToDelete = NULL;
	if (ChartView->chart())
	{
		chartToDelete = ChartView->chart();
	}

	Series->setColor(QColor(0, 0, 255));
	Chart = new QChart();
	Chart->legend()->hide();
	Chart->addSeries(Series);
	Chart->setTitle(name);

	AxisX = new QDateTimeAxis();
	AxisX->setTickCount(10);
	AxisX->setFormat("MMM yyyy");
	AxisX->setTitleText("Date");
	Chart->addAxis(AxisX, Qt::AlignBottom);
	Series->attachAxis(AxisX);

	AxisY = new QValueAxis();
	AxisY->setLabelFormat("%i");
	AxisY->setTitleText("Value");
	Chart->addAxis(AxisY, Qt::AlignLeft);
	Series->attachAxis(AxisY);

	ChartView->setChart(Chart);   // WHY ?!
	delete(chartToDelete);

	if (LinearParametersAplied)
	{
		AddLinearChart(data);
	}
	LinearParametersAplied = false;

};

void ChartHolder::AddLinearChart(std::vector<std::pair< double, double > > &data)
{
	//LinearChart = new QChart();
	LinearSeries = new QLineSeries();
	QDateTime momentInTime;
	std::pair<double, double> tempPair;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		tempPair = data[i];
		momentInTime.setMSecsSinceEpoch(tempPair.first);
		LinearSeries->append(momentInTime.toMSecsSinceEpoch(), LinearFunctionParameterA * i + LinearFunctionParameterB );
	}
	Chart->addSeries(LinearSeries);

	LinearAxisX = AxisX;
	LinearAxisX->setTickCount(10);
	LinearSeries->attachAxis(LinearAxisX);

	LinearAxisY = AxisY;
	LinearSeries->attachAxis(LinearAxisY);
	LinearSeries->setColor(QColor(255,0,0));
}
