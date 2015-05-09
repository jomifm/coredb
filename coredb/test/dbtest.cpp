#include "dbtest.h"
#include "datatest.h"
#include "utils/logger/utilslogger.h"

#include "db/manager/dbmanager.h"

DbTest::DbTest(QObject *parent)
{
    Q_UNUSED(parent)
    LogFuncionBegin;

    DbManager::getInstance("test", "ars_tor", "ars_tor");

    LogFuncionEnd;
}

void DbTest::testSqlStatements()
{
    LogFuncionBegin;

    //Declaracion de Variables
    QString strStat;

    //Compreuba la sentencia SELECT
    strStat = SqlFactory::getSelectStatement("TABLE1");
    LogInfo() << "Statements SELECT whith all columns [" << ((strStat == QString("SELECT * FROM TABLE1;"))? "OK":"FAIL") << "]";
    strStat = SqlFactory::getSelectStatement("TABLE2", "COL2 = 'val2'");
    LogInfo() << "Statements SELECT + WHERE whith all columns [" << ((strStat == QString("SELECT * FROM TABLE2 WHERE COL2 = 'val2';"))? "OK":"FAIL") << "]";
    strStat = SqlFactory::getSelectStatement("TABLE3", "COL3 = 'val3'", "COL3");
    LogInfo() << "Statements SELECT + WHERE + ORDERBY whith all columns [" << ((strStat == QString("SELECT * FROM TABLE3 WHERE COL3 = 'val3' ORDER BY COL3;"))? "OK":"FAIL") << "]";

    //Compreuba la sentencia SELECT <cols>
    QStringList stlCols = QStringList() << "COL1" << "COL2";
    strStat = SqlFactory::getSelectColumnsStatement("TABLE1", stlCols);
    LogInfo() << "Statements SELECT <cols> whith all columns [" << ((strStat == QString("SELECT COL1, COL2 FROM TABLE1;"))? "OK":"FAIL") << "]";
    strStat = SqlFactory::getSelectColumnsStatement("TABLE2", stlCols, "COL2 = 'val2'");
    LogInfo() << "Statements SELECT <cols> + WHERE whith all columns [" << ((strStat == QString("SELECT COL1, COL2 FROM TABLE2 WHERE COL2 = 'val2';"))? "OK":"FAIL") << "]";
    strStat = SqlFactory::getSelectColumnsStatement("TABLE3", stlCols, "COL3 = 'val3'", "COL3");
    LogInfo() << "Statements SELECT <cols> + WHERE + ORDERBY whith all columns [" << ((strStat == QString("SELECT COL1, COL2 FROM TABLE3 WHERE COL3 = 'val3' ORDER BY COL3;"))? "OK":"FAIL") << "]";

    //Compreuba la sentencia UPDATE
    strStat = SqlFactory::getUpddateStatement("TABLE1", "COL1 = 'val1'");
    LogInfo() << "Statements UPDATE [" << ((strStat == QString("UPDATE TABLE1 SET COL1 = 'val1';"))? "OK":"FAIL") << "]";
    strStat = SqlFactory::getUpddateStatement("TABLE2", "COL2 = 'val2'", "COL3 = 'val3'");
    LogInfo() << "Statements UPDATE + WHERE [" << ((strStat == QString("UPDATE TABLE2 SET COL2 = 'val2' WHERE COL3 = 'val3';"))? "OK":"FAIL") << "]";

    //Compreuba la sentencia DELETE
    strStat = SqlFactory::getDeleteStatement("TABLE1");
    LogInfo() << "Statements DELETE [" << ((strStat == QString("DELETE FROM TABLE1;"))? "OK":"FAIL") << "]";
    strStat = SqlFactory::getDeleteStatement("TABLE2", "COL2 = 'val2'");
    LogInfo() << "Statements DELETE + WHERE [" << ((strStat == QString("DELETE FROM TABLE2 WHERE COL2 = 'val2';"))? "OK":"FAIL") << "]";

    LogFuncionEnd;
}

