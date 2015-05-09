#ifndef SerializableObject_H
#define SerializableObject_H

#include <QtCore/QObject>
#include <QtCore/QStringList>

#include <xml/mainserialize.h>

class MetadataTabs;
class MetadataTable;
class SerializableObject : public QObject, public MainSerialize
{
    Q_OBJECT

public:
    typedef enum {
        EObjectModeRam,
        EObjectModeReadOnly,
        EObjectModeReadWrite
    } EnumObjectMode;

public:
    SerializableObject(EnumObjectMode mode = EObjectModeRam, QObject *poParent = NULL);
    ~SerializableObject();

    EnumObjectMode getMode() const { return mode_; }
    void setMode(const EnumObjectMode & mode) { mode_ = mode; }

    void clear(const QStringList & stlExcludeOptionalTabs = QStringList());

    bool restart();

    MetadataTable* getTable(const QString & strName) const;

    bool isChanges() const;
    void vouchChanges() const;

    bool loadTables(const QString & strWhereColumnName = "", const int & intWhereColumnValue = 0);
    bool loadTable(const QString & strTableName, const QString & strWhereColumnName = "", const int & intWhereColumnValue = 0);

    bool updateTables(const QString & strWhereColumnName, const int & intWhereColumnValue);
    bool updateTable(const QString & strTableName, const QString & strWhereColumnName = "", const int & intWhereColumnValue = 0);

    void copyTables(SerializableObject *objectSource, const QString & strUpdateColumnName, const int & intUpdateColumnValue);
    void copyTable(SerializableObject *objectSource, const QString & strTableName,
                   const QString & strUpdateColumnName, const int & intUpdateColumnValue);

    /**
     * @brief is called to create list of objects for serialization
     * */
    virtual void createSerializeList();

    /**
     * @brief is called to create list of objects for deserialization
     * */
    virtual void createDeserializeList();

    virtual QString getStartTransaction();
    virtual void setStartTransaction();
    virtual void rollbackTransaction(const QString & strXml);

protected:
    EnumObjectMode mode_;
    MetadataTabs *dataTables_;
    QString strXmlBackup;
};

#endif // SerializableObject_H
