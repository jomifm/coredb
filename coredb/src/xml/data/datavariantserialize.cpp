#include "xml/data/datavariantserialize.h"
#include "utils/logger/utilslogger.h"

DataVariantSerialize::DataVariantSerialize()
{
    LogFuncionBegin;

    //m_bFirstAlreadyCalled = false;
    varValue_.setValue(QString(""));

    LogFuncionEnd;
}

DataVariantSerialize::~DataVariantSerialize()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

void DataVariantSerialize::createDeserializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

void DataVariantSerialize::createSerializeList()
{
    LogFuncionBegin;
    //no nested objects
    LogFuncionEnd;
}

QString DataVariantSerialize::serialize()
{
    LogFuncionBegin;

    QString sRetValue = "";
    QString sValue = "";
    QString sSerializationName = getSerializationName();
    char buf[20];

    // begin XML element
    sRetValue.append("<data");
    if (!sSerializationName.isEmpty())
        sRetValue.append(QString(" name=\"%1\"").arg(sSerializationName));
    if (varValue_.type() > 0 && varValue_.type() != QVariant::String)
        sRetValue.append(QString(" type=\"%1\"").arg(varValue_.type()));
    sRetValue.append(">");

    switch (varValue_.type())
    {
        case QVariant::Bool:
            sValue = "true";
            if (varValue_.toBool() == false) {
                sValue = "false";
            }
            break;
        case QVariant::Double:
            snprintf(buf, 20, "%lf", varValue_.toDouble());
            sValue.append(buf);
            break;
        case QVariant::Int:
            snprintf(buf, 20, "%d", varValue_.toInt());
            sValue.append(buf);
            break;
        case QVariant::LongLong:
            snprintf(buf, 20, "%ld", (long int)varValue_.toLongLong());
            sValue.append(buf);
            break;
        case QVariant::String:
            sValue = serializeSpecialChars(varValue_.toString());
            break;
        default:
            break;
    }

    sRetValue.append(sValue);

    // end XML element
    sRetValue.append("</");
    sRetValue.append("data");
    sRetValue.append(">");

    LogFuncionEnd;

    return sRetValue;
}

void DataVariantSerialize::setXMLValue(const QString & newValue)
{
    LogFuncionBegin;

    varValue_.setValue(deserializeSpecialChars(newValue));

    LogFuncionEnd;
}

void DataVariantSerialize::setXMLValue(const QString & sValue, const int & intType)
{
    LogFuncionBegin;

    const QString strValue = deserializeSpecialChars(sValue);

    if (intType == QVariant::Bool) varValue_.setValue(strValue == QString("true")? true:false);
    else if (intType == QVariant::Double) varValue_.setValue(strValue.toDouble());
    else if (intType == QVariant::Int) varValue_.setValue(strValue.toInt());
    else if (intType == QVariant::LongLong) varValue_.setValue(strValue.toLongLong());
    else if (intType == QVariant::String) varValue_.setValue(deserializeSpecialChars(strValue));
    else varValue_.clear();

    LogFuncionEnd;
}
