#ifndef VectorRowSerialize_H_
#define VectorRowSerialize_H_

#include "xml/mainserialize.h"

/**
 * @brief Class VectorColumnSerialize is used to serialize / deserialize
 *        vector element
 * */
class MetadataRow;
class VectorRowSerialize : public MainSerialize
{
public:
    /**
     * @brief default constructor
     * */
    VectorRowSerialize();

    /**
     * @brief default constructor
     * */
    virtual ~VectorRowSerialize();

    /**
     * @brief set pointer to vector<MetadataRow *>
     * */
    void setValue(QVector<MetadataRow *> *pValue) { m_pValue = pValue; }

    /**
     * @brief get pointer to vector<MetadataColumn *>
     * */
    QVector<MetadataRow *>* getValue() const { return m_pValue; }

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

    QVector<MetadataRow *> *m_pValue;
};

#endif /* VectorRowSerialize_H_ */
