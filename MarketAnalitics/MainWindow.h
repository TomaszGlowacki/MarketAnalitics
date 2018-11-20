
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
#include <QTWidgets\QTreeView>
#include <QTWidgets\QLayout>

#include <QTGui\QScreen>
#include <QTcore\QItemSelectionModel>
#include <QTGui\QStandardItemModel>
#include <QTGui\QKeyEvent>
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
	double ResolutionHeight;
	double ResolutionWidth;
	double RatioX;
	double RatioY;

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

	QTreeView *TreeViewFunds;
	QStandardItemModel *TreeViewModelFunds;
	QKeyEvent *KeyEvent;

	QTreeView *TreeViewProperties;
	QStandardItemModel *TreeViewModelProperties;

protected:
	bool eventFilter(QObject* sender, QEvent* event);
	void keyPressEvent(QKeyEvent *event);

	public slots:
	void slotButtonClicked(bool checked = 0);
	void load();
	void TakeData();
	void NextFund();
	void PreviousFund();
	void TreeViewFundsClick(const QModelIndex &index);

public:
	Window(QWidget *parent = 0);
	~Window();
	void CreateLabels();

	void CalculateData();
	void ApplyChart();
	void SetWindowSize();

	void AddTextToTreeViewFunds(int row, QString id, QString name);
	void AddTextToTreeViewFunds(int row, int id, QString name);
	void AddTextToTreeViewFunds(int row, double id, QString name);

	void AddTextToTreeViewProperties(int row, QString label, QString value);
	void AddTextToTreeViewProperties(int row, QString label, int value);
	void AddTextToTreeViewProperties(int row, QString label, double value);

	void ResetTreeViewFundsContent();
	void ResetTreeViewPropertiesContent();
};


#endif // FILEDOWNLOADER_H

