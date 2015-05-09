#ifndef MetadataTable_H_
#define MetadataTable_H_

#include <vector>
#ifdef CORETMCS_DBMANAGER
    #include "db/C_Select.h"
    #include "db/manager/dbmanager.h"
    #include "db/metadata/metadatacolumn.h"
#endif

#include "xml/mainserialize.h"
#include "xml/data/intserialize.h"
#include "xml/data/stringserialize.h"
#include "xml/data/vectorrowserialize.h"
#include "xml/data/vectorstringserialize.h"


/**
 * @brief Class MetadataTable is used to store DB table data.
 * */
class DbManager;
class MetadataRow;
class MetadataTable : public MainSerialize
{
public:
    /**
     * @brief Enumeration of possible table statuses
     * */
    typedef enum
    {
        /** default table status - table empty/not loaded */
        E_TAB_STAT_NONE,
        /** table loaded with data */
        E_TAB_STAT_LOADED,
        /** table contains updated data */
        E_TAB_STAT_UPDATED
    } E_TABLE_STATUS;

    typedef enum {
        ETableModeRam,
        ETableModeReadOnly,
        ETableModeReadWrite
    } EnumTableMode;

public:
    /**
     * @brief Default constructor
     * */
    MetadataTable();
    /**
     * @brief Constructor that creates table with specified table name
     * */
    MetadataTable(const QString & tableName, EnumTableMode mode = ETableModeRam);
    /**
     * @brief Default destructor
     * */
    virtual ~MetadataTable();

    EnumTableMode getMode() const { return mode_; }
    void setMode(const EnumTableMode & mode) { mode_ = mode; }

    /**
     * @brief Returns the name of the table
     * */
    QString getName() const { return strName_.getValue(); }

    /**
     * @brief Returns WHERE condition of table data selection
     * */
    QString getWhere() const;

    /**
     * @brief Sets WHERE condition of table data selection
     * */
    void setWhere(const QString & strWhere);

    /**
     * @brief Returns ORDER BY condition of table data selection
     * */
    QString getOrderBy() const;

    /**
     * @brief Sets ORDER BY condition of table data selection
     * */
    void setOrderBy(const QString & strOrderBy);

    /**
     * @brief Check if status of table is "Updated"
     * Table status is "Updated" if some table data are changed
     * */
     bool isUpdated() const;
    /**
     * @brief Check if status of table is "Loaded"
     * Table status is "Loaded" if it contains at least one row of data
     * */
    bool isLoaded() const;
    /**
     * @brief Set status of table to "Updated"
     * */
    void setUpdated();
    /**
     * @brief Set status of table to "Loaded"
     * */
    void setLoaded();
    /**
     * @brief Create new row in the table
     * */
    MetadataRow * addRow();
    /**
     * @brief Create new row based on row in first parameter
     * */
    MetadataRow * addRow(MetadataRow* metadataRowCopy,
                         const QString & strUpdateColumnName = "", const int & intUpdateColumnValue = 0);
    /**
     * @brief Returns pointer to row object specified by row number.
     * */
    MetadataRow * getRow(const unsigned int & rowNum) const;
    /**
     * @brief Returns number of rows of the table
     * */
    unsigned int getNumberOfRows() const;
    /**
     * @brief Dump table data to stdout
     * */
    void dumpTableData(const char delim='\t') const;
    /**
     * @brief Dump table data to file
     * */
    void dumpTableData(const QString & fileName, const char delim='\t') const;

    /**
     * @brief Delete all rows of the table that they are not in database idDBRow = false
     * */
    void deleteNotDbRow();

    /**
     * @brief Delete all table rows and reset status to 'None'
     * */
    void deleteRows();

    /**
     * @brief Returns pointer to table row which contains column "ID" with
     * value equal to idToFind. If not found returns NULL.
     * */
    MetadataRow *findRowWithID(const int idToFind, const bool skipDeleted=true) const;

    MetadataRow *getRowWithFieldvalue(QString strToFind, QString strColumnName, bool booSkipDeleted = true);
    MetadataRow *getRowWithFieldvalue(int intValueToFind, QString strColumnName, bool booSkipDeleted = true);

    /* Serialization functions */

    /**
     * @brief is called to create list of objects for deserialization
     * */
    virtual void createDeserializeList();

    /**
     * @brief is called to create list of objects for serialization
     * */
    virtual void createSerializeList();

public:
    /** Method loads table data from database */
    void loadTable();

    /** Method updates table data in database */
    int updateTable();

public:
    /** create where condition from given row data and table primary key */
    QString getWhereByPK(const int & rowNum);

    QVector<QString> getPkColumns() const { return stlPrimaryKeyColumns_; }
    void setPkColumns (const QVector<QString> & listPkCols)  { stlPrimaryKeyColumns_ = listPkCols; }

private:
    EnumTableMode mode_;

    /* status of the table */
    IntSerialize idStatus_; /* E_TABLE_STATUS */

    /* table name */
    StringSerialize strName_;

    /* vector of table rows */
    QVector<MetadataRow *> vectorRows_;
    /* Serialization object for m_rows */
    VectorRowSerialize serializeRows_;

    /* table where condition */
    StringSerialize strWhereStatement;
    /* table ORDER BY condition */
    StringSerialize strOrderByStatement;

    /* list of the names of the table primary key columns */
    QVector<QString> stlPrimaryKeyColumns_;
    /* Serialization object for m_PKColumns */
    VectorStringSerialize vectorPkColumns;
};
#endif // !defined(MetadataTable_H_)
