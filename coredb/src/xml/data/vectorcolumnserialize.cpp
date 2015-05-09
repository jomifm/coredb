#include "xml/data/vectorcolumnserialize.h"
#include "db/metadata/metadatacolumn.h"
#include "utils/logger/utilslogger.h"

VectorColumnSerialize::VectorColumnSerialize()
{
    LogFuncionBegin;

    m_pValue = NULL;

    LogFuncionEnd;
}

VectorColumnSerialize::~VectorColumnSerialize()
{
    LogFuncionBegin;

    if (m_pValue != NULL)
    {
        for (QVector <MetadataColumn*>::iterator tabCol = m_pValue->begin();
                tabCol != m_pValue->end(); ++tabCol)
        {
            delete *tabCol;
        }
        m_pValue->clear();
    }

    LogFuncionEnd;
}

void VectorColumnSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString VectorColumnSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    QString sSerializationName = getSerializationName();
    int iCount = 0;
    MetadataColumn *pTableColumn = NULL;

    // begin XML element
    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    // serialize vector's elements
    iCount = m_pValue->size();
    for (int i = 0; i < iCount; i++)
    {
        pTableColumn = m_pValue->at(i);
        pTableColumn->setSerializationName("Column");
        pTableColumn->createSerializeList();
        sRetValue.append(pTableColumn->serialize());
    }

    // end XML element
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void VectorColumnSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void VectorColumnSerialize::setXMLValue(const QString & sValue)
{
    Q_UNUSED(sValue)
}

bool VectorColumnSerialize::deserializeObject(DeserializeXml*, XmlNode* pXmlNode)
{
    LogFuncionBegin;

    bool  bRetValue = true;
    QString sValue = "";
    XmlNode* pChildXmlNode = NULL;
    MetadataColumn* pTableColumn = NULL;

    if (pXmlNode != NULL)
    {
        int iChildCount = pXmlNode->getChildCount();
        if (iChildCount == 0)
        {
            /* nothing to do */
            bRetValue = true;
        }
        else
        {
            for(int i = 0; i < iChildCount; i++)
            {
                /* Create just initial MetadataColumn.
                 * Real values will be deserialized from XML.
                 * */
                pTableColumn = new MetadataColumn(QString("initName"), MetadataColumn::E_CT_BOOLEAN);
                pTableColumn->createDeserializeList();
                pChildXmlNode = pXmlNode->getChild(i);
                if (pChildXmlNode != NULL)
                {
                    bRetValue = bRetValue &
                            pTableColumn->deserializeObject(
                                    pTableColumn, pChildXmlNode);
                }
                else
                {
                    /* something is wrong */
                    bRetValue = false;
                }
                if (bRetValue)
                {
                    m_pValue->push_back(pTableColumn);
                }
            }

        }
    }

    LogFuncionEnd;

    return bRetValue;
}
