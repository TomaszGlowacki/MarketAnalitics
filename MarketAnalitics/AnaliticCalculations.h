
#ifndef ANALITICCALCULATIONS_H
#define ANALITICCALCULATIONS_H

#include <vector>

class AnaliticCalculations
{
public:
	AnaliticCalculations();
	~AnaliticCalculations();

	double Average(std::vector< std::pair<double, double> > data );
	double Variance(std::vector< std::pair<double, double> > data);
	double StandardDeviation(std::vector< std::pair<double, double> > data);
	
	double RateOfProfit(double begin, double end);
	std::vector< std::pair<double, double> > SetOfRatesOfProfit( std::vector< std::pair<double, double> > data );
};


#endif // ANALITICCALCULATIONS_H

