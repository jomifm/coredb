#include "xml/xmlnode.h"
#include "utils/logger/utilslogger.h"

XmlNode::XmlNode(XmlNode *pParentNode)
{    
    LogFuncionBegin;

    m_pParentNode = pParentNode;
    m_sNodeValue = "";

    LogFuncionEnd;
}

XmlNode::~XmlNode()
{
    LogFuncionBegin;

    for (QVector<XmlNode*>::iterator node = m_oChildNodes.begin();
            node != m_oChildNodes.end(); ++node) {
        delete *node;
    }

    m_oChildNodes.clear();

    LogFuncionEnd;
}

XmlNode* XmlNode::addChild()
{
    LogFuncionBegin;

    XmlNode *pNewNode = NULL;

    pNewNode = new XmlNode(static_cast<XmlNode*>(this));
    m_oChildNodes.push_back(pNewNode);

    LogFuncionEnd;

    return pNewNode;
}

XmlNode* XmlNode::getChild(const unsigned int & iChildIndex) const
{
    LogFuncionBegin;

    XmlNode* pRetValue = NULL;

    if (iChildIndex < (const unsigned int)m_oChildNodes.size())
        pRetValue = m_oChildNodes.at(iChildIndex);

    LogFuncionEnd;

    return pRetValue;
}

void XmlNode::addAttribute(const QString & strName, const QVariant & strValue)
{
    LogFuncionBegin;

    mapAtts.insert(strName, strValue);

    LogFuncionEnd;
}

void XmlNode::setAttribute(const QString & strName, const QVariant & strValue)
{
    LogFuncionBegin;

    QMap<QString,QVariant>::iterator iter;
    iter = mapAtts.find(strName);
    if (iter != mapAtts.end()) iter->setValue(strValue);

    LogFuncionEnd;
}

QVariant XmlNode::getAttribute(const QString & strName) const
{
    LogFuncionBegin;

    QVariant varProperty(QVariant::Invalid);

    QMap<QString,QVariant>::const_iterator iter;
    iter = mapAtts.find(strName);
    if (iter != mapAtts.end()) varProperty = QVariant(iter.value());

    LogFuncionEnd;

    return varProperty;
}
