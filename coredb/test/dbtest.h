#ifndef DbTest_H
#define DbTest_H

#include <coredb.h>

class DbTest : public SerializableObject
{
    Q_OBJECT
public:
    explicit DbTest(QObject *parent = 0);

    void testSqlStatements();

    void createDatabaseSchema();
    void setDatabaseDummyData();
    void showDatabaseDummyData();

};

#endif // DbTest_H
