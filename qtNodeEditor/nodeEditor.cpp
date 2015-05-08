#include "nodeEditor.h"

#include <QGraphicsScene>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "nodeAttr.h"
#include "attrConnection.h"
#include "nodeBlock.h"

#include <QWheelEvent>

NodeEditor::NodeEditor(QObject *parent) :
    QObject(parent)
{
	conn = 0;
}

void NodeEditor::install(QGraphicsScene *s, QGraphicsView *v)
{
	s->installEventFilter(this);
	scene = s;
    view = v;
}

QGraphicsItem* NodeEditor::itemAt(const QPointF &pos)
{
	QList<QGraphicsItem*> items = scene->items(QRectF(pos - QPointF(1,1), QSize(3,3)));

	foreach(QGraphicsItem *item, items)
		if (item->type() > QGraphicsItem::UserType)
			return item;

	return 0;
}

bool NodeEditor::eventFilter(QObject *o, QEvent *e)
{
	QGraphicsSceneMouseEvent *me = (QGraphicsSceneMouseEvent*) e;

	switch ((int) e->type())
	{
    case QEvent::GraphicsSceneWheel:{
        // Typical Calculations (Ref Qt Doc)
        QWheelEvent *event = (QWheelEvent *)e ;


        double sf = 1.15; //How fast we zoom
        if( event->delta() > 0) {
            view->scale(sf, sf);
        } else {
            view->scale(1/sf, 1/sf);
        }

        break;
    }
	case QEvent::GraphicsSceneMousePress:
	{

		switch ((int) me->button())
		{
		case Qt::LeftButton:
		{
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && item->type() == NodeAttr::Type)
			{
                conn = new AttrConnection(0);
                scene->addItem(conn);
				conn->setAttr1((NodeAttr*) item);
				conn->setPos1(item->scenePos());
				conn->setPos2(me->scenePos());
				conn->updatePath();

				return true;
			} else if (item && item->type() == NodeBlock::Type)
			{
				/* if (selBlock)
					selBlock->setSelected(); */
				// selBlock = (QNEBlock*) item;
			}
			break;
		}
		case Qt::RightButton:
		{
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && (item->type() == AttrConnection::Type || item->type() == NodeBlock::Type))
				delete item;
			// if (selBlock == (QNEBlock*) item)
				// selBlock = 0;
			break;
		}
		}
	}
	case QEvent::GraphicsSceneMouseMove:
	{
		if (conn)
		{
			conn->setPos2(me->scenePos());
			conn->updatePath();
			return true;
		}
		break;
	}
	case QEvent::GraphicsSceneMouseRelease:
	{
		if (conn && me->button() == Qt::LeftButton)
		{
			QGraphicsItem *item = itemAt(me->scenePos());
			if (item && item->type() == NodeAttr::Type)
			{
				NodeAttr *port1 = conn->attr1();
				NodeAttr *port2 = (NodeAttr*) item;

				if (port1->block() != port2->block() && port1->isOutput() != port2->isOutput() && !port1->isConnected(port2))
				{
					conn->setPos2(port2->scenePos());
					conn->setAttr2(port2);
					conn->updatePath();
					conn = 0;
					return true;
				}
			}

			delete conn;
			conn = 0;
			return true;
		}
		break;
	}
	}
	return QObject::eventFilter(o, e);
}

void NodeEditor::save(QDataStream &ds)
{
	foreach(QGraphicsItem *item, scene->items())
		if (item->type() == NodeBlock::Type)
		{
			ds << item->type();
			((NodeBlock*) item)->save(ds);
		}

	foreach(QGraphicsItem *item, scene->items())
		if (item->type() == AttrConnection::Type)
		{
			ds << item->type();
			((AttrConnection*) item)->save(ds);
		}
}

void NodeEditor::load(QDataStream &ds)
{
	scene->clear();

	QMap<quint64, NodeAttr*> portMap;

	while (!ds.atEnd())
	{
		int type;
		ds >> type;
		if (type == NodeBlock::Type)
		{
            NodeBlock *block = new NodeBlock(0);
            scene->addItem(block);
			block->load(ds, portMap);
		} else if (type == AttrConnection::Type)
		{
            AttrConnection *conn = new AttrConnection(0);
            scene->addItem(conn);
			conn->load(ds, portMap);
		}
	}
}
