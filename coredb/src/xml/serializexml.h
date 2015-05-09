#ifndef SerializeXml_H_
#define SerializeXml_H_

#include <QtCore/QString>
#include <QtCore/QVector>

/**
 * @brief Class SerializeXml is main parent class used to serialize
 *        inherited classes
 * */
class SerializeXml
{
public:
    /**
     * @brief default constructor
     * */
    SerializeXml();

    /**
     * @brief default denstructor
     * */
    virtual ~SerializeXml();

    /**
     * @brief return object's serialization name
     * */
    QString getSerializationName() const { return m_sSerializationName; }

    /**
     * @brief set object's deserialization name
     * */
    void setSerializationName(const QString & sSerializationName) { m_sSerializationName = sSerializationName; }

    /**
     * @brief called by main serialization class
     *        for identification of serialization objects
     * */
    bool addSerializeObject(SerializeXml* oObject, const QString & sSerializationName);

    /**
     * @brief entry call for class serialization
     * */
    QString serializeAll();

    /**
     * @brief responsible for correct object > string serialization
     * */
    virtual QString serialize();

    /**
     * @brief is called to create list of objects for serialization
     * */
    virtual void createSerializeList();

protected:
    /* serialization name */
    QString m_sSerializationName;

    /* list of objects to serialize */
    QVector<SerializeXml*> m_lstSerializeObjects;

    QString serializeSpecialChars(const QString & srcStr);
};

#endif /* SerializeXml_H_ */
