#ifndef DATATEST_H
#define DATATEST_H

#include <coredb.h>

class DataTest : public SerializableObject
{
    Q_OBJECT
public:
    explicit DataTest(QObject *parent = 0);

    void addDummy();
    void testDummy();

    void deserializeConfigurationFile();

//    int getIntValue() { return intSerialValue_.getValue(); }
//    void setIntValue(int intValue) { intSerialValue_.setValue(intValue); }

//    QString getStrValue() { return QString::fromStdString(strSerialValue_.getValue()); }
//    void setStrValue(QString strValue) { strSerialValue_.setValue(strValue.toStdString()); }

    int getIntValue() { return intSerialValue_.getValue().toInt(); }
    void setIntValue(int intValue) { intSerialValue_.setValue(intValue); }

    QString getStrValue() { return strSerialValue_.getValue().toString(); }
    void setStrValue(QString strValue) { strSerialValue_.setValue(strValue); }

    QVariant getVarValue() { return dataVarSerialValue_.getValue(); }
    void setVarValue(QVariant varValue) { dataVarSerialValue_.setValue(varValue); }

    virtual void createSerializeList();
    virtual void createDeserializeList();

    IntSerialize intValue_;
    StringSerialize strValue_;
private:
    DataVariantSerialize intSerialValue_;
    DataVariantSerialize strSerialValue_;
    DataVariantSerialize dataVarSerialValue_;

signals:

public slots:

};

#endif // DATATEST_H
