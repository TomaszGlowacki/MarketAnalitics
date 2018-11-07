
#include "Downloader.h"
#include <QtCore\QEventLoop>


Downloader::Downloader(QUrl imageUrl, QObject *parent) :
	QObject(parent)
{
	connect(
		&m_WebCtrl, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(Downloaded(QNetworkReply*))
	);

	QNetworkRequest request(imageUrl);
	
	QNetworkReply *reply = m_WebCtrl.get(request);
	//m_DownloadedData = reply->readAll();

	QEventLoop event;
	connect(reply, SIGNAL(finished()), &event, SLOT(quit()));
	event.exec();
	m_DownloadedData = reply->readAll();
	m_DownloadedData = m_DownloadedData.mid( 1, m_DownloadedData.size()-2);
	//QTextCodec::codecForMib(1015)->toUnicode(downloader->downloadedData());
}

Downloader::~Downloader() { }

void Downloader::downloaded()
{

}

void Downloader::Downloaded(QNetworkReply* pReply) {
	m_DownloadedData = pReply->readAll();
	//emit a signal
	pReply->deleteLater();
	emit downloaded();
}

QString Downloader::downloadedData() const {
	return m_DownloadedData;
}