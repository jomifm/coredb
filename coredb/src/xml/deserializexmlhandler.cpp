#include "xml/deserializexmlhandler.h"
#include "utils/logger/utilslogger.h"

DeserializeXmlHandler::DeserializeXmlHandler()
    : m_oXML(NULL)
{
    LogFuncionBegin;

    m_sLastElementText = "";
    m_pCurrentXmlNode = &m_oXML;

    LogFuncionEnd;
}

DeserializeXmlHandler::~DeserializeXmlHandler()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

bool DeserializeXmlHandler::characters ( const QString & ch )
{
    LogFuncionBegin;

    m_sLastElementText += ch;

    LogFuncionEnd;

    return true;
}

bool DeserializeXmlHandler::startElement (const QString &, const QString &,
                                          const QString &, const QXmlAttributes &atts)
{
    LogFuncionBegin;

    //Add child node
    m_pCurrentXmlNode = m_pCurrentXmlNode->addChild();
    m_sLastElementText = "";

    //Obtiene los atributos del nodo xml
    for (int i = 0; i < atts.count(); i++)
        m_pCurrentXmlNode->addAttribute(atts.localName(i), atts.value(i));

    LogFuncionEnd;

    return true;
}

bool DeserializeXmlHandler::endElement (const QString &, const QString &, const QString &)
{
    LogFuncionBegin;

    m_pCurrentXmlNode->setValue(m_sLastElementText);
    m_pCurrentXmlNode = m_pCurrentXmlNode->getParent();
    m_sLastElementText = "";

    LogFuncionEnd;

    return true;
}

bool DeserializeXmlHandler::error(const QXmlParseException & exception)
{
    LogFuncionBegin;

    LogError() << "DeserializeXmlHandler::error";
    LogError() << "XML parse error: " << exception.message()
             << "Line: " << exception.lineNumber()
             << "Column: " << exception.columnNumber();

//    std::stringstream ss;
//    ss << "XML parse error: " << exception.message().toStdString() << "Line: " <<
//                 exception.lineNumber() << "Column: " << exception.columnNumber();
//    C_Logger::WriteLog(LOG_TMCS_ERROR, MODUL_OTHERS, "DeserializeXmlHandler",
//                       EXCEPTION_MSG_ADD(E_TMCS_RT_ERROR, ss.str()));

    LogFuncionEnd;

    return true;
}

bool DeserializeXmlHandler::fatalError(const QXmlParseException & exception)
{
    LogFuncionBegin;

    LogError() << "DeserializeXmlHandler::fatalError";
    LogError() << "XML parse error: " << exception.message()
             << "Line: " << exception.lineNumber()
             << "Column: " << exception.columnNumber();

//    std::stringstream ss;
//    ss << "XML parse error: " << exception.message().toStdString() << "Line: " <<
//                 exception.lineNumber() << "Column: " << exception.columnNumber();
//    C_Logger::WriteLog(LOG_TMCS_ERROR, MODUL_OTHERS, "DeserializeXmlHandler",
//                       EXCEPTION_MSG_ADD(E_TMCS_RT_ERROR, ss.str()));

    LogFuncionEnd;

    return true;
}
