#include "db/metadata/metadatatable.h"
#include "db/manager/dbmanager.h"
#include "db/manager/sqlfactory.h"
#include "db/metadata/metadatarow.h"
#include "utils/logger/utilslogger.h"

MetadataTable::MetadataTable()
{
    LogFuncionBegin;

    //Inicializacion de variables
    mode_ = ETableModeRam;
    strName_.setValue("");
    idStatus_.setValue(E_TAB_STAT_NONE);
    strWhereStatement.setValue("");
    strOrderByStatement.setValue("");
    setSerializationName("Table");
    serializeRows_.setValue(&vectorRows_);
    serializeRows_.setSerializationName("Rows");
    vectorPkColumns.setValue(&stlPrimaryKeyColumns_);
    vectorPkColumns.setSerializationName("PKColumns");

    LogFuncionEnd;
}

MetadataTable::MetadataTable(const QString & tableName, EnumTableMode mode)
{
    LogFuncionBegin;

    //Inicializacion de variables
    mode_ = mode;
    strName_.setValue(tableName);
    idStatus_.setValue(E_TAB_STAT_NONE);
    strWhereStatement.setValue("");
    strOrderByStatement.setValue("");
    setSerializationName("Table");
    serializeRows_.setValue(&vectorRows_);
    serializeRows_.setSerializationName("Rows");
    vectorPkColumns.setValue(&stlPrimaryKeyColumns_);
    vectorPkColumns.setSerializationName("PKColumns");

    LogFuncionEnd;
}

MetadataTable::~MetadataTable()
{
    LogFuncionBegin;

    //Elimina las variables
    deleteRows();
    stlPrimaryKeyColumns_.clear();

    LogFuncionEnd;
}

bool MetadataTable::isUpdated() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    //Comprueba si la tabla esta actualizada
    return (idStatus_.getValue() == E_TAB_STAT_UPDATED);
}

bool MetadataTable::isLoaded() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    //Comprueba si la tabla esta cargada
    return (idStatus_.getValue() == E_TAB_STAT_LOADED);
}

void MetadataTable::setUpdated()
{
    LogFuncionBegin;

    //Establece la tabla como actualizada
    idStatus_.setValue(E_TAB_STAT_UPDATED);

    LogFuncionEnd;
}

void MetadataTable::setLoaded()
{
    LogFuncionBegin;

    //Establece la tabla como cargada
    idStatus_.setValue(E_TAB_STAT_LOADED);

    LogFuncionEnd;
}

MetadataRow *MetadataTable::addRow()
{
    LogFuncionBegin;

    //Crea una nueva fila para la tabla
    MetadataRow * metadataRow = new MetadataRow();
    vectorRows_.push_back(metadataRow);

    LogFuncionEnd;

    return metadataRow;
}

MetadataRow *MetadataTable::addRow(MetadataRow* metadataRowSource,
                                   const QString & strUpdateColumnName, const int & intUpdateColumnValue)
{
    LogFuncionBegin;

    //Declaracion de variables
    MetadataRow* metadataRow = NULL;
    MetadataColumn* metadataColumn = NULL;
    MetadataColumn* metadataColumnSource = NULL;

    //Comprueba la row cno la informacion de origen
    if (metadataRowSource && !metadataRowSource->isDeleted())
    {
        //Crea una nueva row en la tabla
        metadataRow = addRow();
        metadataRow->setNew();

        //Recorre las rows de la tabla de origen
        unsigned int iColCount = metadataRowSource->getNumberOfColumns();
        for (unsigned int iCol = 1; iCol <= iColCount; iCol++)
        {
            //Obtiene la columna de la tabla de origen
            metadataColumnSource = metadataRowSource->getColumn(iCol);

            //Copia la columna de origen
            metadataColumn = metadataRow->addColumn(metadataColumnSource);

            //Comprueba si es la columna de actualizacion y le establece el nuevo valor
            if (metadataColumn == NULL) continue;
            else if (strUpdateColumnName.isEmpty()) continue;
            else if (metadataColumn->getName() != strUpdateColumnName) continue;

            //Actualiza el valor de la columna
            metadataColumn->setValue(intUpdateColumnValue);
        }
    }

    LogFuncionEnd;

    return metadataRow;
}

unsigned int MetadataTable::getNumberOfRows() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return vectorRows_.size();
}

MetadataRow *MetadataTable::getRow(const unsigned int & rowNum) const
{
    LogFuncionBegin;

    if (rowNum > (const unsigned int)vectorRows_.size() || rowNum < 1)
    {
        return NULL;
    }

    LogFuncionEnd;

    return vectorRows_[rowNum - 1];
}

QString MetadataTable::getWhere() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return strWhereStatement.getValue();
}

