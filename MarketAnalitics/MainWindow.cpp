
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

void Window::AddTextToTreeViewFunds(int row, int id, QString name)
{
	AddTextToTreeViewFunds(row, QString::number(id), name);
}

void Window::AddTextToTreeViewFunds(int row, double id, QString name)
{
	AddTextToTreeViewFunds(row, QString::number(id), name);
}

void Window::AddTextToTreeViewFunds(int row, QString id, QString name)
{
	QStandardItem *item = new QStandardItem(QString::number(row));
	TreeViewModelFunds->setItem(row, 0, item);
	item = new QStandardItem(id);
	TreeViewModelFunds->setItem(row, 1, item);
	item = new QStandardItem(name);
	TreeViewModelFunds->setItem(row, 2, item);
}

void Window::AddTextToTreeViewProperties(int row, QString label, double value)
{
	AddTextToTreeViewProperties(row, label, QString::number(value, 'f', 2));
}

void Window::AddTextToTreeViewProperties(int row, QString label, int value)
{
	AddTextToTreeViewProperties(row, label, QString::number(value));
}

void Window::AddTextToTreeViewProperties(int row, QString label, QString value)
{
	QStandardItem *item = new QStandardItem(label);
	TreeViewModelProperties->setItem(row, 0, item);
	item = new QStandardItem(value);
	TreeViewModelProperties->setItem(row, 1, item);
}

void Window::CalculateData()
{
	if (AllFunds[CurrentFund]) 
	{
		Fund *fund = AllFunds[CurrentFund];

		AddTextToTreeViewProperties(0, "Id", fund->getId());
		AddTextToTreeViewProperties(1, "Name", fund->getName());
		AddTextToTreeViewProperties(2, "Amount", (int)fund->getData().size());
		AddTextToTreeViewProperties(3, "Average", ACalculator.Average(fund->getData()));
		AddTextToTreeViewProperties(4, "Variance", ACalculator.Variance(fund->getData()));
		AddTextToTreeViewProperties(5, "Standard Deviation", ACalculator.StandardDeviation(fund->getData()));
		AddTextToTreeViewProperties(6, "Rate Of profit", ACalculator.RateOfProfit(fund->getData()[0].second, fund->getData()[fund->getData().size() - 1].second));
		//AddTextToTreeView(7, "Fund Id", fund->getId());

		TreeViewProperties->resizeColumnToContents(0);
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
	// old function
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

	ResetTreeViewFundsContent();
	for (unsigned int i = 0; i < AllFunds.size(); ++i)
	{
		AddTextToTreeViewFunds(i, AllFunds[i]->getId(), AllFunds[i]->getName());
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

void Window::ResetTreeViewFundsContent()
{
	TreeViewModelFunds->clear();
	QStringList Headers;
	Headers << " " << "Id" << "Nazwa Funduszu";
	TreeViewModelFunds->setHorizontalHeaderLabels(Headers);

	TreeViewFunds->setModel(TreeViewModelFunds);

	TreeViewFunds->setMinimumWidth(500);
	TreeViewFunds->setMaximumWidth(500);

	TreeViewFunds->setColumnWidth(0, 10);
	TreeViewFunds->setColumnWidth(1, 30);
	TreeViewFunds->setColumnWidth(2, 250);
}

void Window::ResetTreeViewPropertiesContent()
{
	TreeViewModelProperties->clear();
	QStringList Headers;
	Headers << "Nazwa" << "Wartosc";
	TreeViewModelProperties->setHorizontalHeaderLabels(Headers);
};

void Window::TreeViewFundsClick(const QModelIndex &index)
{
	CurrentFund = TreeViewModelFunds->itemFromIndex(index)->row();
	ApplyChart();
}

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

	TreeViewFunds = new QTreeView();
	TreeViewFunds->installEventFilter(this);
	TreeViewModelFunds = new QStandardItemModel(0,3 );
	
	ResetTreeViewFundsContent();
	TreeViewFunds->setRootIsDecorated(false);

	connect(TreeViewFunds, SIGNAL(clicked(QModelIndex)), this, SLOT(TreeViewFundsClick(QModelIndex)));
	connect(TreeViewFunds, SIGNAL(activated(QModelIndex)), this, SLOT(TreeViewFundsClick(QModelIndex)));

	TreeViewProperties = new QTreeView();
	TreeViewModelProperties = new QStandardItemModel(0,2);
	TreeViewProperties->setRootIsDecorated(false);
	TreeViewProperties->setModel(TreeViewModelProperties);
	ResetTreeViewPropertiesContent();

	QHBoxLayout *MainLayout = new QHBoxLayout;
	QVBoxLayout *ChartLayout = new QVBoxLayout;
	QHBoxLayout *ButtonLayout = new QHBoxLayout;

	MainLayout->setContentsMargins(5,5,5,30);
	MainLayout->addWidget(TreeViewFunds);
	MainLayout->addLayout(ChartLayout,4);
	MainLayout->addWidget(TreeViewProperties,1);
	
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

};

bool Window::eventFilter(QObject* sender, QEvent* event)
{
	
	if (sender == TreeViewFunds)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent * keyEvent = (QKeyEvent*)(event);
			if (keyEvent->key() == Qt::Key_Up)
			{
				PreviousFund();
				TreeViewFunds->setCurrentIndex(TreeViewModelFunds->index(CurrentFund, 0));
				return true;
			} 
			else if (keyEvent->key() == Qt::Key_Down)
			{
				NextFund();
				TreeViewFunds->setCurrentIndex(TreeViewModelFunds->index(CurrentFund, 0));
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
	return 0;
}

void Window::keyPressEvent(QKeyEvent *event)
{
	/*
	if (event->type() == QEvent::KeyPress)
	{
		//QKeyEvent * keyEvent = (QKeyEvent*)(event);
		if (TreeViewFunds->hasFocus()) 
		{
			QMessageBox::information(this, "Salam", "Control Key was ressed" + QString::number(event->key()));
			if (event->key() == Qt::Key_Up)
			{
				PreviousFund();
				return;
			}
			else if (event->key() == Qt::Key_Down)
			{
				NextFund();
				return;
			}
		}
	} */
}
