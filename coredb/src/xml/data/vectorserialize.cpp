#include "xml/data/vectorserialize.h"
#include "utils/logger/utilslogger.h"

VectorSerialize::VectorSerialize()// : vector<T>()
{
    LogFuncionBegin;

    m_pValue = NULL;

    LogFuncionEnd;
}

VectorSerialize::~VectorSerialize()
{
    //vector<TTT>::~vector();
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void VectorSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString VectorSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    QString sSerializationName = getSerializationName();
    int iCount = 0;
    IntSerialize  oSerializeXml;

    //begin XML element
    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    //serialize vector's elements
    iCount = m_pValue->size();
    for (int i = 0; i < iCount; i++)
    {
        oSerializeXml = m_pValue->at(i);
        oSerializeXml.setSerializationName("int");
        sRetValue.append(oSerializeXml.serialize());
    }

    //end XML element
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void VectorSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void VectorSerialize::setXMLValue(const QString & sValue)
{
    LogFuncionBegin;

    IntSerialize  oSerializeXml;

    oSerializeXml.setXMLValue(sValue);
    m_pValue->push_back(oSerializeXml);

    LogFuncionEnd;
}

