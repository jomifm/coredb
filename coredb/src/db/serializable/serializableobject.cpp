#include "db/serializable/serializableobject.h"
#include "db/metadata/metadatarow.h"
#include "db/metadata/metadatatable.h"
#include "db/metadata/metadatatabs.h"
#include "utils/logger/utilslogger.h"

SerializableObject::SerializableObject(EnumObjectMode mode, QObject *poParent)
    : QObject(poParent)
{
    LogFuncionBegin;

    //Inicializacion de variables
    mode_ = mode;
    dataTables_ = NULL;

    //Inicializacion de variables de serializacion
    setSerializationName("SerializableObject");

    LogFuncionEnd;
}

SerializableObject::~SerializableObject()
{
    LogFuncionBegin;

    //Elimina la lista de tabs
    delete dataTables_;

    LogFuncionEnd;
}

void SerializableObject::clear(const QStringList & stlExcludeOptionalTabs)
{
    LogFuncionBegin;

    //Limpia el contenido de las tablas
    dataTables_->clear(stlExcludeOptionalTabs);

    LogFuncionEnd;
}

bool SerializableObject::restart()
{
    LogFuncionBegin;

    //Declaracion de variables
    bool booRetValue = true;
    MetadataTable *metadataTable = NULL;

    //Comprueba si existen tabs
    if (dataTables_ != NULL)
    {
        //Recorre la lista de tablas
        int iTableCount = dataTables_->tabCount();
        for (int i = 0; i < iTableCount; i++)
        {
            //Obtiene la tabla y comprueba si exsite
            metadataTable = dataTables_->getTable(i);
            if (metadataTable != NULL)
            {
                //Reinicializa la tabla
                dataTables_->restart(metadataTable->getName());
            }
            else booRetValue = false;
        }
    }
    else booRetValue = false;

    LogFuncionEnd;

    return booRetValue;
}

MetadataTable* SerializableObject::getTable (const QString & strName) const
{
    LogFuncionBegin;
    LogFuncionEnd;

    //Devuelve la tabla para el nombre indicado
    return dataTables_->getTable(strName);
}

bool SerializableObject::isChanges() const
{
    LogFuncionBegin;

    //Declaracion de variables
    bool booRetValue = false;
    MetadataTable *metadataTable = NULL;
    int iTableCount = 0;
    unsigned int iRowCount = 0;
    MetadataRow *metadataRow = NULL;

    //Recorre las tablas del objeto
    iTableCount = dataTables_->tabCount();
    for(int i = 0; i < iTableCount; i++)
    {
        //Obtiene la tabla y comprueba que existe y es valida
        metadataTable = dataTables_->getTable(i);
        if (metadataTable == NULL) continue;

        //Recorre las rows de la tabla
        iRowCount = metadataTable->getNumberOfRows();
        for(unsigned int iRow = 1; iRow <= iRowCount; iRow++)
        {
            //Obtiene la row y comprueba que existe y es valida
            metadataRow = metadataTable->getRow(iRow);
            if (metadataRow == NULL) continue;

            //Comprueba se ha realizado alguna operacion en la row
            if (metadataRow->isDeleted() || metadataRow->isUpdated() || metadataRow->isNew())
            {
                booRetValue = true;
                break;
            }
        }
        if (booRetValue) break;
    }

    LogFuncionEnd;

    return booRetValue;
}

