#ifndef VectorTableSerialize_H_
#define VectorTableSerialize_H_

#include "xml/mainserialize.h"
#include "xml/data/intserialize.h"

/**
 * @brief Class VectorColumnSerialize is used to serialize / deserialize
 *        vector element
 * */
class MetadataTable;
class VectorTableSerialize : public MainSerialize
{
public:
    /**
     * @brief default constructor
     * */
    VectorTableSerialize();

    /**
     * @brief default constructor
     * */
    virtual ~VectorTableSerialize();

    /**
     * @brief set pointer to vector<MetadataTable*>
     * */
    void setValue(QVector<MetadataTable *> *pValue) { m_pValue = pValue; }

    /**
     * @brief get pointer to vector<MetadataTable *>
     * */
    QVector<MetadataTable *>* getValue() const { return m_pValue; }

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

    QVector<MetadataTable *> *m_pValue;
};

#endif /* VectorTableSerialize_H_ */
