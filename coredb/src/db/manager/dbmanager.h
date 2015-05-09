#ifndef DbManager_H_
#define DbManager_H_

#include <QString>
#include <QtSql>

typedef enum
{
    TABLE_ORIGINAL,
    TABLE_CREATE,
    TABLE_MODIFY,
    TABLE_DELETE,
} EnumManagerTableOperations;

class DbManager
{
public:
    DbManager (const QString & strDatabase,
               const QString & strUsername, const QString & strPassword);
    DbManager (const QString & strConnectionString);
    ~DbManager();

    static DbManager *getInstance(const QString & strDatabase,
                               const QString & strUsername, const QString & strPassword);
    static DbManager *getInstance() { return dbManager_; }

    QSqlDatabase getConnection() const { return sqlDatabase_; }

    bool isConnected() const { return sqlDatabase_.isOpen(); }

    void executeQuery (const QString & strQuery);
    int executeUpdate (const QString & strQuery);
    void createTable (const QString & strQuery);
    void dropTable (const QString & strTableName);

    void commit();
    void rollback();

    QStringList getTableColumns (const QString & strTableName);
    QStringList getTablePkColumns (const QString & strTableName);

private:
    static DbManager *dbManager_;
    QSqlDatabase sqlDatabase_;
};

#endif /* DbManager_H_ */
