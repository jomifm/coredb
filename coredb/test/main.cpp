#include <QtCore/QString>
#include <QCoreApplication>
#include <QtCore/QFile>

#include "datatest.h"
#include "dbtest.h"
#include "coredb.h"
#include "utils/logger/utilslogger.h"

void testDataDb();
void testDataXml();
void deserializeConfigurationFile();

int main(int argc, char *argv[])
{
    LogFuncionBegin;

    qInstallMessageHandler(CoreSimLogger::MyLogger);
    LogInfo() << "Starting test application CoreDb";

	QCoreApplication a(argc, argv);

    //Prueba la funcionalidad de base de datos
    testDataDb();

    //Prueba la manipulacion de metadatos y serializacion/deserializacion de datos
    //testDataXml();
}

void testDataDb()
{
    LogFuncionBegin;

    DbTest objectDb;

    //Testea la composicion de sentencias SQL
    //objectDb.testSqlStatements();

    //Testea la creacion y uso de base de datos
    objectDb.createDatabaseSchema();
    objectDb.setDatabaseDummyData();
    objectDb.showDatabaseDummyData();

    LogFuncionEnd;
}

void testDataXml ()
{
    LogFuncionBegin;

    //Objeto que carga los Datos y serializa el Xml a partir de ellos
    DataTest objectUp;
    objectUp.addDummy();

    //Testea datos reales
    /*MetadataTable *dataTable = objectUp.getTable("T_CONFIG");
    if (dataTable != NULL)
    {
        MetadataRow *dataRow = dataTable->addRow();
        dataRow->addColumn("ID", MetadataColumn::E_CT_INT)->setValue(101);
        dataRow->addColumn("NOMBRE", MetadataColumn::E_CT_STRING)->setValue("CfgTest");
    }*/

    //Objeto que deserializa el Xml y carga los datos en los Metadatos
    QString strXml = objectUp.serializeAll();
    //LogInfo() << "Contenido serializado Xml:";
    //LogInfo() << strXml;

    DataTest objectDown;
    objectDown.deserializeAll(strXml);
    objectDown.testDummy();

    LogFuncionEnd;
}

