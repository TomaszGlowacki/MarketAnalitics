
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTcore\QObject>
#include <QTcore\QString>
#include <QTcore\Qurl>
#include <QTcore\Qfile>
#include <QTcore\QTextCodec>
#include <QTcore\QJsonObject>
#include <QTcore\QJsonDocument>
#include <QTcore\QJsonArray>

#include <QTwidgets\QApplication>
#include <QTwidgets\QPushButton>
#include <QTWidgets\QLabel>
#include <QTWidgets\QProgressBar>
#include <QTWidgets\QMessageBox>

#include <QTGui\QScreen>

#include <QTNetwork\qtnetworkglobal.h>

#include "Downloader.h"
#include "Fund.h"
#include "ChartHolder.h"
#include "AnaliticCalculations.h"

#include <vector>

class Window : public QWidget
{
	Q_OBJECT

private:
	int ResolutionHeight;
	int ResolutionWidth;

	QPushButton *LoadDataButton;
	QProgressBar *progressBar;

	ChartHolder *Chart;
	Downloader *downloader;
	int value;

	QPushButton *PreviousFundButton;
	QPushButton *NextFundButton;

	std::vector<Fund*> AllFunds;
	unsigned int CurrentFund;
	AnaliticCalculations ACalculator;

	QLabel *FundIdLabel;
	QLabel *FundIdLabelValue;
	QLabel *FundNameLabel;
	QLabel *FundNameLabelValue;
	QLabel *AmountOfDataLabel;
	QLabel *AmountOfDataLabelValue;
	QLabel *AverageLabel;
	QLabel *AverageLabelValue;
	QLabel *VarianceLabel;
	QLabel *VarianceLabelValue;
	QLabel *StandardDeviationLabel;
	QLabel *StandardDeviationLabelValue;
	QLabel *RateOfProfitLabel;
	QLabel *RateOfProfitLabelValue;

	public slots:
	void slotButtonClicked(bool checked = 0);
	void load();
	void TakeData();
	void NextFund();
	void PreviousFund();

public:
	Window(QWidget *parent = 0);
	~Window();
	void CreateLabels();

	void CalculateData();
};


#endif // FILEDOWNLOADER_H

