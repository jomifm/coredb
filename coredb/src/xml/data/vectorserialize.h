#ifndef VectorSerialize_H_
#define VectorSerialize_H_

#include "xml/serializexml.h"
#include "xml/deserializexml.h"
#include "xml/data/intserialize.h"

/**
 * @brief Class VectorSerialize is used to serialize / deserialize
 *        vector element
 * */
//template<class TTT>
class VectorSerialize : public SerializeXml, public DeserializeXml
{
public:
    /**
     * @brief default constructor
     * */
    VectorSerialize();

    /**
     * @brief default constructor
     * */
    virtual ~VectorSerialize();

    /**
     * @brief set pointer to vector<IntSerialize>
     * */
    void setValue(QVector<IntSerialize> *pValue) { m_pValue = pValue; }

    /**
     * @brief get pointer to vector<IntSerialize>
     * */
    QVector<IntSerialize>* getValue() const { return m_pValue; }

    /**
     * @brief responsible for correct vector > string serialization
     * */
    virtual QString serialize();//required from SerializeXml

    /**
     * @brief responsible for correct string > vector deserialization
     * */
    virtual void setXMLValue(const QString & sValue);//required from DeserializeXml

    /**
     * @brief do nothing here
     * */
    virtual void createSerializeList();

    /**
     * @brief do nothing here
     * */
    virtual void createDeserializeList();

    QVector<IntSerialize> *m_pValue;
};

#endif /* VectorSerialize_H_ */
