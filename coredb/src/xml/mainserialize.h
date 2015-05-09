#ifndef MainSerialize_H_
#define MainSerialize_H_

#include "xml/serializexml.h"
#include "xml/deserializexml.h"

/**
 * @brief Class MainSerialize is used to implement (hide)
 *        necessary serialize / deserialize implementation
 * */
class MainSerialize : public SerializeXml, public DeserializeXml
{

public:
    //enum E_TABLE_ACTION {
    //	TABLE_ORIGINAL,
    //	TABLE_CREATE,
    //	TABLE_MODIFY,
    //	TABLE_DELETE
    //};

public:
    /**
     * @brief default constructor
     * */
    MainSerialize();

    /**
     * @brief default constructor
     * */
    virtual ~MainSerialize();

    /**
     * @brief do nothing here
     * */
    virtual void createDeserializeList();

    /**
     * @brief do nothing here
     * */
    virtual void createSerializeList();
};

#endif /* MainSerialize_H_ */
