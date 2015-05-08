#include "nodeBlock.h"

#include <QPen>
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPainter>

#include "nodeAttr.h"
#include <QDebug>

NodeBlock::NodeBlock(AttrList *al, QGraphicsItem *parent) : QGraphicsPathItem(parent)
{
	QPainterPath p;
	p.addRoundedRect(-50, -15, 100, 30, 5, 5);
	setPath(p);
	setPen(QPen(Qt::darkGreen));
	setBrush(Qt::green);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	horzMargin = 20;
	vertMargin = 5;
	width = horzMargin;
	height = vertMargin;

    attributes = al;
}

NodeAttr* NodeBlock::addAttr(const QString &name, bool isOutput, int flags, int ptr)
{
    NodeAttr *port = new NodeAttr(this);
	port->setName(name);
	port->setIsOutput(isOutput);
    port->setNodeBlock(this);
    port->setAttrFlags(flags);
	port->setPtr(ptr);


	QFontMetrics fm(scene()->font());
	int w = fm.width(name);
	int h = fm.height();
	// port->setPos(0, height + h/2);
	if (w > width - horzMargin)
		width = w + horzMargin;
	height += h;


	QPainterPath p;
	p.addRoundedRect(-width/2, -height/2, width, height, 5, 5);
	setPath(p);


	int y = -height / 2 + vertMargin + port->radius();
    foreach(QGraphicsItem *port_, childItems()) {
        if (port_->type() != NodeAttr::Type)
			continue;

        NodeAttr *port = (NodeAttr*) port_;
		if (port->isOutput())
			port->setPos(width/2 + port->radius(), y);
		else
			port->setPos(-width/2 - port->radius(), y);
		y += h;
	}

	return port;
}


void NodeBlock::save(QDataStream &ds)
{
	ds << pos();

	int count(0);

    foreach(QGraphicsItem *port_, childItems())
	{
        if (port_->type() != NodeAttr::Type)
			continue;

		count++;
	}

	ds << count;

    foreach(QGraphicsItem *port_, childItems())
	{
        if (port_->type() != NodeAttr::Type)
			continue;

        NodeAttr *port = (NodeAttr*) port_;
		ds << (quint64) port;
        ds << port->attrName();
		ds << port->isOutput();
        ds << port->attrFlags();
	}
}

void NodeBlock::load(QDataStream &ds, QMap<quint64, NodeAttr*> &attrMap)
{
	QPointF p;
	ds >> p;
	setPos(p);
	int count;
	ds >> count;
	for (int i = 0; i < count; i++)
	{
		QString name;
		bool output;
		int flags;
		quint64 ptr;

		ds >> ptr;
		ds >> name;
		ds >> output;
		ds >> flags;
        attrMap[ptr] = addAttr(name, output, flags, ptr);
	}
}

#include <QStyleOptionGraphicsItem>

void NodeBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)

	if (isSelected()) {
		painter->setPen(QPen(Qt::darkYellow));
		painter->setBrush(Qt::yellow);
	} else {
		painter->setPen(QPen(Qt::darkGreen));
		painter->setBrush(Qt::green);
	}

	painter->drawPath(path());
}

NodeBlock* NodeBlock::clone()
{
    NodeBlock *b = new NodeBlock(attributes, 0);
    this->scene()->addItem(b);

    foreach(QGraphicsItem *port_, childItems())
    {
        if (port_->type() == NodeAttr::Type)
        {
            NodeAttr *port = (NodeAttr*) port_;
            b->addAttr(port->attrName(), port->isOutput(), port->attrFlags(), port->ptr());
        }
    }

	return b;
}

QVector<NodeAttr*> NodeBlock::ports()
{
    QVector<NodeAttr*> res;
	foreach(QGraphicsItem *port_, childItems())
	{
        if (port_->type() == NodeAttr::Type)
            res.append((NodeAttr*) port_);
	}
	return res;
}

QVariant NodeBlock::itemChange(GraphicsItemChange change, const QVariant &value)
{

    Q_UNUSED(change);

	return value;
}

