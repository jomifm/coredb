#include "db/metadata/metadatarow.h"
#include "utils/logger/utilslogger.h"

MetadataRow::MetadataRow()
{
    LogFuncionBegin;

    m_status.setValue(E_TR_STAT_NORMAL);
    setSerializationName("Row");
    m_SerializeColumns.setValue(&m_columns);
    m_SerializeColumns.setSerializationName("Columns");
    m_isDBrow.setValue(false);

    LogFuncionEnd;
}

MetadataRow::~MetadataRow()
{
    LogFuncionBegin;

    for (QVector<MetadataColumn*>::iterator tabCol = m_columns.begin(); tabCol
            != m_columns.end(); ++tabCol) {
        delete *tabCol;
    }
    m_columns.clear();

    LogFuncionEnd;
}

void MetadataRow::setNormal()
{
    LogFuncionBegin;

    m_status.setValue(E_TR_STAT_NORMAL);

    LogFuncionEnd;
}

void MetadataRow::setNew()
{
    LogFuncionBegin;

    m_status.setValue(E_TR_STAT_NEW);

    LogFuncionEnd;
}

void MetadataRow::setUpdated()
{
    LogFuncionBegin;

    m_status.setValue(E_TR_STAT_UPDATED);

    LogFuncionEnd;
}

void MetadataRow::setDeleted()
{
    LogFuncionBegin;

    m_status.setValue(E_TR_STAT_DELETED);

    LogFuncionEnd;
}

bool MetadataRow::isNormal() const
{
    LogFuncionBegin;
    LogFuncionEnd;
    return (m_status.getValue() == E_TR_STAT_NORMAL);
}

bool MetadataRow::isNew() const
{
    LogFuncionBegin;
    LogFuncionEnd;
    return (m_status.getValue() == E_TR_STAT_NEW);
}

bool MetadataRow::isDeleted() const
{
    LogFuncionBegin;
    LogFuncionEnd;
    return (m_status.getValue() == E_TR_STAT_DELETED);
}

bool MetadataRow::isUpdated() const
{
    LogFuncionBegin;
    LogFuncionEnd;
    return (m_status.getValue() == E_TR_STAT_UPDATED);
}

MetadataColumn *MetadataRow::addColumn(const QString & colName,
                                     const MetadataColumn::E_COLUMN_TYPE & dataType)
{
    LogFuncionBegin;

    MetadataColumn * pnewCol = NULL;

    pnewCol = new MetadataColumn(colName, dataType);
    m_columns.push_back(pnewCol);

    LogFuncionEnd;

    return pnewCol;
}

MetadataColumn *MetadataRow::addColumn(const QString & strColumnName,
                                       const QVariant::Type & idDataType)
{
    LogFuncionBegin;

    MetadataColumn::E_COLUMN_TYPE idType;
    MetadataColumn * metadataColumn = NULL;

    if (idDataType == QVariant::Bool) idType = MetadataColumn::E_CT_BOOLEAN;
    else if (idDataType == QVariant::Int) idType = MetadataColumn::E_CT_INT;
    else if (idDataType == QVariant::Double) idType = MetadataColumn::E_CT_DOUBLE;
    else idType = MetadataColumn::E_CT_STRING;

    metadataColumn = new MetadataColumn(strColumnName, idType);
    m_columns.push_back(metadataColumn);

    LogFuncionEnd;

    return metadataColumn;
}

