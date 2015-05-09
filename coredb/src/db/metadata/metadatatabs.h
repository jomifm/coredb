#ifndef MetadataTabs_H_
#define MetadataTabs_H_

#include <QtCore/QString>
#include <QtCore/QStringList>

#include "xml/data/vectortableserialize.h"

class MetadataTable;
class MetadataTabs : public MainSerialize
{
public:
    MetadataTabs();
    MetadataTabs(const QStringList & strListTables);
    virtual ~MetadataTabs();

    QStringList getTableNames() const { return stlTableNames_; }

    void restart(const QString & strTableName);

    /**
     * @brief Returns pointer to table specified by its name. If table with
     * given name is not found then returns NULL.
     * */
    MetadataTable* getTable(const QString & tabName) const;

    /**
     * @brief Returns pointer to table specified by its index in list of tables.
     * In case if requested index is out of bounds then returns NULL. Tables are
     * indexed from zero.
     * */
    MetadataTable* getTable(const int tabIndex) const;

    /**
     * @brief Returns number of tables.
     * */
    int tabCount() const { return vectorTables_.size(); }

    /**
     * @brief Clear data from all tables, except list of tables specified as
     * parameter
     * */
    void clear (const QStringList & strExcludeOptionalTables = QStringList());

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
    QVector<MetadataTable*> vectorTables_;
    VectorTableSerialize serializeTables_;

    QStringList stlTableNames_;
};

#endif /* MetadataTabs_H_ */
