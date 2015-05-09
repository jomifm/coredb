#include "db/metadata/metadatatabs.h"
#include "db/metadata/metadatatable.h"
#include "utils/logger/utilslogger.h"

MetadataTabs::MetadataTabs()
{
    LogFuncionBegin;

    //Inicializacion de variables
    setSerializationName("Tab");
    serializeTables_.setValue(&vectorTables_);
    serializeTables_.setSerializationName("Tables");

    LogFuncionEnd;
}

MetadataTabs::MetadataTabs(const QStringList & strListTables)
{
    LogFuncionBegin;

    //Inicializacion de variables
    setSerializationName("Tab");
    serializeTables_.setValue(&vectorTables_);
    serializeTables_.setSerializationName("Tables");

    //Crea las tablas con los nombres de la lista
    for (int i = 0; i < strListTables.count(); i++)
        vectorTables_.push_back(new MetadataTable(strListTables.at(i)));

    //Copia la lista de tablas
    stlTableNames_ = strListTables;

    LogFuncionEnd;
}

MetadataTabs::~MetadataTabs()
{
    LogFuncionBegin;

    //Elimina las tablas
    QVector<MetadataTable*>::iterator t;
    for(t = vectorTables_.begin(); t != vectorTables_.end(); ++t) {
        delete *t;
    }

    vectorTables_.clear();

    LogFuncionEnd;
}

MetadataTable* MetadataTabs::getTable(const QString & tabName) const
{
    LogFuncionBegin;

    //Declaracion de variables
    unsigned int tables = 0;
    MetadataTable* tab = NULL;

    //Recorre la lista de tablas
    tables = vectorTables_.size();
    for(unsigned int tabIdx = 0; tabIdx < tables; ++tabIdx)
    {
        //Obtiene la tabla y comprueba si nombre coincide
        tab = vectorTables_.at(tabIdx);
        if (tab != NULL && tab->getName() == tabName)
        {
            return tab;
        }
    }

    LogFuncionEnd;

    return 0;
}

MetadataTable* MetadataTabs::getTable(const int intTabIndex) const
{
    LogFuncionBegin;

    //Declaracion de variables
    MetadataTable * pRetTab = NULL;

    //Recorre la lista de tablas y comprueba el indice
    if (intTabIndex >= 0 && intTabIndex < vectorTables_.size())
        pRetTab = vectorTables_.at(intTabIndex);
    else pRetTab = NULL;

    LogFuncionEnd;

    return pRetTab;
}

void MetadataTabs::createDeserializeList()
{
    LogFuncionBegin;

    //Declaracion de variables
    QVector<MetadataTable*>::iterator t;

    m_vDeserializeObjects.clear();
    addDeserializeObject(&serializeTables_);
    for(t = vectorTables_.begin(); t != vectorTables_.end(); ++t)
    {
        delete *t;
    }
    vectorTables_.clear();

    LogFuncionEnd;
}

void MetadataTabs::createSerializeList()
{
    LogFuncionBegin;

    m_lstSerializeObjects.clear();
    addSerializeObject(&serializeTables_, "Tables");

    LogFuncionEnd;
}

void MetadataTabs::restart(const QString & strTableName)
{
    LogFuncionBegin;

    //Declaracion de variables
    QVector<MetadataTable*>::iterator iter;
    QVector<MetadataTable*>::iterator iter2;

    //Recorre la lista de tablas
    for(iter = vectorTables_.begin(); iter != vectorTables_.end(); ++iter)
    {
        //Comprueba el nombre de la tabla
        if ((*iter)->getName() == strTableName)
        {
            //Elimina la tabla existente y crea una nueva en memoria
            delete *iter;
            iter2 = vectorTables_.erase(iter);
            vectorTables_.insert(iter2, new MetadataTable(strTableName));
            break;
        }
    }

    LogFuncionEnd;
}

void MetadataTabs::clear (const QStringList & stlExcludeOptionalTables)
{
    LogFuncionBegin;

    QString tableName = "";
    QVector<MetadataTable*>::iterator t;
    QStringList::const_iterator lnm;
    bool clearIt = false;

    for(t = vectorTables_.begin(); t != vectorTables_.end(); ++t)
    {
        clearIt = true;
        if (stlExcludeOptionalTables.empty() != true)
        {
            tableName = (*t)->getName();
            //lnm = find (excludeTables.begin(), excludeTables.end(), tableName);
            for(lnm = stlExcludeOptionalTables.begin(); lnm != stlExcludeOptionalTables.end(); ++lnm)
                if ((*lnm) == tableName) break;
            if (lnm != stlExcludeOptionalTables.end())
            {
                clearIt = false;
            }
        }
        if (clearIt)
        {
            (*t)->deleteRows();
        }
    }

    LogFuncionEnd;
}
