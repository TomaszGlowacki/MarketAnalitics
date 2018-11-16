
//#include "stdafx.h"

#include "MainWindow.h"


QJsonObject ObjectFromString(const QString& in)
{
	QJsonObject obj;
	QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());
	// check validity of the document
	if (!doc.isNull())
	{
		if (doc.isObject())
			obj = doc.object();
		else
			qDebug() << "Document is not an object" << endl;
	}
	else
		qDebug() << "Invalid JSON...\n" << in << endl;
	return obj;
}

void Window::slotButtonClicked(bool checked)
{
	
}

void Window::load()
{
	QString DataAsString = downloader->m_DownloadedData;
	QJsonDocument document = QJsonDocument::fromJson(DataAsString.toUtf8());
	QJsonObject object = document.object();
	QJsonObject::iterator JsonIterator;
	Fund *fund = new Fund();
	double JsonValue;
	for (JsonIterator = object.begin(); JsonIterator != object.end(); ++JsonIterator)
	{
		if (JsonIterator.value().isArray())
		{
			JsonValue;
			for (int i = 0; i< JsonIterator.value().toArray().count() ; ++i)
			{
				JsonValue = JsonIterator.value().toArray().at(i).toArray().at(1).toDouble();
				fund->AddSingleData(JsonIterator.value().toArray().at(i).toArray().at(0).toDouble(), JsonValue);
			}
		}
		if (JsonIterator.key() == "name") fund->setName(JsonIterator.value().toString());
		if (JsonIterator.key() == "id") fund->setId(JsonIterator.value().toString());
	}
	AllFunds.push_back(fund);
}

void Window::AddTextToTreeView(int row, QString label, double value)
{
	AddTextToTreeView(row, label, QString::number(value, 'f', 2));
}

void Window::AddTextToTreeView(int row, QString label, int value)
{
	AddTextToTreeView(row, label, QString::number(value));
}

void Window::AddTextToTreeView(int row, QString label, QString value)
{
	QStandardItem *item = new QStandardItem(label);
	TreeViewModel->setItem(row, 0, item);
	item = new QStandardItem(value);
	TreeViewModel->setItem(row, 1, item);
}

void Window::CalculateData()
{
	if (AllFunds[CurrentFund]) 
	{
		Fund *fund = AllFunds[CurrentFund];
		FundIdLabelValue->setText(fund->getId());
		FundNameLabelValue->setText(fund->getName());
		AmountOfDataLabelValue->setText(QString::number(fund->getData().size()));
		AverageLabelValue->setText(QString::number(ACalculator.Average(fund->getData()), 'f', 2));
		VarianceLabelValue->setText(QString::number(ACalculator.Variance(fund->getData()), 'f', 2));
		StandardDeviationLabelValue->setText(QString::number(ACalculator.StandardDeviation(fund->getData()), 'f', 2));
		RateOfProfitLabelValue->setText(QString::number(ACalculator.RateOfProfit(fund->getData()[0].second, fund->getData()[fund->getData().size() - 1].second), 'f', 2));
		
		AddTextToTreeView(0, "Id", fund->getId());
		AddTextToTreeView(1, "Name", fund->getName()); 
		AddTextToTreeView(2, "Amount", (int)fund->getData().size());
		AddTextToTreeView(3, "Average", ACalculator.Average(fund->getData()));
		AddTextToTreeView(4, "Variance", ACalculator.Variance(fund->getData()));
		AddTextToTreeView(5, "Standard Deviation", ACalculator.StandardDeviation(fund->getData()));
		AddTextToTreeView(6, "Rate Of profit", ACalculator.RateOfProfit(fund->getData()[0].second, fund->getData()[fund->getData().size() - 1].second));
		//AddTextToTreeView(7, "Fund Id", fund->getId());

		TreeView->resizeColumnToContents(0);
	}
}

void Window::ApplyChart()
{
	Fund *fund = AllFunds[CurrentFund];
	std::pair<double, double> tempPair = ACalculator.LeastSquares(fund->getData());
	Chart->ApplyLinearFunctionParameters(tempPair.first, tempPair.second);
	Chart->CreateChart(AllFunds[CurrentFund]->getData(), AllFunds[CurrentFund]->getName());
	CalculateData();
}

