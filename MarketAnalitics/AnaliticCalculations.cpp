
#include "AnaliticCalculations.h"


AnaliticCalculations::AnaliticCalculations()
{
}

AnaliticCalculations::~AnaliticCalculations()
{
}

double AnaliticCalculations::Average(std::vector< std::pair<double, double> > data )
{
	if (data.size() == 0) return 0;
	double sum = 0.0;
	for (unsigned int i=0 ; i<data.size() ; ++i)
	{
		sum += data[i].second;
	}
	return (sum / data.size() );
}

double AnaliticCalculations::Variance(std::vector< std::pair<double, double> > data)
{
	if (data.size() == 0) return 0;
	double average = Average(data);
	double sum = 0.0;
	for (unsigned int i = 0; i<data.size(); ++i)
	{
		sum += ( ( data[i].second - average )*( data[i].second - average ) );
	}
	return (sum / data.size());

}

double AnaliticCalculations::StandardDeviation(std::vector< std::pair<double, double> > data)
{
	return (sqrt(Variance(data)));
}

double AnaliticCalculations::RateOfProfit(double begin, double end)
{
	return ((end/begin)-1);
}

std::vector< std::pair<double, double> > AnaliticCalculations::SetOfRatesOfProfit(std::vector< std::pair<double, double> > data)
{
	std::vector< std::pair<double, double> > tempData;
	for (unsigned int i = 1; i<data.size(); ++i)
	{
		tempData.push_back( std::pair<double, double>(data[i].first, RateOfProfit(data[i-1].second, data[i].second)));
	}
	return tempData;
}



