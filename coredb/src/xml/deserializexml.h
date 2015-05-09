#ifndef DeserializeXml_H_
#define DeserializeXml_H_

#include <QtCore/QVector>

#include "xml/xmlnode.h"

/**
 * @brief Class DeserializeXml is main parent class used to deserialize
 *        inherited classes
 * */
class DeserializeXml
{
public:
    /**
     * @brief default constructor
     * */
    DeserializeXml();

    /**
     * @brief default destructor
     * */
    virtual ~DeserializeXml();

    /**
     * @brief called by deserialization class
     * for identification of deserialzation objects
     * */
    void addDeserializeObject(DeserializeXml* oObject);

    /**
     * @brief entry call for class deserialization
     * */
    bool deserializeAll(const QString & sXML);

    /**
     * @brief return vector of deserialization objects
     * */
    QVector<DeserializeXml*>* getDeserializeObjects() { return &m_vDeserializeObjects; }

    /**
     * @brief responsible for correct string > object deseralization
     * */
    virtual void setXMLValue(const QString & sValue);

    /**
     * @brief responsible for correct string > object deseralization
     * */
    virtual void setXMLValue(const QString & sValue, const int & intType);

    /**
     * @brief is called to create list of objects for deseralization
     * */
    virtual void createDeserializeList();

    /**
     * @brief deserialize XmlNode structure in m_pCurrentXmlNode into objects
     * */
    virtual bool deserializeObject(DeserializeXml* pDeserializeObj, XmlNode* pXmlNode);

    XmlNode m_oXML;
    XmlNode *m_pCurrentXmlNode;

protected:
    /* list of objects to deserialize */
    QVector<DeserializeXml*>  m_vDeserializeObjects;

    QString deserializeSpecialChars(const QString & pString);
};


#endif /* DeserializeXml_H_ */
