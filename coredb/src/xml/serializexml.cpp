#include "xml/serializexml.h"
#include "utils/logger/utilslogger.h"

SerializeXml::SerializeXml()
{
    LogFuncionBegin;

    m_sSerializationName = "Object";
    m_lstSerializeObjects.clear();

    LogFuncionEnd;
}

SerializeXml::~SerializeXml()
{
    LogFuncionBegin;

    m_lstSerializeObjects.clear();

    LogFuncionEnd;
}

bool SerializeXml::addSerializeObject(SerializeXml* oObject,
                                        const QString & sSerializationName)
{
    LogFuncionBegin;

    m_lstSerializeObjects.push_back(oObject);
    oObject->setSerializationName(sSerializationName);

    LogFuncionEnd;

    return true;
}

void SerializeXml::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString SerializeXml::serializeAll()
{
    LogFuncionBegin;

    QString sRetValue = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";

    createSerializeList();
    sRetValue.append(serialize());

    LogFuncionEnd;

    return sRetValue;
}

QString SerializeXml::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    SerializeXml* oSerializationObj = NULL;
    QString sSerializationName = getSerializationName();
    QString sSubSerialization = "";

    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");
    for (int i = 0; i < (int)m_lstSerializeObjects.size(); i++) {
        oSerializationObj = m_lstSerializeObjects.at(i);
        oSerializationObj->createSerializeList();
        sSubSerialization += oSerializationObj->serialize();
    }
    sRetValue.append(sSubSerialization);
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

QString SerializeXml::serializeSpecialChars(const QString & srcStr)
{
    LogFuncionBegin;

    QString convertedString(srcStr);

    convertedString = convertedString.replace("&", "&amp;");
    convertedString = convertedString.replace(">", "&gt;");
    convertedString = convertedString.replace("<", "&lt;");
    convertedString = convertedString.replace("\"", "&quot;");

    LogFuncionEnd;

    return convertedString;
}
