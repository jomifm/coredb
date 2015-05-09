#ifndef VectorStringSerialize_H_
#define VectorStringSerialize_H_

#include "xml/serializexml.h"
#include "xml/deserializexml.h"

/**
 * @brief Class VectorStringSerialize is used to serialize / deserialize
 *        vector element
 * */
class VectorStringSerialize : public SerializeXml, public DeserializeXml
{
public:
    /**
     * @brief default constructor
     * */
    VectorStringSerialize();

    /**
     * @brief default constructor
     * */
    virtual ~VectorStringSerialize();

    /**
     * @brief set pointer to vector<string>
     * */
    void  setValue(QVector<QString> *pValue) { m_pValue = pValue; }

    /**
     * @brief get pointer to vector<string>
     * */
    QVector<QString>* getValue() const { return m_pValue; }

    /**
     * @brief responsible for correct vector > string serialization
     * */
    virtual QString serialize();

    /**
     * @brief responsible for correct string > vector deserialization
     * */
    virtual void setXMLValue(const QString & sValue);

    /**
     * @brief do nothing here
     * */
    virtual void createSerializeList();

    /**
     * @brief do nothing here
     * */
    virtual void createDeserializeList();

    /**
     * @brief deserialize XmlNode structure in m_pCurrentXmlNode into objects
     * */
    virtual bool deserializeObject(DeserializeXml* pDeserializeObj, XmlNode* pXmlNode);

    QVector<QString> *m_pValue;
};

#endif /* VectorStringSerialize_H_ */