void MetadataTable::setWhere(const QString & strWhere)
{
    LogFuncionBegin;

    this->strWhereStatement.setValue(strWhere);

    LogFuncionEnd;
}

QString MetadataTable::getOrderBy() const
{
    LogFuncionBegin;
    LogFuncionEnd;

    return strOrderByStatement.getValue();
}

void MetadataTable::setOrderBy(const QString & strOrderBy)
{
    LogFuncionBegin;

    this->strOrderByStatement.setValue(strOrderBy);

    LogFuncionEnd;
}

void MetadataTable::dumpTableData(const char delim) const
{
    LogFuncionBegin;

    Q_UNUSED(delim)

//    QString strDel="";
//    unsigned int rowNr=0;

//    cout << "STARTING DATA DUMP OF TABLE:" << getName().toStdString() << endl;

//    for (rowNr = 1; rowNr <= m_rows.size(); rowNr++)
//    {
//        // for first row print column names
//        if (rowNr == 1)
//        {
//            strDel.append(m_rows.at(rowNr-1)->colNamesToString(delim).size()), '=');
//            cout << "Row No, " << m_rows.at(rowNr-1)->colNamesToString(delim)
//                    << endl << strDel << endl;
//        }
//        cout << rowNr << ": " << m_rows.at(rowNr-1)->dataToString(delim).toStdString() << endl;
//    }

    LogFuncionEnd;
}

void MetadataTable::dumpTableData(const QString & fileName, const char delim) const
{
    LogFuncionBegin;

    Q_UNUSED(fileName)
    Q_UNUSED(delim)

//    fstream outFl;
//    string flDel="";
//    unsigned int rowNr = 0;

//    try
//    {
//        outFl.open(fileName.toStdString().c_str(), fstream::out);

//        outFl << "STARTING DATA DUMP OF TABLE: " << getName().toStdString() << endl;

//        for (rowNr = 1; rowNr <= m_rows.size(); rowNr++)
//        {
//            // for first row print column names
//            if (rowNr == 1)
//            {
//                flDel.append(m_rows.at(rowNr-1)->colNamesToString(delim).toStdString().size(), '=');
//                outFl << "Row No, " << m_rows.at(rowNr-1)->colNamesToString(delim).toStdString()
//                        << endl << flDel << endl;
//            }
//            outFl << rowNr << ": " << m_rows.at(rowNr-1)->dataToString(delim).toStdString() << endl;
//        }
//        outFl.close();
//    }
//    catch (exception& e)
//    {
//        if (outFl.is_open())
//        {
//            outFl.close();
//        }
//        throw;
//    }

    LogFuncionEnd;
}

void MetadataTable::deleteNotDbRow()
{
    LogFuncionBegin;

    QVector<MetadataRow *> new_m_rows;

    for (int i = 0; i < (int)vectorRows_.size(); i++)
    {
        if (!vectorRows_[i]->isDeleted()) new_m_rows.push_back(vectorRows_[i]);
        else delete vectorRows_[i];
    }

    vectorRows_.clear();
    idStatus_.setValue(E_TAB_STAT_NONE);

    vectorRows_ = new_m_rows;

    LogFuncionEnd;
}

void MetadataTable::deleteRows()
{
    LogFuncionBegin;

    for (QVector<MetadataRow*>::iterator tabRow = vectorRows_.begin(); tabRow
            != vectorRows_.end(); ++tabRow)
    {
        delete *tabRow;
    }
    vectorRows_.clear();
    idStatus_.setValue(E_TAB_STAT_NONE);

    LogFuncionEnd;
}

MetadataRow * MetadataTable::findRowWithID(const int idToFind, const bool skipDeleted) const
{
    LogFuncionBegin;

    MetadataRow * foundRow = NULL;
    MetadataRow * currentRow = NULL;

    for (unsigned int rowNr = 1; rowNr <= (const unsigned int)vectorRows_.size(); rowNr++)
    {
        currentRow = getRow(rowNr);

        if (skipDeleted == true &&
            currentRow->isDeleted() == true) continue;

        if (currentRow->GetRowID() == idToFind)
        {
            foundRow = currentRow;
            break;
        }
    }

    LogFuncionEnd;

    return foundRow;
}

MetadataRow * MetadataTable::getRowWithFieldvalue(QString strToFind, QString columnName, bool skipDeleted)
{
    LogFuncionBegin;

    MetadataRow * foundRow = NULL;
    MetadataRow * currentRow = NULL;

    for (unsigned int rowNr = 1; rowNr <= (const unsigned int)vectorRows_.size(); rowNr++)
    {
        currentRow = getRow(rowNr);

        if (skipDeleted == true &&
            currentRow->isDeleted() == true) continue;

        if (currentRow->GetColumnValueString(columnName) == strToFind)
        {
            foundRow = currentRow;
            break;
        }
    }

    LogFuncionEnd;

    return foundRow;
}

