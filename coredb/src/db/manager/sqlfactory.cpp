#include "db/manager/sqlfactory.h"
#include "utils/logger/utilslogger.h"

#include <QStringList>

SqlFactory::SqlFactory()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

SqlFactory::~SqlFactory()
{
    LogFuncionBegin;
    LogFuncionEnd;
}

QString SqlFactory::getSelectStatement (const QString  & strTableName, const QString & strWhere,
                                        const QString & strOrderBy)
{
    LogFuncionBegin;

    //Declaracion de variables
    QString strStatement = "";

    //Composicion de la sentencia SQL
    strStatement = QString("SELECT * FROM %1").arg(strTableName);

    //Comprueba si introduce sentencia condicional
    if (!strWhere.isEmpty())
        strStatement.append(QString(" WHERE %1").arg(strWhere));

    //Comprueba si introduce sentencia de ordenacion
    if (!strOrderBy.isEmpty())
        strStatement.append(QString(" ORDER BY %1").arg(strOrderBy));

    //Finaliza la sentencia
    strStatement.append(";");

    LogFuncionEnd;

    return strStatement;
}

QString SqlFactory::getSelectColumnsStatement(const QString & strTableName, const QStringList & strColumns,
                                              const QString & strWhere, const QString & strOrderBy)
{
    LogFuncionBegin;

    //Declaracion de variables
    QString strStatement = "";
    QString strCols = "";

    //Prepara la seleccion de columnas
    for (QStringList::const_iterator col = strColumns.begin(); col != strColumns.end(); ++col)
    {
        if (!strCols.isEmpty()) strCols.append(", ");
        strCols.append(*col);
    }

    //Composicion de la sentencia SQL
    strStatement = QString("SELECT %1 FROM %2").arg(strCols).arg(strTableName);

    //Comprueba si introduce sentencia condicional
    if (!strWhere.isEmpty())
        strStatement.append(QString(" WHERE %1").arg(strWhere));

    //Comprueba si introduce sentencia de ordenacion
    if (!strOrderBy.isEmpty())
        strStatement.append(QString(" ORDER BY %1").arg(strOrderBy));

    //Finaliza la sentencia
    strStatement.append(";");

    LogFuncionEnd;

    return strStatement;
}

QString SqlFactory::getInsertStatement(const QString & strTableName, const QString & strColumns,
                                       const QString & strValues)
{
    LogFuncionBegin;

    //Declaracion de variables
    QString strStatement = "";

    //Composicion de la sentencia SQL
    strStatement  = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(strTableName).arg(strColumns).arg(strValues);

    //Finaliza la sentencia
    strStatement.append(";");

    LogFuncionEnd;

    return strStatement;
}

QString SqlFactory::getUpddateStatement(const QString & strTableName, const QString & strSetPairs,
                                        const QString & strWhere)
{
    LogFuncionBegin;


    //Declaracion de variables
    QString strStatement = "";

    //Composicion de la sentencia SQL
    strStatement = QString("UPDATE %1 SET %2").arg(strTableName).arg(strSetPairs);

    //Comprueba si introduce sentencia condicional
    if (!strWhere.isEmpty())
        strStatement.append(QString(" WHERE %1").arg(strWhere));

    //Finaliza la sentencia
    strStatement.append(";");

    LogFuncionEnd;

    return strStatement;
}

QString SqlFactory::getDeleteStatement(const QString & strTableName, const QString & strWhere)
{
    LogFuncionBegin;

    QString strStatement = "";

    //Composicion de la sentencia SQL
    strStatement = QString("DELETE FROM %1").arg(strTableName);

    //Comprueba si introduce sentencia condicional
    if (!strWhere.isEmpty())
        strStatement.append(QString(" WHERE %1").arg(strWhere));

    //Finaliza la sentencia
    strStatement.append(";");

    LogFuncionEnd;

    return strStatement;
}