void Window::NextFund()
{
	if (AllFunds.size() != 0) 
	{
		if (CurrentFund == AllFunds.size() - 1) CurrentFund = 0;
		else CurrentFund++;
		ApplyChart();
	}
}

void Window::PreviousFund()
{
	if (AllFunds.size() != 0)
	{
		if (CurrentFund == 0) CurrentFund = (int)AllFunds.size() - 1;
		else CurrentFund--;
		ApplyChart();
	}
}

void Window::CreateLabels()
{
	int labelStartX = 2300;
	int labelStartY = 100;
	int labelDistanceX = 300;
	int labelDistanceY = 50;

	FundIdLabel = new QLabel("Id:", this);
	FundIdLabel->setGeometry(labelStartX, labelStartY + labelDistanceY, 300, 100);
	FundNameLabel = new QLabel("Nazwa:", this);
	FundNameLabel->setGeometry(labelStartX, labelStartY + labelDistanceY * 2, 300, 100);
	AmountOfDataLabel = new QLabel("Ilosc Danych:", this);
	AmountOfDataLabel->setGeometry(labelStartX, labelStartY + labelDistanceY * 3, 300, 100);
	AverageLabel = new QLabel("Srednia:", this);
	AverageLabel->setGeometry(labelStartX, labelStartY + labelDistanceY * 4, 300, 100);
	VarianceLabel = new QLabel("Variancja:", this);
	VarianceLabel->setGeometry(labelStartX, labelStartY + labelDistanceY * 5, 300, 100);
	StandardDeviationLabel = new QLabel("Odchylenie standardowe:", this);
	StandardDeviationLabel->setGeometry(labelStartX, labelStartY + labelDistanceY * 6, 300, 100);
	RateOfProfitLabel = new QLabel("Stopa zwrotu:", this);
	RateOfProfitLabel->setGeometry(labelStartX, labelStartY + labelDistanceY * 7, 300, 100);

	FundIdLabelValue = new QLabel("", this);
	FundIdLabelValue->setGeometry(labelStartX + labelDistanceX, labelStartY + labelDistanceY, 300, 100);
	FundNameLabelValue = new QLabel("", this);
	FundNameLabelValue->setGeometry(labelStartX + labelDistanceX, labelStartY + labelDistanceY * 2, 300, 100);
	AmountOfDataLabelValue = new QLabel("0", this);
	AmountOfDataLabelValue->setGeometry(labelStartX + labelDistanceX, labelStartY + labelDistanceY * 3, 300, 100);
	AverageLabelValue = new QLabel("0", this);
	AverageLabelValue->setGeometry(labelStartX + labelDistanceX, labelStartY + labelDistanceY * 4, 300, 100);
	VarianceLabelValue = new QLabel("0", this);
	VarianceLabelValue->setGeometry(labelStartX + labelDistanceX, labelStartY + labelDistanceY * 5, 300, 100);
	StandardDeviationLabelValue = new QLabel("0", this);
	StandardDeviationLabelValue->setGeometry(labelStartX + labelDistanceX, labelStartY + labelDistanceY * 6, 300, 100);
	RateOfProfitLabelValue = new QLabel("0", this);
	RateOfProfitLabelValue->setGeometry(labelStartX + labelDistanceX, labelStartY + labelDistanceY * 7, 300, 100);
}

void Window::TakeData()
{
	QUrl imageURL;
	std::vector<QString> setOfFundId;

	QFile file("ids.txt");
	if (file.open(QFile::ReadWrite | QFile::Text))
	{
		QTextStream in(&file);
		while (!in.atEnd()) 
		{
			QString line = in.readLine();
			setOfFundId.push_back(line);
		}
	}
	progressBar->setMaximum((int)setOfFundId.size()-1);
	progressBar->setValue(0);
	int progressBarValue = 0;
	//for (unsigned int i = 0; i < 10; ++i)    // just few charts, do not download all while debug
	for (unsigned int i = 0; i < setOfFundId.size(); ++i)
	{
		imageURL.setUrl(QString("https://www.mbank.pl/ajax/SFI/drawChart/?funds[]=" + setOfFundId[i]));
		downloader = new Downloader(imageURL, this);
		load();
		progressBar->setValue(++progressBarValue);
	}

	ApplyChart();
}

