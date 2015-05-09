#ifndef StringSerialize_H_
#define StringSerialize_H_

#include "xml/serializexml.h"
#include "xml/deserializexml.h"

/**
 * @brief Class StringSerialize is used to serialize / deserialize
 *        string element
 * */
class StringSerialize : public SerializeXml, public DeserializeXml
{
public:
    /**
     * @brief default constructor
     * */
    StringSerialize();
    StringSerialize(QString str);

    /**
     * @brief default constructor
     * */
    virtual ~StringSerialize();

    /**
     * @brief set string value
     * */
    void setValue(const QString & sValue) { m_sValue = sValue; }

    /**
     * @brief get string value
     * */
    QString getValue() const { return m_sValue; }

    /**
     * @brief responsible for correct string > string serialization
     * */
    virtual QString serialize();

    /**
     * @brief responsible for correct string > string deserialization
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
    QString m_sValue;
};

#endif /* StringSerialize_H_ */