MetadataColumn *MetadataRow::addColumn(MetadataColumn *pColumnToCopy)
{
    LogFuncionBegin;

    MetadataColumn*  pRetValue = NULL;
    QString          sColumnName;
    MetadataColumn::E_COLUMN_TYPE   eColumnType;
    bool            BoolValue;
    signed char     ByteValue;
    double          DoubleValue;
    float           FloatValue;
    int             IntValue;
    long            LongValue;
    short int       ShortValue;
    QString         strValue;

    if (pColumnToCopy != NULL)
    {
        sColumnName = pColumnToCopy->getName();
        eColumnType = pColumnToCopy->getDatatype();
        pRetValue = addColumn(sColumnName, eColumnType);
        if (pRetValue != NULL)
        {
            if (pColumnToCopy->isNull())
            {
                pRetValue->setNull(true);
            }
            else if (pColumnToCopy->isNone())
            {
                pRetValue->setNone();
            }
            else
            {
                switch (eColumnType)
                {
                case MetadataColumn::E_CT_BOOLEAN:
                    if (pColumnToCopy->getValue(&BoolValue))
                    {
                        pRetValue->setValue(BoolValue);
                    }
                    break;
                case MetadataColumn::E_CT_BYTE:
                    if (pColumnToCopy->getValue(&ByteValue))
                    {
                        pRetValue->setValue(ByteValue);
                    }
                    break;
                case MetadataColumn::E_CT_DOUBLE:
                    if (pColumnToCopy->getValue(&DoubleValue))
                    {
                        pRetValue->setValue(DoubleValue);
                    }
                    break;
                case MetadataColumn::E_CT_FLOAT:
                    if (pColumnToCopy->getValue(&FloatValue))
                    {
                        pRetValue->setValue(FloatValue);
                    }
                    break;
                case MetadataColumn::E_CT_INT:
                    if (pColumnToCopy->getValue(&IntValue))
                    {
                        pRetValue->setValue(IntValue);
                    }
                    break;
                case MetadataColumn::E_CT_LONG:
                    if (pColumnToCopy->getValue(&LongValue))
                    {
                        pRetValue->setValue(LongValue);
                    }
                    break;
                case MetadataColumn::E_CT_SHORT:
                    if (pColumnToCopy->getValue(&ShortValue))
                    {
                        pRetValue->setValue(ShortValue);
                    }
                    break;
                case MetadataColumn::E_CT_STRING:
                case MetadataColumn::E_CT_DATE:
                case MetadataColumn::E_CT_TIME:
                case MetadataColumn::E_CT_TIMESTAMP:
                    if (pColumnToCopy->getValue(&strValue))
                    {
                        pRetValue->setValue(strValue);
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

    LogFuncionEnd;

    return pRetValue;
}

MetadataColumn *MetadataRow::getColumn(const unsigned int & colIndex) const
{
    LogFuncionBegin;

    if (colIndex > (const unsigned int)m_columns.size() || colIndex < 1)
    {
        LogFuncionEnd;
        return NULL;
    }

    LogFuncionEnd;

    return m_columns.at(colIndex - 1);
}

MetadataColumn *MetadataRow::getColumn(const QString & colName) const
{
    LogFuncionBegin;

    QVector <MetadataColumn *>::const_iterator it = m_columns.begin();
    while (it != m_columns.end())
    {
        if ((*it)->getName().toUpper() == colName.toUpper())
        {
            LogFuncionEnd;
            return (*it);
        }

        ++it;
    }

    LogFuncionEnd;

    return NULL;
}

QString MetadataRow::dataToString(const char delim) const
{
    LogFuncionBegin;

    QString sstr;

    for (int colIdx = 1; colIdx <= getNumberOfColumns(); colIdx++)
    {
        sstr.append(getColumn(colIdx)->getValue());
        if (colIdx != getNumberOfColumns())
        {
            sstr.append(delim);
        }
    }

    LogFuncionEnd;

    return sstr;
}

QString MetadataRow::colNamesToString(const char delim) const
{
    LogFuncionBegin;

    QString retStr="";

    for (int colIdx = 1; colIdx <= getNumberOfColumns(); colIdx++)
    {
        retStr += getColumn(colIdx)->getName();
        if (colIdx != getNumberOfColumns())
        {
            retStr += delim;
        }
    }

    LogFuncionEnd;

    return retStr;
}

QString MetadataRow::getUpdPairs() const
{
    LogFuncionBegin;

    QString retStr;
    QString colVal;

    if (m_status.getValue() == E_TR_STAT_UPDATED)
    {
        for (int colIdx = 1; colIdx <= getNumberOfColumns(); colIdx++)
        {
            MetadataColumn * ptabCol = getColumn(colIdx);

            if (ptabCol->isUpdated())
            {
                if (retStr != "")
                {
                    retStr += ", ";
                }
                retStr += ptabCol->getName() + " = " + ptabCol->getValue();
            }
        }
    }

    LogFuncionEnd;

    return retStr;
}

void MetadataRow::createDeserializeList()
{
    LogFuncionBegin;

    m_vDeserializeObjects.clear();
    addDeserializeObject(&m_status);
    addDeserializeObject(&m_isDBrow);
    addDeserializeObject(&m_SerializeColumns);

    LogFuncionEnd;
}

void MetadataRow::createSerializeList()
{
    LogFuncionBegin;

    m_lstSerializeObjects.clear();
    addSerializeObject(&m_status, "status");
    addSerializeObject(&m_isDBrow, "isDBrow");
    addSerializeObject(&m_SerializeColumns, "Columns");

    LogFuncionEnd;
}

void MetadataRow::setDbRow(const bool isDbRow)
{
    LogFuncionBegin;

    m_isDBrow.setValue(isDbRow);

    LogFuncionEnd;
}

bool MetadataRow::isDbRow() const
{
    LogFuncionBegin;

    return m_isDBrow.getValue();

    LogFuncionEnd;
}

int MetadataRow::GetRowID() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return GetColumnValueInt("ID");
}

int MetadataRow::GetColumnValueInt(const QString & columnName) const
{
    LogFuncionBegin;

    int columnValue = -1;
    MetadataColumn *column = getColumn(columnName);

    if (column != NULL)
    {
        if (!column->isNull())
        {
            column->getValue(&columnValue);
        }
    }

    LogFuncionEnd;

    return columnValue;
}

QString MetadataRow::GetColumnValueString(const QString & columnName) const
{
    LogFuncionBegin;

    QString columnValue = "";
    MetadataColumn *column = getColumn(columnName);

    if (column != NULL)
    {
        if (!column->isNull())
        {
            column->getValue(&columnValue);
        }
    }

    LogFuncionEnd;

    return columnValue;
}

bool MetadataRow::GetColumnValueBool(const QString & columnName) const
{
    LogFuncionBegin;

	bool columnValue = false;
    QString strValue = "", strSI = "SI";

    MetadataColumn *column = getColumn(columnName);

    if (column != NULL)
    {
        if (!column->isNull())
        {
            column->getValue(&strValue);
            if (strValue == strSI)
            	columnValue = true;
        }
    }

    LogFuncionEnd;

    return columnValue;
}
