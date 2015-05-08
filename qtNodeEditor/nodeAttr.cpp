#include "nodeAttr.h"

#include <QGraphicsScene>
#include <QFontMetrics>

#include <QPen>

#include "attrConnection.h"

NodeAttr::NodeAttr(QGraphicsItem *parent):
    QGraphicsPathItem(parent)
{
	label = new QGraphicsTextItem(this);

	radius_ = 5;
	margin = 2;

	QPainterPath p;
	p.addEllipse(-radius_, -radius_, 2*radius_, 2*radius_);
	setPath(p);

	setPen(QPen(Qt::darkRed));
	setBrush(Qt::red);

	setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

	m_attrFlags = 0;
}

NodeAttr::~NodeAttr()
{
	foreach(AttrConnection *conn, m_connections)
		delete conn;
}

void NodeAttr::setNodeBlock(NodeBlock *b)
{
	m_block = b;
}

void NodeAttr::setName(const QString &n)
{
	name = n;
	label->setPlainText(n);
}

void NodeAttr::setIsOutput(bool o)
{
	isOutput_ = o;

	QFontMetrics fm(scene()->font());
	QRect r = fm.boundingRect(name);

	if (isOutput_)
		label->setPos(-radius_ - margin - label->boundingRect().width(), -label->boundingRect().height()/2);
	else
		label->setPos(radius_ + margin, -label->boundingRect().height()/2);
}

int NodeAttr::radius()
{
	return radius_;
}

bool NodeAttr::isOutput()
{
	return isOutput_;
}

QVector<AttrConnection*>& NodeAttr::connections()
{
	return m_connections;
}

void NodeAttr::setAttrFlags(int f)
{
	m_attrFlags = f;

	if (m_attrFlags & TypePort)
	{
		QFont font(scene()->font());
		font.setItalic(true);
		label->setFont(font);
		setPath(QPainterPath());
	} else if (m_attrFlags & NamePort)
	{
		QFont font(scene()->font());
		font.setBold(true);
		label->setFont(font);
		setPath(QPainterPath());
	}
}

NodeBlock* NodeAttr::block() const
{
	return m_block;
}

quint64 NodeAttr::ptr()
{
	return m_ptr;
}

void NodeAttr::setPtr(quint64 p)
{
	m_ptr = p;
}

bool NodeAttr::isConnected(NodeAttr *other)
{
	foreach(AttrConnection *conn, m_connections)
		if (conn->attr1() == other || conn->attr2() == other)
			return true;

	return false;
}

QVariant NodeAttr::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemScenePositionHasChanged)
	{
		foreach(AttrConnection *conn, m_connections)
		{
			conn->updatePosFromPorts();
			conn->updatePath();
		}
	}
	return value;
}