void SerializableObject::vouchChanges() const
{
    LogFuncionBegin;

    //Declaracion de Variables
    MetadataTable* metadataTable = NULL;
    MetadataRow* metadataRow = NULL;
    MetadataColumn* metadataColumn = NULL;
    int iTableCount = 0;
    unsigned int iRowCount = 0;
    unsigned int iColumnCount = 0;

    //Recorre la lista de tabals
    iTableCount = dataTables_->tabCount();
    for(int i = 0; i < iTableCount; i++)
    {
        //Obtiene la tabla
        metadataTable = dataTables_->getTable(i);
        if (metadataTable == NULL) continue;

        //Elimina las rows que se encuentran deleted
        metadataTable->deleteNotDbRow();

        //Recorre las rows de la tabla
        iRowCount = metadataTable->getNumberOfRows();
        for (unsigned int iRow = iRowCount; iRow > 0; iRow--)
        {
            //Obtiene la row y comprueba si es valida
            metadataRow = metadataTable->getRow(iRow);
            if (metadataRow == NULL) continue;

            //Inicializa la row
            metadataRow->setNormal();
            metadataRow->setDbRow(true);

            //Recorre las columnas de la tabla
            iColumnCount = metadataRow->getNumberOfColumns();
            for (unsigned int iCol = iColumnCount; iCol > 0; iCol--)
            {
                //Obtiene la row y comprueba si es valida
                metadataColumn = metadataRow->getColumn(iCol);
                if (metadataColumn == NULL) continue;

                //Inicializa la columna
                metadataColumn->setLoaded();
            }
        }
    }

    LogFuncionEnd;
}

bool SerializableObject::loadTables(const QString & strWhereColumnName, const int & intWhereColumnValue)
{
    LogFuncionBegin;

    //Comprueba si el objeto permite acceso a la Base de Datos
    if (EObjectModeRam == mode_)
    {
        LogWarning() << "Cannot access to database in Object Ram mode";
        return false;
    }

    //Declaracion de variables
    QStringList stlTables;

    //Recorre la lista de tablas y las carga
    stlTables = dataTables_->getTableNames();
    for(int i = 0; i < stlTables.count(); i++)
        loadTable(stlTables.at(i), strWhereColumnName, intWhereColumnValue);

    LogFuncionEnd;

    return true;
}

bool SerializableObject::loadTable(const QString & strTableName, const QString & strWhereColumnName, const int & intWhereColumnValue)
{
    LogFuncionBegin;

    //Comprueba si el objeto permite acceso a la Base de Datos
    if (EObjectModeRam == mode_)
    {
        LogWarning() << "Cannot access to database in Object Ram mode";
        return false;
    }

    //Declaracion dde variables
    MetadataTable * metadataTable = NULL;

    //Obtiene la tabla quse se pretende cargar
    metadataTable = getTable(strTableName);
    if (metadataTable != NULL)
    {
        //Comprueba si es valido el valor de la clausula where
        if (!strWhereColumnName.isEmpty() && intWhereColumnValue >= 0)
             metadataTable->setWhere(QString(" %1 = %2 ").arg(strWhereColumnName).arg(intWhereColumnValue));

        //Establece el modo de operacion de la Tabla
        if (EObjectModeReadOnly == mode_) metadataTable->setMode(MetadataTable::ETableModeReadOnly);
        else if (EObjectModeReadWrite == mode_) metadataTable->setMode(MetadataTable::ETableModeReadWrite);
        else metadataTable->setMode(MetadataTable::ETableModeRam);

        //Carga los datos de la tabla
        metadataTable->loadTable();

        LogInfo() << "Loaded [Table:" << strTableName << "] with" << metadataTable->getNumberOfRows() << "row(s)";
    }

    LogFuncionEnd;

    return true;
}

bool SerializableObject::updateTables(const QString & strWhereColumnName, const int & intWhereColumnValue)
{
    LogFuncionBegin;

    //Comprueba si el objeto permite acceso a la Base de Datos
    if (EObjectModeReadWrite != mode_)
    {
        LogWarning() << "Cannot access to database without Object Read/Write mode";
        return false;
    }

    //Declaracion de variables
    QStringList stlTables;

    //Recorre la lista de tablas y las actualiza
    stlTables = dataTables_->getTableNames();
    for(int i = 0; i < stlTables.count(); i++)
        updateTable(stlTables.at(i), strWhereColumnName, intWhereColumnValue);

    return true;

    LogFuncionEnd;
}

