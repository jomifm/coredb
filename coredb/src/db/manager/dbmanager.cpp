#include "db/manager/dbmanager.h"
#include "utils/logger/utilslogger.h"

//Indica el driver del gestor de BBDD
QString strDatabaseDriver ("QSQLITE");

//The only instance of this class
DbManager* DbManager::dbManager_ = NULL;

DbManager::DbManager(const QString & strDatabase, const QString & strUsername, const QString & strPassword)
{
    LogFuncionBegin;

    LogInfo() << "Database connection: " << strDatabase << strUsername << strPassword;

    //Instancia del gestor de conexion con la base de datos
    sqlDatabase_ = QSqlDatabase::addDatabase(strDatabaseDriver);
    sqlDatabase_.setHostName("127.0.0.1");
    sqlDatabase_.setDatabaseName(strDatabase);
    sqlDatabase_.setUserName(strUsername);
    sqlDatabase_.setPassword(strPassword);
    if (!sqlDatabase_.open())
    {
        LogError() << "Database Error: " << sqlDatabase_.lastError().text();
	}
    else LogInfo() << "Database " << sqlDatabase_.databaseName() << " open successfully " << sqlDatabase_.isOpen();

    LogFuncionEnd;
}

DbManager::~DbManager()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

DbManager *DbManager::getInstance(const QString & strDatabase, const QString & strUsername, const QString & strPassword)
{
    LogFuncionBegin;

    //Instancia del gestor de conexion con la base de datos
    dbManager_ = new DbManager (strDatabase, strUsername, strPassword);

    LogFuncionEnd;

    return dbManager_;
}

void DbManager::executeQuery(const QString & strQuery)
{
    LogFuncionBegin;

	//Ejecuta la sentencia
    executeUpdate(strQuery);

    LogFuncionEnd;
}

int DbManager::executeUpdate(const QString & strQuery)
{
    LogFuncionBegin;

	//Ejecuta la sentencia
    QSqlQuery sqlQuery(strQuery);
	if (!sqlQuery.isActive()) 
	{
        LogError() << "Query Failed: " << sqlQuery.lastQuery() << sqlQuery.lastError().text();
	}
    else LogInfo() << "Query executed succesfully (AffectedRows:" << sqlQuery.numRowsAffected() << ")";

    LogFuncionEnd;

    return sqlQuery.numRowsAffected();
}

void DbManager::dropTable(const QString & strTablaName)
{
    LogFuncionBegin;

	//Declaracion de Variables
    QString strDropStatement;

	//Obtiene la sentencia Sql de eliminacion de la Tabla
    strDropStatement = "DROP TABLE IF EXISTS " + strTablaName + ";";

	//Ejecuta la sentencia Sql
    executeQuery(strDropStatement);

    LogFuncionEnd;
}

void DbManager::commit()
{
    LogFuncionBegin;

    //Realiza un commit de las operaciones realizadas antes del autocommit
    sqlDatabase_.commit();

    LogFuncionEnd;
}

void DbManager::rollback()
{
    LogFuncionBegin;

    //Realiza un rollback de las operaciones realizadas antes del autocommit
    sqlDatabase_.rollback();

    LogFuncionEnd;
}

QStringList DbManager::getTableColumns(const QString & strTableName)
{
    LogFuncionBegin;

    //Declaracion de variables
    QStringList stlColumns;
    QSqlRecord sqlRecord;

    //Recorre las columnas de la tabla
    sqlRecord = sqlDatabase_.record(strTableName);
    for (int i = 0; i < sqlRecord.count(); i++)
        stlColumns.append(sqlRecord.fieldName(i));

    return stlColumns;

    LogFuncionEnd;
}

QStringList DbManager::getTablePkColumns(const QString & strTableName)
{
    LogFuncionBegin;

    //Declaracion de variables
    QStringList stlPkColumns;
    QSqlIndex sqlIndex;

    //Recorre las columnas de la clave primaria de la tabla
    sqlIndex = sqlDatabase_.primaryIndex(strTableName);
    for (int i = 0; i < sqlIndex.count(); i++)
        stlPkColumns.append(sqlIndex.fieldName(i));

    return stlPkColumns;

    LogFuncionEnd;
}
