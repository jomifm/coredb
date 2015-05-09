#include "xml/data/vectortableserialize.h"
#include "db/metadata/metadatatable.h"
#include "utils/logger/utilslogger.h"

VectorTableSerialize::VectorTableSerialize()
{
    LogFuncionBegin;

    m_pValue = NULL;

    LogFuncionEnd;
}

VectorTableSerialize::~VectorTableSerialize()
{
    LogFuncionBegin;

    if (m_pValue != NULL)
    {
        for (QVector <MetadataTable*>::iterator tabTable = m_pValue->begin();
                tabTable != m_pValue->end(); ++tabTable)
        {
            delete *tabTable;
        }
        m_pValue->clear();
    }

    LogFuncionEnd;
}

void VectorTableSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString VectorTableSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    QString sSerializationName = getSerializationName();
    int iCount = 0;
    MetadataTable *pTable = NULL;

    // begin XML element
    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    // serialize vector's elements
    iCount = m_pValue->size();
    for (int i = 0; i < iCount; i++)
    {
        pTable = m_pValue->at(i);
        pTable->setSerializationName("Table");
        pTable->createSerializeList();
        sRetValue.append(pTable->serialize());
    }

    // end XML element
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void VectorTableSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void VectorTableSerialize::setXMLValue(const QString & sValue)
{
    Q_UNUSED(sValue)
    LogFuncionBegin;
    LogFuncionEnd;
}

bool VectorTableSerialize::deserializeObject(DeserializeXml*, XmlNode* pXmlNode)
{
    LogFuncionBegin;

    bool bRetValue = true;
    QString sValue = "";
    XmlNode* pChildXmlNode = NULL;
    MetadataTable* pTable = NULL;

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
            for (int i = 0; i < iChildCount; i++)
            {
                /* Create just initial Table.
                 * Real values will be deserialized from XML.*/
                pTable = new MetadataTable();
                pTable->createDeserializeList();
                pChildXmlNode = pXmlNode->getChild(i);
                if (pChildXmlNode != NULL)
                {
                    bRetValue = bRetValue &
                            pTable->deserializeObject(pTable, pChildXmlNode);
                }
                else
                {
                    // something is wrong
                    bRetValue = false;
                }
                if (bRetValue)
                {
                    m_pValue->push_back(pTable);
                }
            }

        }
    }

    LogFuncionEnd;

    return bRetValue;
}
