#ifndef CXMLNODE_H_
#define CXMLNODE_H_

#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVector>

class XmlNode
{
public:
    XmlNode(XmlNode *pParentNode);
    virtual ~XmlNode();

    XmlNode* getParent() const { return m_pParentNode; }

    XmlNode* addChild();
    int getChildCount() const { return m_oChildNodes.size(); }
    XmlNode* getChild(const unsigned int & iChildIndex) const;

    QString getNodeValue() const { return m_sNodeValue; }
    void setValue(const QString & sValue) { m_sNodeValue = sValue; }

    void addAttribute(const QString & strName, const QVariant & strValue);
    void setAttribute(const QString & strName, const QVariant & strValue);
    QVariant getAttribute(const QString & strName) const;

private:
    QString m_sNodeValue;
    QVector<XmlNode*> m_oChildNodes;
    XmlNode *m_pParentNode;
    QMap<QString,QVariant> mapAtts;
};

#endif /* CXMLNODE_H_ */
