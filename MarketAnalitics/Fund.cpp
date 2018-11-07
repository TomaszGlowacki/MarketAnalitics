
#include "Fund.h"

Fund::Fund()
{}

Fund::~Fund()
{}

void Fund::setId(QString id) { Id = id; };
QString Fund::getId() { return Id; };

void Fund::setName(QString name) { Name = name; };
QString Fund::getName() { return Name; };
void Fund::setShortName(QString shortName) { ShortName = shortName; };
QString Fund::getShortName() { return ShortName; };
void Fund::setFullName(QString fullName) { FullName = fullName; };
QString Fund::getFullName() { return FullName; };

void Fund::setMenagmentPayment(double menagmentPayment) { MenagmentPayment = menagmentPayment; };
double Fund::getMenagmentPayment() { return MenagmentPayment; };
void Fund::setEntryPercentPayment(double entryPercentPayment) { EntryPercentPayment = entryPercentPayment; };
double Fund::getEntryPercentPayment() { return EntryPercentPayment; };
void Fund::setEntryPayment(double entryPayment) { EntryPayment = entryPayment; };
double Fund::getEntryPayment() { return EntryPayment; };
void Fund::setExitPercentPayment(double exitPercentPayment) { ExitPercentPayment = exitPercentPayment; };
double Fund::getExitPercentPayment() { return ExitPercentPayment; };
void Fund::setExitPayment(double exitPayment) { ExitPayment = exitPayment; };
double Fund::getExitPayment() { return ExitPayment; };

void Fund::setRecomendentRisk(int recomendentRisk) { RecomendentRisk = recomendentRisk; };
int Fund::getRecomendentRisk() { return RecomendentRisk; };
void Fund::setFundCategory(int fundCategory) { FundCategory = fundCategory; };
int Fund::getFundCategory() { return FundCategory; };

void Fund::setData(std::vector< std::pair< double, double > >  data) { Data = data; };
std::vector< std::pair< double, double > >  Fund::getData() { return Data; };
void Fund::AddSingleData(double date, double value) { Data.push_back(std::pair<double, double>(date, value)); };
std::pair< double, double > Fund::GetSingleData(unsigned int index) { return Data.at(index); };

