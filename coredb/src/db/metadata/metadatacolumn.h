#ifndef MetadataColumn_H_
#define MetadataColumn_H_

#include "xml/data/stringserialize.h"
#include "xml/data/intserialize.h"
#include "xml/data/boolserialize.h"
#include "xml/data/variantserialize.h"
#include "xml/mainserialize.h"

/**
 * @brief Class provides services to handle table column data and operations
 * */
class MetadataColumn : public MainSerialize
{
public:
    /**
     * @brief Supported column data types
     * */
    enum E_COLUMN_TYPE
    {
        /** Column data type BOOLEAN */
        E_CT_BOOLEAN,
        /** Column data type BYTE */
        E_CT_BYTE,
        /** Column data type DOUBLE */
        E_CT_DOUBLE,
        /** Column data type FLOAT */
        E_CT_FLOAT,
        /** Column data type INT */
        E_CT_INT,
        /** Column data type LONG */
        E_CT_LONG,
        /** Column data type SHORT */
        E_CT_SHORT,
        /** Column data type STRING */
        E_CT_STRING,
        /** Column data type DATE (underlying type is string) */
        E_CT_DATE,
        /** Column data type TIME */
        E_CT_TIME,
        /** Column data type TIMESTAMP */
        E_CT_TIMESTAMP
    };

    /**
     * @brief Possible column statuses
     * */
    enum E_COLUMN_STATUS
    {
        /** Column without data assigned */
        E_TC_STAT_NONE,
        /** Column with set value */
        E_TC_STAT_LOADED,
        /** Column with updated value */
        E_TC_STAT_UPDATED
    };

public:
    /**
     * @brief Constructor to create table column object with the name and data
     * type.
     *
     * Table row is created with specified name and data type. These column
     * properties are not modifiable.
     *
     * @param colName IN : Table column name
     * @param dataType IN : Table column data type
     * */
    MetadataColumn(const QString & colName, const MetadataColumn::E_COLUMN_TYPE dataType);
    /**
     * @brief Default destructor
     * */
    virtual ~MetadataColumn();
    /**
     * @brief Returns column data type.
     *
     * @return Returns column data type
     * */
    MetadataColumn::E_COLUMN_TYPE getDatatype() const;
    /**
     * @brief Returns column name
     *
     * @return Returns column name
     * */
    QString getName() const;

    /**
     * @brief Set column value to NULL/notNULL
     *
     * @param toNull IN: if true set column value to NULL, otherwise set column
     * to not NULL
     * */
    void setNull(const bool toNull, bool const upd=true);
    /**
     * @brief Set column status to "None". It means empty column without
     * data loaded.
     * */
    void setNone();
    /**
     * @brief Set column status to "Loaded". It means column has data loaded.
     * */
    void setLoaded();
    /**
     * @brief Set column status to "Updated". It means column has data are
     * updated.
     * */
    void setUpdated();
    /**
     * @brief Check if column value is NULL
     *
     * @return true if column value is NULL, otherwise returns false
     * */
    bool isNull() const;
    /**
     * @brief Check if column value is set or not
     *
     * @return true if column value is not set, otherwise returns false
     * */
    bool isNone() const;
    /**
     * @brief Check if column value is set or not
     *
     * @return true if column value is set, otherwise returns false
     * */
    bool isLoaded() const;
    /**
     * @brief Check if column value is updated
     *
     * @return true if column value is updated, otherwise returns false
     * */
    bool isUpdated() const;
    /**
     * @brief Set column BOOLEAN value to value of input parameter.
     *
     * If column data type doesn't correspond to input parameter data type, then
     * value is not set and method returns false.
     *
     * @return true if column value is successfully, otherwise returns false
     * */
    bool setValue(const bool val, const bool upd=true);
    /**
     * @brief Set column BYTE value to value of input parameter.
     *
     * If column data type doesn't correspond to input parameter data type, then
     * value is not set and method returns false.
     *
     * @return true if column value is successfully, otherwise returns false
     * */
    bool setValue(const signed char val, const bool upd=true);
    /**
     * @brief Set column DOUBLE value to value of input parameter.
     *
     * If column data type doesn't correspond to input parameter data type, then
     * value is not set and method returns false.
     *
     * @return true if column value is successfully, otherwise returns false
     * */
    bool setValue(const double val, const bool upd=true);
    /**
     * @brief Set column FLOAT value to value of input parameter.
     *
     * If column data type doesn't correspond to input parameter data type, then
     * value is not set and method returns false.
     *
     * @return true if column value is successfully, otherwise returns false
     * */
    bool setValue(const float val, const bool upd=true);
    /**
     * @brief Set column INT value to value of input parameter.
     *
     * If column data type doesn't correspond to input parameter data type, then
     * value is not set and method returns false.
     *
     * @return true if column value is successfully, otherwise returns false
     * */
    bool setValue(const int val, const bool upd=true);
    /**
     * @brief Set column LONG value to value of input parameter.
     *
     * If column data type doesn't correspond to input parameter data type, then
     * value is not set and method returns false.
     *
     * @return true if column value is successfully, otherwise returns false
     * */
    bool setValue(const long val, const bool upd=true);
    /**
     * @brief Set column SHORT value to value of input parameter.
     *
     * If column data type doesn't correspond to input parameter data type, then
     * value is not set and method returns false.
     *
     * @return true if column value is successfully, otherwise returns false
     * */
    bool setValue(const short int val, const bool upd=true);
    /**
     * @brief According to column data type copy input parameter value to
     * associated column data item
     *
     * If column data type doesn't correspond to input parameter data type, then
     * value is not set and method returns false. The following data types are
     * accepted as string: STRING, DATE, TIME and TIMESTAMP.
     *
     * @return true if column value is successfully, otherwise returns false
     * */
    bool setValue(const QString & val, const bool upd=true);

