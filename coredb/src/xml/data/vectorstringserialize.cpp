#include "xml/data/vectorstringserialize.h"
#include "utils/logger/utilslogger.h"

VectorStringSerialize::VectorStringSerialize()
{
    LogFuncionBegin;

    m_pValue = NULL;

    LogFuncionEnd;
}

VectorStringSerialize::~VectorStringSerialize()
{
    LogFuncionBegin;

    if (m_pValue != NULL)
    {
        m_pValue->clear();
    }

    LogFuncionEnd;
}

void VectorStringSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString VectorStringSerialize::serialize()
{
    LogFuncionBegin;

    QString          sRetValue = "";
    QString          sSerializationName = getSerializationName();
    int             iCount = 0;
    QString          sString = "";
    char            cIndex[10];

    // begin XML element
    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    // serialize vector's elements
    iCount = m_pValue->size();
    for (int i = 0; i < iCount; i++)
    {
        sString.clear();

        snprintf(cIndex, 10, "i%d", i);

        sString.append("<");
        sString.append(cIndex);
        sString.append(">");

        sString.append(serializeSpecialChars(m_pValue->at(i)));

        sString.append("</");
        sString.append(cIndex);
        sString.append(">");

        sRetValue.append(sString);
    }

    // end XML element
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void VectorStringSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void VectorStringSerialize::setXMLValue(const QString & sValue)
{
    Q_UNUSED(sValue)
    LogFuncionBegin;
    LogFuncionEnd;
}

bool VectorStringSerialize::deserializeObject(DeserializeXml* pDeserializeObj, XmlNode* pXmlNode)
{
    LogFuncionBegin;

    Q_UNUSED(pDeserializeObj)

    bool bRetValue = true;
    //string sValue = "";
    XmlNode* pChildXmlNode = NULL;
    QString sString = "";

    if (pXmlNode != NULL)
    {
        int iChildCount = pXmlNode->getChildCount();
        if (iChildCount == 0)
        {
            // nothing to do
            bRetValue = true;
        }
        else
        {
            for(int i = 0; i < iChildCount; i++)
            {
                pChildXmlNode = pXmlNode->getChild(i);
                if (pChildXmlNode != NULL)
                {
                    /*if (pChildXmlNode->GetChildCount() != 0)
                    {*/
                        sString = pChildXmlNode->getNodeValue();
                        //pDeserializeObj->SetXMLValue(sString);
                        m_pValue->push_back(sString);
                    /*}
                    else
                    {
                        bRetValue = false;
                    }*/
                }
                else
                {
                    /* something is wrong */
                    bRetValue = false;
                }
            }

        }
    }

    LogFuncionEnd;

    return bRetValue;
}
