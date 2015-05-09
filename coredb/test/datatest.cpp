#include "datatest.h"
#include "utils/logger/utilslogger.h"

#include <QtCore/QStringList>

#include "db/metadata/metadatatable.h"
#include "db/metadata/metadatarow.h"

static QStringList strList = QStringList()
    << "TABLE1"
    << "TABLE2"
    << "TABLE3";

DataTest::DataTest(QObject *parent) :
    SerializableObject(SerializableObject::EObjectModeRam, parent)
{
    LogFuncionBegin;

    setSerializationName("Configuration");
    intSerialValue_.setValue(0);
    strSerialValue_.setValue(QString(""));
    dataVarSerialValue_.setValue(QString(""));
    dataTables_ = new MetadataTabs(strList);

    LogFuncionEnd;
}

void DataTest::createSerializeList()
{
    LogFuncionBegin;

    SerializableObject::createSerializeList();
//    intValue_.setValue(99);
//    strValue_.setValue("string-dummy-value");
//    addSerializeObject(&intValue_, "FieldInteger");
//    addSerializeObject(&strValue_, "FieldString");

    addSerializeObject(&intSerialValue_, "FieldDataInteger");
    addSerializeObject(&strSerialValue_, "FieldDataString");
    addSerializeObject(&dataVarSerialValue_, "FieldDataVariantString");

    LogFuncionEnd;
}

void DataTest::createDeserializeList()
{
    LogFuncionBegin;

    SerializableObject::createDeserializeList();
    addDeserializeObject(&intSerialValue_);
    addDeserializeObject(&strSerialValue_);
    addDeserializeObject(&dataVarSerialValue_);

    LogFuncionEnd;
}

void DataTest::addDummy()
{
    LogFuncionBegin;

    MetadataTable *dataTable;
    MetadataRow *dataRow;

    dataTable = getTable("TABLE1");
    if (dataTable != NULL)
    {
        dataRow = dataTable->addRow();
        dataRow->addColumn("TABLE1_COL1", MetadataColumn::E_CT_INT)->setValue(1);
        dataRow->addColumn("TABLE1_COL2", MetadataColumn::E_CT_STRING)->setValue(QString("table1-row1"));

        dataRow = dataTable->addRow();
        dataRow->addColumn("TABLE1_COL1", MetadataColumn::E_CT_INT)->setValue(2);
        dataRow->addColumn("TABLE1_COL2", MetadataColumn::E_CT_STRING)->setValue(QString("table1-row2"));

        dataRow = dataTable->addRow();
        dataRow->addColumn("TABLE1_COL1", MetadataColumn::E_CT_INT)->setValue(3);
        dataRow->addColumn("TABLE1_COL2", MetadataColumn::E_CT_STRING)->setValue(QString("table1-row3"));
    }

    dataTable = getTable("TABLE2");
    if (dataTable != NULL)
    {
        dataRow = dataTable->addRow();
        dataRow->addColumn("TABLE2_COL1", MetadataColumn::E_CT_INT)->setValue(1);
        dataRow->addColumn("TABLE2_COL2", MetadataColumn::E_CT_STRING)->setValue(QString("table2-row1"));
    }

    setIntValue(9999);
    setStrValue("DataTestValue");
    setVarValue(QString("Setted-Object-Up"));

    LogFuncionEnd;
}

void DataTest::testDummy()
{
    LogFuncionBegin;

    //Comprueba la deserializacion de las tablas
    MetadataTable *table = NULL;
    table = getTable("TABLE1");
    if (NULL != table)
    {
        LogInfo() << "Exist table" << table->getName() << "[ OK ]";

        //Compreuba la deserializacion de rows
        LogInfo() << "Number of rows in table" << table->getNumberOfRows() << "[" << ((table->getNumberOfRows() == 3)? "OK":"FAIL") << "]";

        for (int i = 1; i <= (int)table->getNumberOfRows(); i++)
        {
            LogInfo() << "Data row contents" << table->getRow(i)->GetColumnValueInt("TABLE1_COL1")
                     << table->getRow(i)->GetColumnValueString("TABLE1_COL2")
                     << "[" << ((table->getRow(i)->GetColumnValueInt("TABLE1_COL1") == i)? "OK":"FAIL") << "]"
                     << "[" << ((table->getRow(i)->GetColumnValueString("TABLE1_COL2") == QString("table1-row%1").arg(i))? "OK":"FAIL") << "]";
        }
    }
    else LogInfo() << "Exist table 'TABLE1' [ FAIL ]";

    table = NULL;
    table = getTable("TABLE2");
    if (NULL != table)
    {
        LogInfo() << "Exist table" << table->getName() << "[ OK ]";

        //Compreuba la deserializacion de rows
        LogInfo() << "Number of rows in table" << table->getNumberOfRows() << "[" << ((table->getNumberOfRows() == 1)? "OK":"FAIL") << "]";

        for (int i = 1; i <= (int)table->getNumberOfRows(); i++)
        {
            LogInfo() << "Data row contents" << table->getRow(i)->GetColumnValueInt("TABLE2_COL1")
                     << table->getRow(i)->GetColumnValueString("TABLE2_COL2")
                     << "[" << ((table->getRow(i)->GetColumnValueInt("TABLE2_COL1") == i)? "OK":"FAIL") << "]"
                     << "[" << ((table->getRow(i)->GetColumnValueString("TABLE2_COL2") == QString("table2-row%1").arg(i))? "OK":"FAIL") << "]";
        }
    }
    else LogInfo() << "Exist table 'TABLE1' [ FAIL ]";

    //Comprueba la deserializacion de informacion adicional
    LogInfo() << "Deserialization 'Integer' field contents" << getIntValue() << "[" << ((getIntValue() == 9999)? "OK":"FAIL") << "]";
    LogInfo() << "Deserialization 'String' field contents" << getStrValue() << "[" << ((getStrValue() == "DataTestValue")? "OK":"FAIL") << "]";
    LogInfo() << "Deserialization 'Variant(String)' field contents" << getVarValue().toString() << "[" << ((getVarValue().toString() == "Setted-Object-Up")? "OK":"FAIL") << "]";

    LogFuncionEnd;
}

void DataTest::deserializeConfigurationFile()
{
    LogFuncionBegin;

    DataTest objectDown;

    QFile file1("ACC_1R0v5.xml");
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    QString strContents = file1.readAll();
    objectDown.deserializeAll(strContents);

    MetadataTable *table = NULL;
    table = objectDown.getTable("T_CONFIG");
    if (table == NULL) LogWarning() << "Tabla no encontrada";
    else LogInfo() << "Tabla:" << table->getName();

    if (NULL != table)
    {
        if (table->getNumberOfRows() > 0)
            LogInfo() << "Config: " << table->getRow(1)->GetColumnValueInt("ID")
                     << table->getRow(1)->GetColumnValueString("NOMBRE");
    }

    LogFuncionEnd;
}
