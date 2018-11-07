
//#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MarketAnalitics/AnaliticCalculations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(AnaliticCalculation)
	{
	public:
		
		TEST_METHOD(RateOfProfit1)
		{
			AnaliticCalculations AC;
			double result = AC.RateOfProfit(100, 120) ;
			Assert::AreEqual(0.2, result, 0.1, L"message", LINE_INFO());
		}
		TEST_METHOD(RateOfProfit2)
		{
			AnaliticCalculations AC;
			double result = AC.RateOfProfit(1000, 1200);
			Assert::AreEqual(0.2, AC.RateOfProfit(1000, 1200), 0.1, L"message", LINE_INFO());
		}
		TEST_METHOD(RateOfProfit3)
		{
			AnaliticCalculations AC;
			double result = AC.RateOfProfit(120, 100);
			Assert::AreEqual(-0.166667, AC.RateOfProfit(120, 100), 0.000001 , L"message", LINE_INFO());
		}
		TEST_METHOD(RateOfProfit4)
		{
			AnaliticCalculations AC;
			Assert::AreEqual(0.0, AC.RateOfProfit(100, 100), 0.1, L"message", LINE_INFO());
		}
		TEST_METHOD(RateOfProfit5)
		{
			AnaliticCalculations AC;
			Assert::AreEqual(1.0, AC.RateOfProfit(100, 200), 0.1, L"message", LINE_INFO());
		}
		TEST_METHOD(RateOfProfit6)
		{
			AnaliticCalculations AC;
			Assert::AreEqual(2.0, AC.RateOfProfit(100, 300), 0.1, L"message", LINE_INFO());
		}
		TEST_METHOD(RateOfProfit7)
		{
			AnaliticCalculations AC;
			Assert::AreEqual(-0.5, AC.RateOfProfit(100, 50), 0.1, L"message", LINE_INFO());
		}

		TEST_METHOD(SetOfRates1)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 100));
			TestVector.push_back(std::pair<double, double>(1, 200));
			TestVector.push_back(std::pair<double, double>(1, 400));
			std::vector< std::pair<double, double> > RatesVector = AC.SetOfRatesOfProfit(TestVector);

			Assert::AreEqual(1.0, RatesVector[0].second, 0.1, L"message", LINE_INFO());
			Assert::AreEqual(1.0, RatesVector[1].second, 0.1, L"message", LINE_INFO());
		}

		TEST_METHOD(Average1a)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			double result = AC.Average(TestVector);
			Assert::AreEqual(0, result, 0.01, L"message", LINE_INFO());
		}
		TEST_METHOD(Average1b)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 1));
			double result = AC.Average(TestVector);
			Assert::AreEqual(1, result, 0.01, L"message", LINE_INFO());
		}
		TEST_METHOD(Average2)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 1));
			TestVector.push_back(std::pair<double, double>(1, 2));
			TestVector.push_back(std::pair<double, double>(1, 3));
			double result = AC.Average(TestVector);
			Assert::AreEqual(2.0, result, 0.01, L"message", LINE_INFO());
		}
		TEST_METHOD(Average3)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, -10));
			TestVector.push_back(std::pair<double, double>(1, 0));
			TestVector.push_back(std::pair<double, double>(1, 10));
			double result = AC.Average(TestVector);
			Assert::AreEqual(0.0, result, 0.01, L"message", LINE_INFO());
		}
		TEST_METHOD(Average4)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 1));
			TestVector.push_back(std::pair<double, double>(1, 2));
			TestVector.push_back(std::pair<double, double>(1, 3));
			TestVector.push_back(std::pair<double, double>(1, 4));
			TestVector.push_back(std::pair<double, double>(1, 5));
			TestVector.push_back(std::pair<double, double>(1, 6));
			TestVector.push_back(std::pair<double, double>(1, 7));
			TestVector.push_back(std::pair<double, double>(1, 8));
			TestVector.push_back(std::pair<double, double>(1, 9));
			TestVector.push_back(std::pair<double, double>(1, 10));
			TestVector.push_back(std::pair<double, double>(1, 11));
			double result = AC.Average(TestVector);
			Assert::AreEqual(6.0, result, 0.01, L"message", LINE_INFO());
		}
		TEST_METHOD(Average5)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			
			for (int i = 0; i <= 1000; ++i)
			{
				TestVector.push_back(std::pair<double, double>(1, i));
			}

			double result = AC.Average(TestVector);
			Assert::AreEqual(500.0, result, 0.01, L"message", LINE_INFO());
		}
		TEST_METHOD(Average6)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;

			for (int i = 0; i <= 1000000; ++i)
			{
				TestVector.push_back(std::pair<double, double>(1, i));
			}

			double result = AC.Average(TestVector);
			Assert::AreEqual(500000.0, result, 0.01, L"message", LINE_INFO());
		}

		TEST_METHOD(Variance0)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;

			double result = AC.Variance(TestVector);
			Assert::AreEqual(0, result, 0.01, L"message", LINE_INFO());
		}

		TEST_METHOD(Variance1)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 4));
			TestVector.push_back(std::pair<double, double>(1, -3));
			TestVector.push_back(std::pair<double, double>(1, 2));
			double result = AC.Variance(TestVector);
			Assert::AreEqual( 8.6667, result, 0.01, L"message", LINE_INFO());
		}

		TEST_METHOD(Variance2)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 5));
			TestVector.push_back(std::pair<double, double>(1, 7));
			TestVector.push_back(std::pair<double, double>(1, 9));
			double result = AC.Variance(TestVector);
			Assert::AreEqual( 2.66667, result, 0.01, L"message", LINE_INFO());
		}

		TEST_METHOD(Variance3)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 2));
			TestVector.push_back(std::pair<double, double>(1, 5));
			TestVector.push_back(std::pair<double, double>(1, 1));
			TestVector.push_back(std::pair<double, double>(1, 3));
			double result = AC.Variance(TestVector);
			Assert::AreEqual( 2.19, result, 0.01, L"message", LINE_INFO());
		}

		TEST_METHOD(VarianceStandardDeviation1)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 2));
			TestVector.push_back(std::pair<double, double>(1, 5));
			TestVector.push_back(std::pair<double, double>(1, 1));
			TestVector.push_back(std::pair<double, double>(1, 3));
			double result = AC.StandardDeviation(TestVector);
			Assert::AreEqual(1.47902, result, 0.1, L"message", LINE_INFO());
		}

		TEST_METHOD(StandardDeviation0)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			double result = AC.StandardDeviation(TestVector);
			Assert::AreEqual(0.0, result, 0.01, L"message", LINE_INFO());
		}

		TEST_METHOD(StandardDeviation1)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 1));
			TestVector.push_back(std::pair<double, double>(1, 2));
			TestVector.push_back(std::pair<double, double>(1, 2));
			TestVector.push_back(std::pair<double, double>(1, 3));
			TestVector.push_back(std::pair<double, double>(1, 3));
			TestVector.push_back(std::pair<double, double>(1, 3));
			TestVector.push_back(std::pair<double, double>(1, 3));
			TestVector.push_back(std::pair<double, double>(1, 4));
			TestVector.push_back(std::pair<double, double>(1, 4));
			TestVector.push_back(std::pair<double, double>(1, 5));
			double result = AC.StandardDeviation(TestVector);
			Assert::AreEqual(1.1, result, 0.01, L"message", LINE_INFO());
		}

		TEST_METHOD(StandardDeviation2)
		{
			AnaliticCalculations AC;
			std::vector< std::pair<double, double> > TestVector;
			TestVector.push_back(std::pair<double, double>(1, 1));
			TestVector.push_back(std::pair<double, double>(1, 1));
			TestVector.push_back(std::pair<double, double>(1, 1));
			TestVector.push_back(std::pair<double, double>(1, 2));
			TestVector.push_back(std::pair<double, double>(1, 3));
			TestVector.push_back(std::pair<double, double>(1, 3));
			TestVector.push_back(std::pair<double, double>(1, 4));
			TestVector.push_back(std::pair<double, double>(1, 5));
			TestVector.push_back(std::pair<double, double>(1, 5));
			TestVector.push_back(std::pair<double, double>(1, 5));
			double result = AC.StandardDeviation(TestVector);
			Assert::AreEqual(1.61245, result, 0.01, L"message", LINE_INFO());
		}


	};
}