void DbTest::createDatabaseSchema()
{
    LogFuncionBegin;

    DbManager *dbManager = DbManager::getInstance();

    QString strCreate = QString("CREATE TABLE TABLE1 ("
           " TABLE1_COL1 int(11) NOT NULL,"
           " TABLE1_COL2 varchar(30) NOT NULL,"
           " PRIMARY KEY (TABLE1_COL1)"
          ") ; ");

    dbManager->dropTable("TABLE1");
    dbManager->executeQuery(strCreate);

    strCreate = QString("CREATE TABLE TABLE2 ("
           " TABLE2_COL1 int(11) NOT NULL,"
           " TABLE2_COL2 varchar(30) NOT NULL,"
           " PRIMARY KEY (TABLE2_COL1)"
          ") ; ");

    dbManager->dropTable("TABLE2");
    dbManager->executeQuery(strCreate);

    LogFuncionEnd;
}

void DbTest::setDatabaseDummyData()
{
    LogFuncionBegin;

    DbManager *dbManager = DbManager::getInstance();

    LogInfo() << "Insert data row 1 in TABLE1 with result rows affected: " <<
               dbManager->executeUpdate(SqlFactory::getInsertStatement("TABLE1", "TABLE1_COL1, TABLE1_COL2", "1, 'info-table1-row1'"));
    LogInfo() << "Insert data row 1 in TABLE1 with result rows affected: " <<
               dbManager->executeUpdate(SqlFactory::getInsertStatement("TABLE1", "TABLE1_COL1, TABLE1_COL2", "2, 'info-table1-row2'"));
    LogInfo() << "Insert data row 1 in TABLE1 with result rows affected: " <<
               dbManager->executeUpdate(SqlFactory::getInsertStatement("TABLE1", "TABLE1_COL1, TABLE1_COL2", "3, 'info-table1-row3'"));

    LogInfo() << "Insert data row 1 in TABLE2 with result rows affected: " <<
               dbManager->executeUpdate(SqlFactory::getInsertStatement("TABLE2", "TABLE2_COL1, TABLE2_COL2", "10, 'info-table2-row1'"));

    LogFuncionEnd;
}

void DbTest::showDatabaseDummyData()
{
    LogFuncionBegin;
    LogInfo();

    //Carga la Tabla independiente de la Base de Datos
    MetadataTable meta = MetadataTable("TABLE1", MetadataTable::ETableModeReadOnly);
    meta.loadTable();
    LogDebug() << "Rows in table TABLE1: " << meta.getNumberOfRows();

    //Carga las tablas del objeto desde la Base de Datos
    DataTest *dataObject = new DataTest();
    dataObject->setMode(SerializableObject::EObjectModeReadOnly);
    dataObject->loadTables();

    //Muestra la informacion de la Tabla
    MetadataTable *mdTable = dataObject->getTable("TABLE1");
    LogInfo() << "Datos de la Tabla: 'TABLE1' (" << mdTable << ")";
    if (mdTable)
    {
        for (int i = 1; i <= mdTable->getNumberOfRows(); i++)
        {
            MetadataRow *row = mdTable->getRow(i);
            if (row->isDeleted()) continue;

            LogInfo() << "- Row " << i << "Contents column values" << "[COL1:" << row->GetColumnValueInt("TABLE1_COL1") << "]"
                        << "[COL2:" << row->GetColumnValueString("TABLE1_COL2") << "]"
                        << "[COL3:" << row->GetColumnValueString("TABLE1_COL3") << "]";
        }
    }

    //Muestra la informacion de la Tabla
    mdTable = dataObject->getTable("TABLE2");
    LogInfo() << "Datos de la Tabla: 'TABLE2' (" << mdTable << ")";
    if (mdTable)
    {
        for (int i = 1; i <= mdTable->getNumberOfRows(); i++)
        {
            MetadataRow *row = mdTable->getRow(i);
            if (row->isDeleted()) continue;

            LogInfo() << "- Row " << i << "Contents column values" << "[COL1:" << row->GetColumnValueInt("TABLE2_COL1") << "]"
                        << "[COL2:" << row->GetColumnValueString("TABLE2_COL2") << "]"
                        << "[COL3:" << row->GetColumnValueString("TABLE2_COL3") << "]";
        }
    }

    LogFuncionEnd;
}
