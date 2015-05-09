#ifndef MetadataRow_H_
#define MetadataRow_H_

#include "db/metadata/metadatacolumn.h"

#include "xml/mainserialize.h"
#include "xml/data/intserialize.h"
#include "xml/data/vectorcolumnserialize.h"

#include <vector>

/**
 * @brief Class Table Row stores data of one table row.
 * */
class MetadataRow : public MainSerialize
{
public:
    /**
     * @brief Enumeration of table row statuses
     * */
    enum E_ROW_STATUS
    {
        /** Normal row - not new/updated/deleted */
        E_TR_STAT_NORMAL,
        /** New row */
        E_TR_STAT_NEW,
        /** Updated row */
        E_TR_STAT_UPDATED,
        /** Deleted row */
        E_TR_STAT_DELETED
    };

public:
    /**
     * @brief Default constructor. Creates normal row
     * */
    MetadataRow();
    /**
     * @brief Default destructor.
     * */
    virtual ~MetadataRow();
    /**
     * @brief Set status of the row to "Normal". Use it to not perform any DB
     * operation for given row
     * */
    void setNormal();
    /**
     * @brief Set status of the row to "New". Use it to mark rows to insert them
     * into DB
     * */
    void setNew();
    /**
     * @brief Set status of the row to "Updated". Use it to mark rows to update
     * them in DB. Update DB operation will be performed only for columns marked
     * for update.
     * */
    void setUpdated();
    /**
     * @brief Set status of the row to "Deleted". Use it to mark rows to delete
     * them from given database table
     * */
    void setDeleted();
    /**
     * @brief Check if status of the row is "Normal".
     * @return true if the status of row is "Normal", otherwise returns false
     * */
    bool isNormal() const;
    /**
     * @brief Check if status of the row is "New".
     * @return true if the status of row is "New", otherwise returns false
     * */
    bool isNew() const;
    /**
     * @brief Check if status of the row is "Deleted".
     * @return true if the status of row is "Deleted", otherwise returns false
     * */
    bool isDeleted() const;
    /**
     * @brief Check if status of the row is "Updated".
     * @return true if the status of row is "Updated", otherwise returns false
     * */
    bool isUpdated() const;
    /**
     * @brief Create new column in table row
     * @param colName IN: Column name
     * @param dataType IN: Column data type
     * @return If the column is created then returns pointer to created column
     * object. Otherwise returns NULL.
     * */
    MetadataColumn * addColumn(const QString & colName, const MetadataColumn::E_COLUMN_TYPE & dataType);
    MetadataColumn * addColumn(const QString & colName, const QVariant::Type & dataType);
    /**
     * @brief Create new column in table row, based on column in first parameter
     * @param pColumnToCopy IN : column which copy should be added
     * @return If the column is created then returns pointer to created column
     * object. Otherwise returns NULL.
     * */
    MetadataColumn * addColumn(MetadataColumn *pColumnToCopy);
    /**
     * @brief Return pointer to column object specified by column index
     * @param colIndex IN : requested column index
     * @return Pointer to requested column object. If column doesn't exists
     * returns NULL
     * */
    MetadataColumn * getColumn(const unsigned int & colIndex) const;
    /**
     * @brief Return pointer to column object specified by column name
     * @param colName IN : requested column name
     * @return Pointer to requested column object. If column doesn't exists
     * returns NULL
     * */
    MetadataColumn * getColumn(const QString & colName) const;
    /**
     * @brief Returns number of row columns
     * */
    int getNumberOfColumns() const { return m_columns.size(); }
    /**
     *  @brief Returns string with column data delimited with delimiter
     *  specified as parameter. If delimiter parameter is not specified, then
     *  will be used tabulator as default delimiter.
     **/
    QString dataToString(const char delim = '\t') const;
    /**
     *  @brief Returns string with column names delimited with delimiter
     *  specified as parameter. If delimiter parameter is not specified, then
     *  will be used tabulator as default delimiter.
     **/
    QString colNamesToString(const char delim='\t') const;
    /**
     *  @brief Returns string that contain update pairs of columns with updated
     *  data. The string has format:
     *  "COLNAME1=DATA1, COLNAME2=DATA2, ..., COLNAMEn=DATAn"
     **/
    QString getUpdPairs() const;

    /**
     *  @brief Set indicator that given row is loaded from database
     **/
    void setDbRow(const bool isDbRow);

    /**
     *  @brief Indicates if given row is loaded from database
     **/
    bool isDbRow() const;

    int GetRowID() const;
    int GetColumnValueInt(const QString & columName) const;
    QString GetColumnValueString(const QString & columName) const;
    bool GetColumnValueBool(const QString & columName) const;

    /* Serialization functions */

    /**
     * @brief is called to create list of objects for deserialization
     * */
    virtual void createDeserializeList();

    /**
     * @brief is called to create list of objects for serialization
     * */
    virtual void createSerializeList();

private:
    IntSerialize m_status; /* E_ROW_STATUS */
    BoolSerialize m_isDBrow;
    QVector <MetadataColumn *> m_columns;
    /* Serialization object for m_columns */
    VectorColumnSerialize m_SerializeColumns;
};
#endif // not defined(MetadataRow_H_)

