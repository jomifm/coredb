#include "xml/serializexml.h"
#include "xml/deserializexml.h"

#ifndef BoolSerialize_H_
#define BoolSerialize_H_

/**
 * @brief Class BoolSerialize is used to serialize / deserialize
 *        boolean element
 * */
class BoolSerialize : public SerializeXml, public DeserializeXml
{
public:
    /**
     * @brief default constructor
     * */
    BoolSerialize();

    /**
     * @brief default destructor
     * */
    virtual ~BoolSerialize();

    /**
     * @brief set boolean value
     * */
    void setValue(const bool bValue) { m_bValue = bValue; }

    /**
     * @brief get boolean value
     * */
    bool getValue() const { return m_bValue; }

    /**
     * @brief responsible for correct bool > string serialization
     * */
    virtual QString serialize();

    /**
     * @brief responsible for correct string > bool deserialization
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
    bool m_bValue;
};

#endif /* BoolSerialize_H_ */
