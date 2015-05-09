#ifndef DataVariantSerialize_H_
#define DataVariantSerialize_H_

#include <QtCore/QVariant>

#include "xml/mainserialize.h"
#include "xml/data/intserialize.h"

/**
 * @brief Class DataVariantSerialize is used to serialize / deserialize
 *        variant element. From nested variables is serialized just one,
 *        depend on type
 * */
class DataVariantSerialize : public MainSerialize
{
public:

    /**
     * @brief default constructor
     * */
    DataVariantSerialize();

    /**
     * @brief default destructor
     * */
    virtual ~DataVariantSerialize();

    /**
     * @brief responsible for correct variant > string serialization
     * */
    virtual QString serialize();

    /**
     * @brief responsible for correct string > variant deserialization
     * */
    virtual void setXMLValue(const QString & sValue);
    virtual void setXMLValue(const QString & sValue, const int & intType);

    /**
     * @brief is called to create list of objects for deserialization
     * */
    virtual void createDeserializeList();

    /**
     * @brief is called to create list of objects for serialization
     * */
    virtual void createSerializeList();

    /**
     * @brief deserialize XmlNode structure in m_pCurrentXmlNode into objects
     * */
    //virtual bool deserializeObject(DeserializeXml* pDeserializeObj, XmlNode* pXmlNode);

    /**
     * @brief necessary for internal deserialization process
     * */
    //bool m_bFirstAlreadyCalled;

    QVariant getValue() const { return varValue_; }
    void setValue(const QVariant & varValue) { varValue_ = varValue; }
    void setValue(const int & intValue) { varValue_.setValue(intValue); }
    void setValue(const QString & strValue) { varValue_.setValue(strValue); }

private:
    QVariant varValue_;
};

#endif /* DataVariantSerialize_H_ */
