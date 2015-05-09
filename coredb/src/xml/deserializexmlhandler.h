#ifndef DeserializeXmlHandler_H_
#define DeserializeXmlHandler_H_

#include <QXmlDefaultHandler>

#include "xml/deserializexml.h"
#include "xml/xmlnode.h"


/**
 * @brief Class DeserializeXmlHandler is handler class used to handle
 *        deserialization events in SAX XML parser
 *        like startElement, characters, endElement
 * */
class DeserializeXmlHandler : public QXmlDefaultHandler
{
public:
    /**
     * @brief default constructor
     * */
    DeserializeXmlHandler();

    /**
     * @brief default destructor
     * */
    virtual ~DeserializeXmlHandler();

    /**
     * @brief startElement XML event
     * */
    virtual bool startElement (const QString & namespaceURI, const QString & localName,
                               const QString & qName, const QXmlAttributes & atts);

    /**
     * @brief characters (or node value) XML event
     * */
    virtual bool characters ( const QString & ch );

    /**
     * @brief endElement XML event
     * */
    virtual bool endElement (const QString & namespaceURI,
                             const QString & localName, const QString & qName );

    virtual bool error (const QXmlParseException & exception);
    virtual bool fatalError (const QXmlParseException & exception);

    XmlNode* getXml() { return &m_oXML; }

private:
    /* holds currently processing node value */
    QString m_sLastElementText;

    /* holds XmlNode representation of parsed XML*/
    XmlNode m_oXML;

    /* pointer to processing xml node */
    XmlNode *m_pCurrentXmlNode;

};

#endif /* DeserializeXmlHandler_H_ */
