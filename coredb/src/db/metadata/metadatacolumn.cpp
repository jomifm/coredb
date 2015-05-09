#include "db/metadata/metadatacolumn.h"
#include "utils/logger/utilslogger.h"

MetadataColumn::MetadataColumn(const QString & colName, const MetadataColumn::E_COLUMN_TYPE dataType)
{
    LogFuncionBegin;

    m_status.setValue(E_TC_STAT_NONE);
    m_name.setValue(colName);
    m_valVariant.m_datatype.setValue(dataType);
    m_isNull.setValue(false);
    setSerializationName("Column");

    LogFuncionEnd;
}

MetadataColumn::~MetadataColumn()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

MetadataColumn::E_COLUMN_TYPE MetadataColumn::getDatatype() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return (E_COLUMN_TYPE)m_valVariant.m_datatype.getValue();
}

QString MetadataColumn::getName() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return m_name.getValue();
}

void MetadataColumn::setNull(const bool toNull, const bool upd)
{
    LogFuncionBegin;

    m_isNull.setValue(toNull);
    if (upd)
    {
        setUpdated();
    }

    LogFuncionEnd;
}

void MetadataColumn::setNone()
{
    LogFuncionBegin;

    m_status.setValue(E_TC_STAT_NONE);

    LogFuncionEnd;
}

void MetadataColumn::setLoaded()
{
    LogFuncionBegin;

    m_status.setValue(E_TC_STAT_LOADED);

    LogFuncionEnd;
}

void MetadataColumn::setUpdated()
{
    LogFuncionBegin;

    m_status.setValue(E_TC_STAT_UPDATED);

    LogFuncionEnd;
}

bool MetadataColumn::isNull() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return m_isNull.getValue();
}

bool MetadataColumn::isNone() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return (m_status.getValue() == E_TC_STAT_NONE);
}

bool MetadataColumn::isLoaded() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return (m_status.getValue() == E_TC_STAT_LOADED);
}

bool MetadataColumn::isUpdated() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return (m_status.getValue() == E_TC_STAT_UPDATED);
}

bool MetadataColumn::setValue(const signed char val, const bool upd)
{
    LogFuncionBegin;

    if (m_valVariant.m_datatype.getValue() == E_CT_BYTE)
    {
        setNull(false);
        m_valVariant.m_valByte = val;
        if (upd)
        {
            setUpdated();
        }
    }
    return (m_valVariant.m_datatype.getValue() == E_CT_BYTE);

    LogFuncionEnd;
}

bool MetadataColumn::setValue(const bool val, const bool upd)
{
    LogFuncionBegin;

    if (m_valVariant.m_datatype.getValue() == E_CT_BOOLEAN)
    {
        setNull(false);
        m_valVariant.m_valBool = val;
        if (upd)
        {
            setUpdated();
        }
    }

    LogFuncionEnd;

    return (m_valVariant.m_datatype.getValue() == E_CT_BOOLEAN);
}

bool MetadataColumn::setValue(const double val, const bool upd)
{
    LogFuncionBegin;

    if (m_valVariant.m_datatype.getValue() == E_CT_DOUBLE)
    {
        setNull(false);
        m_valVariant.m_valDouble = val;
        if (upd)
        {
            setUpdated();
        }
    }

    LogFuncionEnd;

    return (m_valVariant.m_datatype.getValue() == E_CT_DOUBLE);
}

bool MetadataColumn::setValue(const float val, const bool upd)
{
    LogFuncionBegin;

    if (m_valVariant.m_datatype.getValue() == E_CT_FLOAT)
    {
        setNull(false);
        m_valVariant.m_valFloat = val;
        if (upd)
        {
            setUpdated();
        }
    }

    LogFuncionEnd;

    return (m_valVariant.m_datatype.getValue() == E_CT_FLOAT);
}

bool MetadataColumn::setValue(const int val, const bool upd)
{
    LogFuncionBegin;

    if (m_valVariant.m_datatype.getValue() == E_CT_INT)
    {
        setNull(false);
        m_valVariant.m_valInt = val;
        if (upd)
        {
            setUpdated();
        }
    }

    LogFuncionEnd;

    return (m_valVariant.m_datatype.getValue() == E_CT_INT);
}

bool MetadataColumn::setValue(const short int val, const bool upd)
{
    LogFuncionBegin;

    if (m_valVariant.m_datatype.getValue() == E_CT_SHORT)
    {
        setNull(false);
        m_valVariant.m_valShortInt = val;
        if (upd)
        {
            setUpdated();
        }
    }

    LogFuncionEnd;

    return (m_valVariant.m_datatype.getValue() == E_CT_SHORT);
}

bool MetadataColumn::setValue(const long val, const bool upd)
{
    LogFuncionBegin;

    if (m_valVariant.m_datatype.getValue() == E_CT_LONG)
    {
        setNull(false);
        m_valVariant.m_valLong = val;
        if (upd)
        {
            setUpdated();
        }
    }

    LogFuncionEnd;

    return (m_valVariant.m_datatype.getValue() == E_CT_LONG);
}

bool MetadataColumn::setValue(const QString & val, const bool upd)
{
    LogFuncionBegin;

    bool retVal = false;

    switch (m_valVariant.m_datatype.getValue())
    {
    case MetadataColumn::E_CT_STRING:
    case MetadataColumn::E_CT_DATE:
    case MetadataColumn::E_CT_TIME:
    case MetadataColumn::E_CT_TIMESTAMP:
        setNull(false);
        m_valVariant.m_valStr = val;
        retVal = true;
        if (upd)
        {
            setUpdated();
        }
        break;
    default:
        retVal = false;
        break;
    }

    LogFuncionEnd;

    return retVal;
}