MetadataRow * MetadataTable::getRowWithFieldvalue(int dValueToFind, QString columnName, bool skipDeleted)
{
    LogFuncionBegin;

    MetadataRow * foundRow = NULL;
    MetadataRow * currentRow = NULL;

    for (unsigned int rowNr = 1; rowNr <= (const unsigned int)vectorRows_.size(); rowNr++)
    {
        currentRow = getRow(rowNr);

        if (skipDeleted == true &&
            currentRow->isDeleted() == true) continue;

        if (currentRow->GetColumnValueInt(columnName) == dValueToFind)
        {
            foundRow = currentRow;
            break;
        }
    }

    LogFuncionEnd;

    return foundRow;
}

void MetadataTable::createDeserializeList()
{
    LogFuncionBegin;

    m_vDeserializeObjects.clear();
    addDeserializeObject(&idStatus_);
    addDeserializeObject(&strName_);
    addDeserializeObject(&serializeRows_);
    addDeserializeObject(&strWhereStatement);
    addDeserializeObject(&strOrderByStatement);
    addDeserializeObject(&vectorPkColumns);

    LogFuncionEnd;
}

void MetadataTable::createSerializeList()
{
    LogFuncionBegin;

    m_lstSerializeObjects.clear();
    addSerializeObject(&idStatus_, "status");
    addSerializeObject(&strName_, "name");
    addSerializeObject(&serializeRows_, "Rows");
    addSerializeObject(&strWhereStatement, "whereCond");
    addSerializeObject(&strOrderByStatement, "orderBy");
    addSerializeObject(&vectorPkColumns, "PKColumns");

    LogFuncionEnd;
}

void MetadataTable::loadTable()
{
    LogFuncionBegin;

    //Comprueba si la Tabla permite acceso a la Base de Datos
    if (ETableModeRam == mode_)
    {
        LogWarning() << "Cannot access to database in Table Ram mode";
        return;
    }

    //Declaracion de Varaibles
    QString strSqlStatement = "";
    QSqlQuery sqlQuery;

    //Create SQL statement
    strSqlStatement = SqlFactory::getSelectStatement(getName(), getWhere(), getOrderBy());

    //Ejecuta la sentancia Sql
    sqlQuery = QSqlQuery(strSqlStatement);
    if (!sqlQuery.isActive())
    {
        LogError() << "Query Failed: " << sqlQuery.lastQuery()  << sqlQuery.lastError().text();
        return;
    }

    //Load data into table object
    while (sqlQuery.next())
    {
        //Crea una nueva row
        MetadataRow *metadataRow = addRow();
        QVariant::Type columnType;

        //Establece que se carga de la bbdd
        metadataRow->setDbRow(true);

        //Recorre las columnas de la tabla
        QSqlRecord sqlRecord = sqlQuery.record();
        for (int colIdx = 0; colIdx < sqlRecord.count(); colIdx++)
        {
            //Obtiene el tipo de Valor
            QSqlField sqlField = sqlRecord.field(colIdx);
            columnType = sqlField.value().type();

            //Establece tipos homogeneos
            if (QVariant::LongLong == columnType) columnType = QVariant::Int;

            //Inserta el row en la tabla
            MetadataColumn *metadataColumn = metadataRow->addColumn(sqlField.name(), columnType);
            if (NULL == metadataColumn) {
                LogError() << "Error!! Cannot create [Column:" << sqlField.name() << "] in [Table:" << getName() << "]";
                continue;
            }

            //Establece el valor del row
            if (QVariant::Bool == columnType) metadataColumn->setValue(sqlQuery.value(colIdx).toBool(), false);
            else if (QVariant::Int == columnType) metadataColumn->setValue(sqlQuery.value(colIdx).toInt(), false);
            else if (QVariant::Double == columnType) metadataColumn->setValue(sqlQuery.value(colIdx).toDouble(), false);
            else metadataColumn->setValue(sqlQuery.value(colIdx).toString(), false);

            //Establece que la columna esta cargada
            metadataColumn->setLoaded();

            //If last fetched value was null set column to NULL
            metadataColumn->setNull(sqlQuery.isNull(colIdx), false);
        }
    }

    //Establece las claves primarias de la tablas
    stlPrimaryKeyColumns_ = DbManager::getInstance()->getTablePkColumns(getName()).toVector();

    LogFuncionEnd;
}