bool SerializableObject::updateTable(const QString & strTableName, const QString & strWhereColumnName, const int & intWhereColumnValue)
 {
    LogFuncionBegin;

    //Comprueba si el objeto permite acceso a la Base de Datos
    if (EObjectModeReadWrite != mode_)
    {
        LogWarning() << "Cannot access to database without Object Read/Write mode";
        return false;
    }

    //Declaracion de variales
    bool booRetValue = true;
    MetadataTable *metadataTable = NULL;
    int intRowsUpdated = 0;

    //Obtiene la tabla quse se pretende actualizar
    metadataTable = getTable(strTableName);
    if (metadataTable != NULL)
    {
        //Comprueba si la tabla tiene rows
        if (metadataTable->getNumberOfRows() > 0)
        {
            //Comprueba si es valido el valor de la clausula where
            if (!strWhereColumnName.isEmpty() && intWhereColumnValue >= 0)
                metadataTable->setWhere(QString(" %1 = %2 ").arg(strWhereColumnName).arg(intWhereColumnValue));

            //Actualiza los datos de la tabla
            intRowsUpdated = metadataTable->updateTable();
            LogInfo() << "Table" << strTableName << "updated" << intRowsUpdated << "rows";
        }
    }
    else
    {
        booRetValue = false;
        LogError() << "Trying to update [Table:" << strTableName << "] doesn't exist";
    }

    LogFuncionEnd;

    return booRetValue;
}

void SerializableObject::copyTables(SerializableObject *objectSource,
                                    const QString & strUpdateColumnName, const int & intUpdateColumnValue)
{
    LogFuncionBegin;

    //Declaracion de variables
    QStringList stlTables;

    //Recorre la lista de tablas y las actualiza
    stlTables = objectSource->dataTables_->getTableNames();
    for(int i = 0; i < stlTables.count(); i++)
        copyTable(objectSource, stlTables.at(i), strUpdateColumnName, intUpdateColumnValue);

    LogFuncionEnd;
}

void SerializableObject::copyTable(SerializableObject *objectSource, const QString & strTableName,
                                 const QString & strUpdateColumnName, const int & intUpdateColumnValue)
{
    LogFuncionBegin;

    //Declaracion de variables
    MetadataTable * metadataTable = NULL;
    MetadataTable * metadataTableSource = NULL;
    MetadataRow * metadataRowSource = NULL;
    int iRowsCount;

    metadataTableSource = objectSource->getTable(strTableName);
    metadataTable = this->getTable(strTableName);
    if (metadataTableSource != NULL && metadataTable != NULL)
    {
        iRowsCount = metadataTable->getNumberOfRows();
        for(int i = 1; i <= iRowsCount; i++)
            metadataTable->getRow(i)->setDeleted();

        iRowsCount = metadataTableSource->getNumberOfRows();
        for (int iRow = 1; iRow <= iRowsCount; iRow++)
        {
            //copy row
            metadataRowSource = metadataTableSource->getRow(iRow);
            if (metadataRowSource != NULL && !metadataRowSource->isDeleted())
                metadataTable->addRow(metadataRowSource, strUpdateColumnName, intUpdateColumnValue);
        }
    }

    LogFuncionEnd;
}

void SerializableObject::createSerializeList()
{
    LogFuncionBegin;

    //Establece la lista de objetos para serializar
    m_lstSerializeObjects.clear();
    addSerializeObject(dataTables_, "Tabs");

    LogFuncionEnd;
}

void SerializableObject::createDeserializeList()
{
    LogFuncionBegin;

    //Establece la lista de objetos para deserializar
    m_vDeserializeObjects.clear();
    addDeserializeObject(dataTables_);

    LogFuncionEnd;
}

QString SerializableObject::getStartTransaction()
{
    LogFuncionBegin;

    //Obtiene una copia de la lista de datos del objeto (xml)
    QString strXml = this->serializeAll();

    LogFuncionEnd;

    return strXml;
}

void SerializableObject::setStartTransaction()
{
    LogFuncionBegin;

    //Guarda una copia de la lista de datos del objeto (xml)
    strXmlBackup = this->serializeAll();

    LogFuncionEnd;
}

void SerializableObject::rollbackTransaction(const QString & strXml)
{
    LogFuncionBegin;

    //Restaura la copia de la lista de datos del objeto (xml)
    this->clear();
    if (!strXml.isEmpty()) this->deserializeAll(strXml);
    else this->deserializeAll(strXmlBackup);

    LogFuncionEnd;
}
