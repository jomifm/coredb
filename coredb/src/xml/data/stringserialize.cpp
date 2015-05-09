#include "xml/data/stringserialize.h"
#include "utils/logger/utilslogger.h"

StringSerialize::StringSerialize()
{
}

StringSerialize::StringSerialize(QString strValue)
{
    LogFuncionBegin;

    setValue(strValue);

    LogFuncionEnd;
}

StringSerialize::~StringSerialize()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

void StringSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void StringSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString StringSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";

    QString sSerializationName = getSerializationName();
    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");
    sRetValue.append(serializeSpecialChars(m_sValue));
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void StringSerialize::setXMLValue(const QString & sValue)
{
    LogFuncionBegin;

    m_sValue = deserializeSpecialChars(sValue);

    LogFuncionEnd;
}
