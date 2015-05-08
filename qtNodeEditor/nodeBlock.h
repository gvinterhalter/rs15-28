#ifndef QNEBLOCK_H
#define QNEBLOCK_H

#include <QGraphicsPathItem>
#include "attr.h"

class NodeAttr;

class NodeBlock : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 3 };

    NodeBlock(AttrList *al = 0, QGraphicsItem * parent = 0);

    NodeAttr* addAttr(const QString &name, bool isOutput, int flags = 0, int ptr = 0);
    void NodeBlock::addInput(const QString &name) { addAttr(name, false); }
    void NodeBlock::addOutput(const QString &name) { addAttr(name, true); }
    void NodeBlock::addInputs(const QStringList &names) { foreach(QString n, names) addInput(n); }
    void NodeBlock::addOutpus(const QStringList &names) { foreach(QString n, names) addOutput(n); }

	void save(QDataStream&);
    void load(QDataStream&, QMap<quint64, NodeAttr*> &attrMap);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    NodeBlock * clone();
    QVector<NodeAttr*> ports();

	int type() const { return Type; }


protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);


private:
	int horzMargin;
	int vertMargin;
	int width;
	int height;
    AttrList * attributes;
};

#endif // QNEBLOCK_H
