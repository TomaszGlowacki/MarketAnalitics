
#ifndef FUNDCLASS_H
#define FUNDCLASS_H

#include <QTcore\QString>
#include <Vector>

class Fund
{
private:
	QString Id;

	QString Name;
	QString ShortName;
	QString FullName;

	double MenagmentPayment;
	double EntryPercentPayment;
	double EntryPayment;
	double ExitPercentPayment;
	double ExitPayment;

	int RecomendentRisk;
	int FundCategory;

	std::vector< std::pair< double, double > >  Data;

public:
	Fund();
	~Fund();

	void setId(QString id);
	QString getId();

	void setName(QString name);
	QString getName();
	void setShortName(QString shortName);
	QString getShortName();
	void setFullName(QString fullName);
	QString getFullName();

	void setMenagmentPayment(double menagmentPayment);
	double getMenagmentPayment();
	void setEntryPercentPayment(double entryPercentPayment);
	double getEntryPercentPayment();
	void setEntryPayment(double entryPayment);
	double getEntryPayment();
	void setExitPercentPayment(double exitPercentPayment);
	double getExitPercentPayment();
	void setExitPayment(double exitPayment);
	double getExitPayment();
	void setRecomendentRisk(int recomendentRisk);
	int getRecomendentRisk();
	void setFundCategory(int fundCategory);
	int getFundCategory();

	void setData(std::vector< std::pair< double, double > >  data);
	std::vector< std::pair< double, double > >  getData();
	void AddSingleData(double date, double value);
	std::pair< double, double > GetSingleData(unsigned int index);

};


#endif // FUNDCLASS_H