bool MetadataColumn::getValue(bool *val) const
{
    LogFuncionBegin;

    bool retVal = false;

    if (m_valVariant.m_datatype.getValue() == E_CT_BOOLEAN)
    {
        *val = m_valVariant.m_valBool;
        retVal = true;
    }

    LogFuncionEnd;

    return retVal;
}

bool MetadataColumn::getValue(signed char *val) const
{
    LogFuncionBegin;

    bool retVal = false;

    if (m_valVariant.m_datatype.getValue() == E_CT_BYTE)
    {
        *val = m_valVariant.m_valByte;
        retVal = true;
    }

    LogFuncionEnd;

    return retVal;
}

bool MetadataColumn::getValue(double *val) const
{
    LogFuncionBegin;

    bool retVal = false;

    if (m_valVariant.m_datatype.getValue() == E_CT_DOUBLE)
    {
        *val = m_valVariant.m_valDouble;
        retVal = true;
    }

    LogFuncionEnd;

    return retVal;
}

bool MetadataColumn::getValue(float *val) const
{
    LogFuncionBegin;

    bool retVal = false;

    if (m_valVariant.m_datatype.getValue() == E_CT_FLOAT)
    {
        *val = m_valVariant.m_valFloat;
        retVal = true;
    }

    LogFuncionEnd;

    return retVal;
}

bool MetadataColumn::getValue(int *val) const
{
    LogFuncionBegin;

    bool retVal = false;

    if (m_valVariant.m_datatype.getValue() == E_CT_INT)
    {
        *val = m_valVariant.m_valInt;
        retVal = true;
    }

    LogFuncionEnd;

    return retVal;
}

bool MetadataColumn::getValue(long *val) const
{
    LogFuncionBegin;

    bool retVal = false;

    if (m_valVariant.m_datatype.getValue() == E_CT_LONG)
    {
        *val = m_valVariant.m_valLong;
        retVal = true;
    }

    LogFuncionEnd;

    return retVal;
}

bool MetadataColumn::getValue(short int *val) const
{
    LogFuncionBegin;

    bool retVal = false;

    if (m_valVariant.m_datatype.getValue() == E_CT_SHORT)
    {
        *val = m_valVariant.m_valShortInt;
        retVal = true;
    }

    LogFuncionEnd;

    return retVal;
}

bool MetadataColumn::getValue(QString *val) const
{
    LogFuncionBegin;

    bool retVal = false;

    switch (m_valVariant.m_datatype.getValue())
    {
    case MetadataColumn::E_CT_STRING:
    case MetadataColumn::E_CT_DATE:
    case MetadataColumn::E_CT_TIME:
    case MetadataColumn::E_CT_TIMESTAMP:
        *val = eraseInvalidCharacters(m_valVariant.m_valStr);
        retVal = true;
        break;
    default:
        retVal = false;
        break;
    }

    LogFuncionEnd;

    return retVal;
}

QString MetadataColumn::getValue() const
{
    LogFuncionBegin;

    QString sstr;

    if (isNull())
    {
        sstr = "NULL";
    }
    else
    {
        switch (m_valVariant.m_datatype.getValue())
        {
            case MetadataColumn::E_CT_BOOLEAN:
                sstr = QString("%1").arg(m_valVariant.m_valBool);
                break;
            case MetadataColumn::E_CT_BYTE:
                sstr = QString("%1").arg(m_valVariant.m_valByte);
                break;
            case MetadataColumn::E_CT_DOUBLE:
                sstr = QString("%1").arg(m_valVariant.m_valDouble);
                break;
            case MetadataColumn::E_CT_FLOAT:
                sstr = QString("%1").arg(m_valVariant.m_valFloat);
                break;
            case MetadataColumn::E_CT_INT:
                sstr = QString("%1").arg(m_valVariant.m_valInt);
                break;
            case MetadataColumn::E_CT_LONG:
                sstr = QString("%1").arg(m_valVariant.m_valLong);
                break;
            case MetadataColumn::E_CT_SHORT:
                sstr = QString("%1").arg(m_valVariant.m_valShortInt);
                break;
            case MetadataColumn::E_CT_STRING:
            case MetadataColumn::E_CT_DATE:
            case MetadataColumn::E_CT_TIME:
            case MetadataColumn::E_CT_TIMESTAMP:
                sstr = QString("'%1'").arg(eraseInvalidCharacters(m_valVariant.m_valStr));
                break;
            default:
                sstr = " ";
                break;
        }
    }

    LogFuncionEnd;

    return sstr;
}

QString MetadataColumn::eraseInvalidCharacters(const QString & src) const
{
    LogFuncionBegin;

	char chr = 0;
    QString retStr = "";

	retStr.reserve(src.size());

    for (unsigned int idx = 0; idx < (unsigned int)src.size(); idx++)
    {
        chr = src.toStdString().at(idx);
        if (chr != '\'' && chr != '\"')
        {
            retStr += chr;
        }
    }

    LogFuncionEnd;

    return retStr;
}

void MetadataColumn::createDeserializeList()
{
    LogFuncionBegin;

    m_vDeserializeObjects.clear();
    addDeserializeObject(&m_status);
    addDeserializeObject(&m_name);
    addDeserializeObject(&m_isNull);
    addDeserializeObject(&m_valVariant);

    LogFuncionEnd;
}

void MetadataColumn::createSerializeList()
{
    LogFuncionBegin;

    m_lstSerializeObjects.clear();
    addSerializeObject(&m_status, "status");
    addSerializeObject(&m_name, "name");
    addSerializeObject(&m_isNull, "isNull");
    addSerializeObject(&m_valVariant, "Variant");

    LogFuncionEnd;
}