void Window::SetWindowSize() 
{
	QScreen *screen = QGuiApplication::primaryScreen();
	QRect  screenGeometry = screen->geometry();
	ResolutionHeight = screenGeometry.height();
	ResolutionWidth = screenGeometry.width();
	// a:b = c:d   // c = ad/b  , d = bc/a
	//setFixedSize(2000, 1000);
	
	double RefX = 3840;
	double RefY = 2160;

	RatioX = ResolutionWidth / RefX;
	RatioY = ResolutionHeight / RefY;

	resize(ResolutionWidth/RefX , ResolutionHeight / RefY);
}

void Window::ResetTreeViewContent()
{
	TreeViewModel->clear();
	QStringList Headers;
	Headers << "Wskaznik" << "Wartosc";
	TreeViewModel->setHorizontalHeaderLabels(Headers);
};

Window::Window(QWidget *parent) : QWidget(parent)
{
	SetWindowSize();
	setGeometry(100 * RatioX, 100 * RatioY, 3000 * RatioX, 1500 * RatioY);
	CurrentFund = 0;
	progressBar = new QProgressBar(this);
	progressBar->setRange(0, 100);
	progressBar->setValue(0);
	progressBar->setGeometry(1, 1, 500, 50);
	value = 0;

	int buttonStartX = -50;
	int buttonDistanceX = 250;
	LoadDataButton = new QPushButton("Wczytaj dane", this);
	LoadDataButton->setGeometry(buttonStartX + buttonDistanceX * 1, 1200, 200, 50);
	connect(LoadDataButton, SIGNAL(clicked()), this, SLOT(TakeData()));

	PreviousFundButton = new QPushButton("Poprzedni", this);
	PreviousFundButton->setGeometry(buttonStartX + buttonDistanceX * 2, 1200, 200, 50);
	NextFundButton = new QPushButton("Nastepny", this);
	NextFundButton->setGeometry(buttonStartX + buttonDistanceX * 3, 1200, 200, 50);
	CurrentFund = 0;

	connect(PreviousFundButton, SIGNAL(clicked()), this, SLOT(PreviousFund()));
	connect(NextFundButton, SIGNAL(clicked()), this, SLOT(NextFund()));

	Chart = new ChartHolder(this);    // need to add geometry
	CreateLabels();

	TreeView = new QTreeView();
	TreeViewModel = new QStandardItemModel(0,2);
	TreeView->setRootIsDecorated(false);
	TreeView->setModel(TreeViewModel);
	ResetTreeViewContent();

	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 2; ++column) {
			
		}
	}

	

	QHBoxLayout *MainLayout = new QHBoxLayout;
	QVBoxLayout *ChartLayout = new QVBoxLayout;
	QHBoxLayout *ButtonLayout = new QHBoxLayout;

	/*
	QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spLeft.setHorizontalStretch(4);
	Chart->GetWidgetOfChart()->setSizePolicy(spLeft);
	QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spRight.setHorizontalStretch(1);
	TreeView->setSizePolicy(spRight);
	*/

	MainLayout->setContentsMargins(5,5,5,30);
	MainLayout->addLayout(ChartLayout,4);
	MainLayout->addWidget(TreeView,1);
	
	ChartLayout->addWidget(Chart->GetWidgetOfChart());
	ChartLayout->addLayout(ButtonLayout);
	
	ButtonLayout->addWidget(LoadDataButton);
	ButtonLayout->addWidget(PreviousFundButton);
	ButtonLayout->addWidget(NextFundButton);
	ButtonLayout->addWidget(progressBar);


	setLayout(MainLayout);

	
};

Window::~Window() 
{
	delete(LoadDataButton);
	delete(progressBar);

	delete(Chart);
	delete(downloader);
	
	delete(PreviousFundButton);
	delete(NextFundButton);

	delete(FundIdLabel);
	delete(FundIdLabelValue);
	delete(FundNameLabel);
	delete(FundNameLabelValue);
	delete(AmountOfDataLabel);
	delete(AmountOfDataLabelValue);
	delete(AverageLabel);
	delete(AverageLabelValue);
	delete(VarianceLabel);
	delete(VarianceLabelValue);
	delete(StandardDeviationLabel);
	delete(StandardDeviationLabelValue);
	delete(RateOfProfitLabel);
	delete(RateOfProfitLabelValue);

};


