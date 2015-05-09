#include "xml/data/intserialize.h"
#include "utils/logger/utilslogger.h"

IntSerialize::IntSerialize()
{
    LogFuncionBegin;

    m_iValue = 0;

    LogFuncionEnd;
}

IntSerialize::~IntSerialize()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

void IntSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void IntSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString IntSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    char buf[10];
    QString sSerializationName = getSerializationName();

    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");
    snprintf(buf, 10, "%d", m_iValue);
    sRetValue.append(buf);
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void IntSerialize::setXMLValue (const QString & sValue)
{
    LogFuncionBegin;

    m_iValue = atoi(sValue.toStdString().c_str());

    LogFuncionEnd;
}
