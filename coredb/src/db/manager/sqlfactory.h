#ifndef SqlFactory_H_
#define SqlFactory_H_

#include <QString>

/**
 * @brief Class provides methods that generate various SQL statements
 */
class SqlFactory
{
public:
    SqlFactory();
    virtual ~SqlFactory();

    /**
     * @brief Method generates SELECT statement of all columns of given table
     * */
    static QString getSelectStatement (const QString  & strTableName, const QString & strWhere = "",
                                       const QString & strOrderBy = "");

    /**
     * @brief Method generates SELECT statement for columns specified by array
     * of column names
     * */
    static QString getSelectColumnsStatement (const QString & strTableName, const QStringList & strColumns,
                                              const QString & strWhere = "", const QString & strOrderBy = "");
    /**
     * @brief Method generates INSERT statement with specified columns and data
     * */
    static QString getInsertStatement (const QString & strTableName, const QString & strColumns,
                                       const QString & strValues);

    /**
     * @brief Method generates UPDATE statement.
     * */
    static QString getUpddateStatement (const QString & strTableName, const QString & strSetPairs,
                                        const QString & strWhere = "");
    /**
     * @brief Method generates DELETE statement.
     * */
    static QString getDeleteStatement (const QString & strTableName, const QString & strWhere = "");

};

#endif /* SqlFactory_H_ */
