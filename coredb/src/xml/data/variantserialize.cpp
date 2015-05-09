#include "xml/data/variantserialize.h"
#include "db/metadata/metadatacolumn.h"
#include "utils/logger/utilslogger.h"

VariantSerialize::VariantSerialize()
{
    LogFuncionBegin;

    //Inicializacion de variables
    m_datatype.setSerializationName("dataType");
    //m_bFirstAlreadyCalled = false;

    LogFuncionEnd;
}

VariantSerialize::~VariantSerialize()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

void VariantSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //addDeserializeObject(&m_datatype);
    LogFuncionEnd;
}

void VariantSerialize::createSerializeList()
{
    LogFuncionBegin;
    //addSerializeObject(&m_datatype, "datatype");
    LogFuncionEnd;
}

QString VariantSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    QString sValue = "";
    QString sSerializationName = getSerializationName();
    char buf[20];

    //Begin XML element
    sRetValue.append("<");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    //Serialize data type first
    sRetValue.append(m_datatype.serialize());

    //Then serialize data value
    sRetValue.append("<value>");

    switch ((MetadataColumn::E_COLUMN_TYPE)m_datatype.getValue())
    {
        case MetadataColumn::E_CT_BOOLEAN:
            sValue = "true";
            if (m_valBool == false) {
                sValue = "false";
            }
            break;
        case MetadataColumn::E_CT_BYTE:
            snprintf(buf, 20, "%d", m_valByte);
            sValue.append(buf);
            break;
        case MetadataColumn::E_CT_DOUBLE:
            snprintf(buf, 20, "%lf", m_valDouble);
            sValue.append(buf);
            break;
        case MetadataColumn::E_CT_FLOAT:
            snprintf(buf, 20, "%lf", m_valFloat);
            sValue.append(buf);
            break;
        case MetadataColumn::E_CT_INT:
            snprintf(buf, 20, "%d", m_valInt);
            sValue.append(buf);
            break;
        case MetadataColumn::E_CT_LONG:
            snprintf(buf, 20, "%ld", m_valLong);
            sValue.append(buf);
            break;
        case MetadataColumn::E_CT_SHORT:
            snprintf(buf, 20, "%d", m_valShortInt);
            sValue.append(buf);
            break;
        case MetadataColumn::E_CT_STRING:
        case MetadataColumn::E_CT_DATE:
        case MetadataColumn::E_CT_TIME:
        case MetadataColumn::E_CT_TIMESTAMP:
            sValue = serializeSpecialChars(m_valStr);
            break;
        default:
            break;
    }
    sRetValue.append(sValue);

    sRetValue.append("</value>");

    //End XML element
    sRetValue.append("</");
    sRetValue.append(sSerializationName);
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

bool VariantSerialize::deserializeObject(DeserializeXml*, XmlNode* pXmlNode)
{
    LogFuncionBegin;

    bool bRetValue = false;
    QString sValue = "";
    char*  pChar = NULL;
    XmlNode* pChildXmlNode = NULL;

    if (pXmlNode != NULL)
    {
        int iChildCount = pXmlNode->getChildCount();
        if (iChildCount == 0)
        {
            // nothing to do
            bRetValue = true;
        }
        else if (iChildCount == 2)
        {
            // first child is m_datatype
            pChildXmlNode = pXmlNode->getChild(0);
            if (pChildXmlNode != NULL)
            {
                m_datatype.setXMLValue(pChildXmlNode->getNodeValue());
            }
            // second child is value
            pChildXmlNode = pXmlNode->getChild(1);
            if (pChildXmlNode != NULL)
            {
                sValue = pChildXmlNode->getNodeValue();
                switch ((MetadataColumn::E_COLUMN_TYPE)m_datatype.getValue())
                {
                    case MetadataColumn::E_CT_BOOLEAN:
                        m_valBool = true;
                        if (sValue.compare("false") == 0)
                        {
                            m_valBool = false;
                        }
                        break;
                    case MetadataColumn::E_CT_BYTE:
                        m_valByte = (signed char)atoi(sValue.toStdString().c_str());
                        break;
                    case MetadataColumn::E_CT_DOUBLE:
                        m_valDouble = strtod(sValue.toStdString().c_str(), &pChar);
                        break;
                    case MetadataColumn::E_CT_FLOAT:
                        m_valFloat = (float)strtod(sValue.toStdString().c_str(), &pChar);
                        break;
                    case MetadataColumn::E_CT_INT:
                        m_valInt = atoi(sValue.toStdString().c_str());
                        break;
                    case MetadataColumn::E_CT_LONG:
                        m_valLong = atol(sValue.toStdString().c_str());
                        break;
                    case MetadataColumn::E_CT_SHORT:
                        m_valShortInt = (short int)atoi(sValue.toStdString().c_str());
                        break;
                    case MetadataColumn::E_CT_STRING:
                    case MetadataColumn::E_CT_DATE:
                    case MetadataColumn::E_CT_TIME:
                    case MetadataColumn::E_CT_TIMESTAMP:
                        m_valStr = deserializeSpecialChars(sValue);
                        break;
                    default:
                        break;
                }
                bRetValue = true;
            }
        }
        else
        {
            /* something wrong here there should be just 2 values:
             * m_datatype and corresponding value*/
        }
    }
    else
    {
        // something is wrong
    }

    LogFuncionEnd;

    return bRetValue;
}
