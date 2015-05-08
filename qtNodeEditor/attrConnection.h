#ifndef QNECONNECTION_H
#define QNECONNECTION_H

#include <QGraphicsPathItem>

class NodeAttr;

class AttrConnection : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 2 };

    AttrConnection(QGraphicsItem *parent = 0);
    ~AttrConnection();

	void setPos1(const QPointF &p);
	void setPos2(const QPointF &p);
    void setAttr1(NodeAttr *p);
    void setAttr2(NodeAttr *p);
	void updatePosFromPorts();
	void updatePath();
    NodeAttr* attr1() const;
    NodeAttr* attr2() const;

	void save(QDataStream&);
    void load(QDataStream&, const QMap<quint64, NodeAttr*> &);

	int type() const { return Type; }

private:
	QPointF pos1;
	QPointF pos2;
    NodeAttr *m_attr1;
    NodeAttr *m_attr2;
};

#endif // QNECONNECTION_H
