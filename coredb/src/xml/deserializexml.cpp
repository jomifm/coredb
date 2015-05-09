#include "xml/deserializexml.h"
#include "xml/deserializexmlhandler.h"
#include "utils/logger/utilslogger.h"

#include <QBuffer>
#include <QtXml>

DeserializeXml::DeserializeXml() : m_oXML(NULL)
{
    LogFuncionBegin;
    m_pCurrentXmlNode = NULL;

    LogFuncionEnd;
}

DeserializeXml::~DeserializeXml()
{
    LogFuncionBegin;

    m_vDeserializeObjects.clear();

    LogFuncionEnd;
}

void DeserializeXml::addDeserializeObject(DeserializeXml* oObject)
{
    LogFuncionBegin;

    m_vDeserializeObjects.push_back(oObject);

    LogFuncionEnd;
}

void DeserializeXml::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

bool DeserializeXml::deserializeAll(const QString & sXML)
{
    LogFuncionBegin;

    bool bRetValue = false;
    QXmlSimpleReader xmlReader;
    DeserializeXmlHandler handler;
    QBuffer oBuffer;

    oBuffer.setData(sXML.toStdString().c_str());
    if (oBuffer.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        createDeserializeList();
        xmlReader.setContentHandler(&handler);
        xmlReader.setErrorHandler(&handler);
        QXmlInputSource *pSource = new QXmlInputSource(&oBuffer);
        if (xmlReader.parse(pSource))
        {
            m_pCurrentXmlNode = handler.getXml();
            if (m_pCurrentXmlNode != NULL)
            {
                if (m_pCurrentXmlNode->getChildCount() == 1)
                {
                    m_pCurrentXmlNode = m_pCurrentXmlNode->getChild(0);
                    deserializeObject(static_cast<DeserializeXml*>(this), m_pCurrentXmlNode);
                    bRetValue = true;
                }
            }
        }
        delete pSource;
    }

    LogFuncionEnd;

    return bRetValue;
}

bool DeserializeXml::deserializeObject(DeserializeXml* pDeserializeObj, XmlNode* pXmlNode)
{
    LogFuncionBegin;

    bool bRetValue = true;
    QVector<DeserializeXml*>* pListDeserializeObj;
    XmlNode* pChildXmlNode;

    if (pXmlNode != NULL)
    {
        pListDeserializeObj = pDeserializeObj->getDeserializeObjects();
        if (pListDeserializeObj != NULL)
        {
            int iObjectsCount = pListDeserializeObj->size();
            int iChildsCount = pXmlNode->getChildCount();
            if (iObjectsCount == iChildsCount)
            {
                if (iObjectsCount != 0)
                {
                    for(int i = 0; i < iObjectsCount; i++)
                    {
                        pDeserializeObj = pListDeserializeObj->at(i);
                        if (pDeserializeObj != NULL)
                        {
                            pDeserializeObj->createDeserializeList();
                            pChildXmlNode = pXmlNode->getChild(i);
                            if (pChildXmlNode != NULL)
                            {
                                bRetValue = bRetValue &
                                    pDeserializeObj->deserializeObject(
                                            pDeserializeObj, pChildXmlNode);
                            }
                            else
                            {
                                /* something is wrong */
                                bRetValue = false;
                            }
                        }
                    }
                }
                else
                {
                    int intType = pXmlNode->getAttribute("type").toInt();
                    if (intType == QVariant::Invalid)
                        pDeserializeObj->setXMLValue(pXmlNode->getNodeValue());
                    else pDeserializeObj->setXMLValue(pXmlNode->getNodeValue(), intType);
                }
            }
            else
            {
                /* something is wrong */
                bRetValue = false;
            }
        } /* no objects for deserialization */
    }
    else
    {
        /* something is wrong */
        bRetValue = false;
    }

    LogFuncionEnd;

    return bRetValue;
}

void DeserializeXml::setXMLValue(const QString & sValue)
{
    Q_UNUSED(sValue)
    /*Do nothing here. This function should be overwritten
    in elementar deserialization classes like
    IntSerialize, BoolSerialize, ...
    */
    LogFuncionBegin;
    LogFuncionEnd;
}

void DeserializeXml::setXMLValue(const QString & sValue, const int & intType)
{
    Q_UNUSED(sValue)
    Q_UNUSED(intType)
    /*Do nothing here. This function should be overwritten
    in elementar deserialization classes like
    IntSerialize, BoolSerialize, ...
    */
    LogFuncionBegin;
    LogFuncionEnd;
}

QString DeserializeXml::deserializeSpecialChars(const QString & srcStr)
{
    LogFuncionBegin;

    QString convertedString(srcStr);

    convertedString = convertedString.replace("&amp;", "&");
    convertedString = convertedString.replace("&gt;", ">");
    convertedString = convertedString.replace("&lt;", "<");
    convertedString = convertedString.replace("&quot;", "\"");

    LogFuncionEnd;

    return convertedString;
}
