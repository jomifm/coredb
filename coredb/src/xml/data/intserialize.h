#ifndef IntSerialize_H_
#define IntSerialize_H_

#include "xml/serializexml.h"
#include "xml/deserializexml.h"

/**
 * @brief Class IntSerialize is used to serialize / deserialize
 *        int element
 * */
class IntSerialize : public SerializeXml, public DeserializeXml
{
public:
    /**
     * @brief default constructor
     * */
    IntSerialize();

    /**
     * @brief default destructor
     * */
    virtual ~IntSerialize();

    /**
     * @brief set integer value
     * */
    void setValue(const int iValue) { m_iValue = iValue; }
    /**
     * @brief get integer value
     * */
    int getValue() const { return m_iValue; }

    /**
     * @brief responsible for correct int > string serialization
     * */
    virtual QString serialize();

    /**
     * @brief responsible for correct string > int deserialization
     * */
    virtual void setXMLValue(const QString & sValue);

    /**
     * @brief do nothing here
     * */
    virtual void createDeserializeList();

    /**
     * @brief do nothing here
     * */
    virtual void createSerializeList();

protected:
    int m_iValue;
};

#endif /* IntSerialize_H_ */
