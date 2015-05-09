#include "xml/data/boolserialize.h"
#include "utils/logger/utilslogger.h"

BoolSerialize::BoolSerialize()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

BoolSerialize::~BoolSerialize()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

void BoolSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void BoolSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString BoolSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    QString sSerializationValue = "true";

    if (m_bValue == false) {
        sSerializationValue = "false";
    }
    QString sSerializationName = getSerializationName();
    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");
    sRetValue.append(sSerializationValue);
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void BoolSerialize::setXMLValue(const QString & sValue)
{
    LogFuncionBegin;

    m_bValue = true;
    //sValue = sValue.trimmed().toLower();
    if (sValue.compare("false") == 0)
    {
        m_bValue = false;
    }

    LogFuncionEnd;
}
