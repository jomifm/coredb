#ifndef VariantSerialize_H_
#define VariantSerialize_H_

#include "xml/mainserialize.h"
#include "xml/data/intserialize.h"

/**
 * @brief Class VariantSerialize is used to serialize / deserialize
 *        variant element. From nested variables is serialized just one,
 *        depend on type
 * */
class VariantSerialize : public MainSerialize
{
public:

    /**
     * @brief default constructor
     * */
    VariantSerialize();

    /**
     * @brief default destructor
     * */
    virtual ~VariantSerialize();

    /**
     * @brief responsible for correct variant > string serialization
     * */
    virtual QString serialize();

    /**
     * @brief responsible for correct string > variant deserialization
     * */
    virtual void setXMLValue (const QString & sValue) { Q_UNUSED(sValue) }

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
    virtual bool deserializeObject(DeserializeXml* pDeserializeObj, XmlNode* pXmlNode);

    /**
     * @brief necessary for internal deserialization process
     * */
    //bool m_bFirstAlreadyCalled;


    IntSerialize m_datatype; /*enum E_COLUMN_TYPE*/

    QString m_valStr;
    union
    {
        bool m_valBool;
        signed char m_valByte;
        double m_valDouble;
        float m_valFloat;
        int m_valInt;
        long m_valLong;
        short int m_valShortInt;
    };
};

#endif /* VariantSerialize_H_ */
