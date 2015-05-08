#include "attrConnection.h"

#include "nodeAttr.h"

#include <QBrush>
#include <QPen>
#include <QGraphicsScene>

AttrConnection::AttrConnection(QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
	setPen(QPen(Qt::black, 2));
	setBrush(Qt::NoBrush);
	setZValue(-1);
	m_attr1 = 0;
	m_attr2 = 0;
}

AttrConnection::~AttrConnection()
{
	if (m_attr1)
		m_attr1->connections().remove(m_attr1->connections().indexOf(this));
	if (m_attr2)
		m_attr2->connections().remove(m_attr2->connections().indexOf(this));
}

void AttrConnection::setPos1(const QPointF &p)
{
	pos1 = p;
}

void AttrConnection::setPos2(const QPointF &p)
{
	pos2 = p;
}

void AttrConnection::setAttr1(NodeAttr *p)
{
	m_attr1 = p;

	m_attr1->connections().append(this);
}

void AttrConnection::setAttr2(NodeAttr *p)
{
	m_attr2 = p;

	m_attr2->connections().append(this);
}

void AttrConnection::updatePosFromPorts()
{
	pos1 = m_attr1->scenePos();
	pos2 = m_attr2->scenePos();
}

void AttrConnection::updatePath()
{
	QPainterPath p;

	//QPointF pos1(m_port1->scenePos());
	//QPointF pos2(m_port2->scenePos());

	p.moveTo(pos1);

	qreal dx = pos2.x() - pos1.x();
	qreal dy = pos2.y() - pos1.y();

	QPointF ctr1(pos1.x() + dx * 0.25, pos1.y() + dy * 0.1);
	QPointF ctr2(pos1.x() + dx * 0.75, pos1.y() + dy * 0.9);

	p.cubicTo(ctr1, ctr2, pos2);

	setPath(p);
}

NodeAttr* AttrConnection::attr1() const
{
	return m_attr1;
}

NodeAttr* AttrConnection::attr2() const
{
	return m_attr2;
}

void AttrConnection::save(QDataStream &ds)
{
	ds << (quint64) m_attr1;
	ds << (quint64) m_attr2;
}

void AttrConnection::load(QDataStream &ds, const QMap<quint64, NodeAttr*> &attrMap)
{
	quint64 ptr1;
	quint64 ptr2;
	ds >> ptr1;
	ds >> ptr2;

    setAttr1(attrMap[ptr1]);
    setAttr2(attrMap[ptr2]);
	updatePosFromPorts();
	updatePath();
}
