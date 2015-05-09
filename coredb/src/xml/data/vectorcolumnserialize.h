#ifndef VectorColumnSerialize_H_
#define VectorColumnSerialize_H_

#include "xml/mainserialize.h"
#include "xml/data/intserialize.h"

/**
 * @brief Class VectorColumnSerialize is used to serialize / deserialize
 *        vector element
 * */
class MetadataColumn;
class VectorColumnSerialize : public MainSerialize
{
public:
    /**
     * @brief default constructor
     * */
    VectorColumnSerialize();

    /**
     * @brief default constructor
     * */
    virtual ~VectorColumnSerialize();

    /**
     * @brief set pointer to vector<MetadataColumn *>
     * */
    void setValue(QVector<MetadataColumn *> *pValue) { m_pValue = pValue; }

    /**
     * @brief get pointer to vector<MetadataColumn *>
     * */
    QVector<MetadataColumn *>* getValue() const { return m_pValue; }

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

    QVector<MetadataColumn *> *m_pValue;
};

#endif /* VectorColumnSerialize_H_ */
