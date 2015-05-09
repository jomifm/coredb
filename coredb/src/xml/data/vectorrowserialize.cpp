#include "xml/data/vectorrowserialize.h"
#include "db/metadata/metadatarow.h"
#include "utils/logger/utilslogger.h"

VectorRowSerialize::VectorRowSerialize()
{
    LogFuncionBegin;

    m_pValue = NULL;

    LogFuncionEnd;
}

VectorRowSerialize::~VectorRowSerialize()
{
    LogFuncionBegin;

    if (m_pValue != NULL)
    {
        for (QVector<MetadataRow*>::iterator tabRow = m_pValue->begin();
                tabRow != m_pValue->end(); ++tabRow)
        {
            delete *tabRow;
        }
        m_pValue->clear();
    }

    LogFuncionEnd;
}

void VectorRowSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString VectorRowSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    QString sSerializationName = getSerializationName();
    int iCount = 0;
    MetadataRow *pTableRow = NULL;

    // begin XML element
    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    // serialize vector's elements
    iCount = m_pValue->size();
    for (int i = 0; i < iCount; i++)
    {
        pTableRow = m_pValue->at(i);
        pTableRow->setSerializationName("Row");
        pTableRow->createSerializeList();
        sRetValue.append(pTableRow->serialize());
    }

    // end XML element
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void VectorRowSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void VectorRowSerialize::setXMLValue(const QString & sValue)
{
    Q_UNUSED(sValue)
    LogFuncionBegin;
    LogFuncionEnd;
}

bool VectorRowSerialize::deserializeObject(DeserializeXml*, XmlNode* pXmlNode)
{
    LogFuncionBegin;

    bool bRetValue = true;
    QString sValue = "";
    XmlNode* pChildXmlNode = NULL;
    MetadataRow* pTableRow = NULL;

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
                /* Create just initial MetadataTableRoe.
                 * Real values will be deserialized from XML. */
                pTableRow = new MetadataRow();
                pTableRow->createDeserializeList();
                pChildXmlNode = pXmlNode->getChild(i);
                if (pChildXmlNode != NULL)
                {
                    bRetValue = bRetValue &
                            pTableRow->deserializeObject(
                                    pTableRow, pChildXmlNode);
                }
                else
                {
                    // something is wrong
                    bRetValue = false;
                }
                if (bRetValue)
                {
                    m_pValue->push_back(pTableRow);
                }
            }

        }
    }

    LogFuncionEnd;

    return bRetValue;
}