    /**
     * @brief Get column value if column data type is BOOLEAN.
     *
     * @param val OUT: Pointer to output parameter of appropriate data type
     *
     * @return true if output value is set successfully, otherwise returns false
     * */
    bool getValue(bool * val) const;
    /**
     * @brief Get column value if column data type is BYTE.
     *
     * @param val OUT: Pointer to output parameter of appropriate data type
     *
     * @return true if output value is set successfully, otherwise returns false
     * */
    bool getValue(signed char * val) const;
    /**
     * @brief Get column value if column data type is DOUBLE.
     *
     * @param val OUT: Pointer to output parameter of appropriate data type
     *
     * @return true if output value is set successfully, otherwise returns false
     * */
    bool getValue(double * val) const;
    /**
     * @brief Get column value if column data type is FLOAT.
     *
     * @param val OUT: Pointer to output parameter of appropriate data type
     *
     * @return true if output value is set successfully, otherwise returns false
     * */
    bool getValue(float * val) const;
    /**
     * @brief Get column value if column data type is INT.
     *
     * @param val OUT: Pointer to output parameter of appropriate data type
     *
     * @return true if output value is set successfully, otherwise returns false
     * */
    bool getValue(int * val) const;
    /**
     * @brief Get column value if column data type is LONG.
     *
     * @param val OUT: Pointer to output parameter of appropriate data type
     *
     * @return true if output value is set successfully, otherwise returns false
     * */
    bool getValue(long * val) const;
    /**
     * @brief Get column value if column data type is SHORT.
     *
     * @param val OUT: Pointer to output parameter of appropriate data type
     *
     * @return true if output value is set successfully, otherwise returns false
     * */
    bool getValue(short int * val) const;
    /**
     * @brief Get column value if column data type is STRING, DATE, TIME or
     * TIMESTAMP.
     *
     * @param val OUT: Pointer to output parameter of appropriate data type
     *
     * @return true if output value is set successfully, otherwise returns false
     * */
    bool getValue(QString * val) const;

    /**
     * @brief Return column data converted to string
     * */
    QString getValue() const;

    /* Serialization functions */

    /**
     * @brief is called to create list of objects for deserialization
     * */
    virtual void   createDeserializeList();

    /**
     * @brief is called to create list of objects for serialization
     * */
    virtual void   createSerializeList();

private:
    IntSerialize m_status; /*enum E_COLUMN_STATUS*/
    StringSerialize m_name;
    BoolSerialize m_isNull;
    VariantSerialize m_valVariant;

    QString eraseInvalidCharacters(const QString & src) const;
};
#endif // not defined(MetadataColumn_H_)