int MetadataTable::updateTable()
{
    LogFuncionBegin;

    //Comprueba si la Tabla permite acceso a la Base de Datos
    if (ETableModeReadWrite != mode_)
    {
        LogWarning() << "Cannot access to database without Table Read/Write mode";
        return false;
    }

    //Declaracion de Variables
    int intRowsUpdated = 0;
    unsigned int intRows = 0;
    QString strSqlStatement = "";

    //Recorre la lista de rows de la tabla
    intRows = getNumberOfRows();
    for (unsigned int rowNum = 1; rowNum <= intRows; rowNum++)
    {
        //Obtiene la row y comprueba si existe y tiene valor valido
        MetadataRow *metadataRow = getRow(rowNum);
        if (metadataRow == NULL) continue;

        //Reinicializacion de la sentencia
        strSqlStatement.clear();

        //Create SQL statement considering type of SQL operation
        if (metadataRow->isUpdated())
        {
            //Sentencia SQL de actualizacion de datos
            strSqlStatement = SqlFactory::getUpddateStatement(getName(),
                                        metadataRow->getUpdPairs(), getWhereByPK(rowNum));
        }
        else if (metadataRow->isDeleted())
        {
            //Do not delete rows not loaded from database
            if (metadataRow->isDbRow() == false) continue;

            //Sentencia SQL de eliminacion de datos
            strSqlStatement = SqlFactory::getDeleteStatement(getName(),
                                        getWhereByPK(rowNum));
        }
        else if (metadataRow->isNew())
        {
            //Sentencia SQL de insercion de datos
            strSqlStatement = SqlFactory::getInsertStatement(getName(),
                                        metadataRow->colNamesToString(','), metadataRow->dataToString(','));
        }

        //Check if DB operation could be performed
        if (!strSqlStatement.isEmpty())
        {
            LogDebug() << "Database statement: " << strSqlStatement;

            //Ejecuta la sentencia
            QSqlQuery sqlQuery(strSqlStatement);
            if (!sqlQuery.isActive())
            {
                LogError() << "Query Failed: " << sqlQuery.lastQuery() << sqlQuery.lastError().text();
            }
            if (sqlQuery.numRowsAffected() >= 0)
                intRowsUpdated += sqlQuery.numRowsAffected();
        }
    }

    LogFuncionEnd;

    return intRowsUpdated;
}

QString MetadataTable::getWhereByPK(const int & rowNum)
{
    LogFuncionBegin;

    //Declaracion de variables
    QString strWhereStat = "";
    bool booMissingPKColumn = false;
    MetadataColumn *metadataColumn = NULL;

    // get row which data will be used for where condition
    MetadataRow * tabRow = getRow(rowNum);

    //Comprueba si el row existe
    if (tabRow != NULL)
    {
        // for each column of primary key get data and it into where condition
        for (QVector<QString>::const_iterator colName = stlPrimaryKeyColumns_.begin();
                colName != stlPrimaryKeyColumns_.end(); ++colName)
        {
            metadataColumn = tabRow->getColumn(*colName);
            if (metadataColumn == NULL)
            {
                booMissingPKColumn = true;
                break;
            }
            // primary key column must be loaded. Should not be updated
            if (metadataColumn->isLoaded())
            {
                if (strWhereStat != "")
                    strWhereStat += " AND ";

                // handle null value
                if (metadataColumn->isNull())
                    strWhereStat += *colName + " IS NULL ";

                else {
                    strWhereStat += *colName + " = ";
                    if (metadataColumn->getDatatype() == MetadataColumn::E_CT_STRING) strWhereStat.append("'");
                    strWhereStat.append(metadataColumn->getValue());
                    if (metadataColumn->getDatatype() == MetadataColumn::E_CT_STRING) strWhereStat.append("'");
                }
            }
        }

        //The case if missing some PK column in table select, get all non updated
        //columns and compose WHERE condition from them
        if (booMissingPKColumn || stlPrimaryKeyColumns_.size() == 0)
        {
            strWhereStat = "";
            for (int colIdx = 1; colIdx <= tabRow->getNumberOfColumns(); colIdx++)
            {
                metadataColumn = tabRow->getColumn(colIdx);
                if (metadataColumn->isLoaded())
                {
                    if (strWhereStat != "")
                        strWhereStat += " AND ";

                    if (metadataColumn->isNull())
                        strWhereStat += metadataColumn->getName() + " IS NULL ";
                    else {
                        strWhereStat += metadataColumn->getName() + " = ";
                        if (metadataColumn->getDatatype() == MetadataColumn::E_CT_STRING) strWhereStat.append("'");
                        strWhereStat.append(metadataColumn->getValue());
                        if (metadataColumn->getDatatype() == MetadataColumn::E_CT_STRING) strWhereStat.append("'");
                    }
                }
            }
        }
    }

    LogFuncionEnd;

    return strWhereStat;
}
