
#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QTcore\QObject>
#include <QTcore\QByteArray>
#include <QtNetwork\QNetworkAccessManager>
#include <QtNetwork\QNetworkRequest>
#include <QtNetwork\QNetworkReply>

class Downloader : public QObject
{
	//Q_OBJECT
public:
	explicit Downloader(QUrl imageUrl, QObject *parent = 0);
	virtual ~Downloader();
	QString downloadedData() const;

	signals:
	void downloaded();

	private slots:
	void Downloaded(QNetworkReply* pReply);

public:
	QNetworkAccessManager m_WebCtrl;
	QString m_DownloadedData;
};

#endif // FILEDOWNLOADER_H

