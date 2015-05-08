#ifndef QNEPORT_H
#define QNEPORT_H

#include <QGraphicsPathItem>

class NodeBlock;
class AttrConnection;

class NodeAttr : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 1 };
	enum { NamePort = 1, TypePort = 2 };

    NodeAttr(QGraphicsItem *parent = 0);
    ~NodeAttr();

    void setNodeBlock(NodeBlock*);
	void setName(const QString &n);
	void setIsOutput(bool o);
	int radius();
	bool isOutput();
    QVector<AttrConnection*>& connections();
    void setAttrFlags(int);

    const QString& attrName() const { return name; }
    int attrFlags() const { return m_attrFlags; }

	int type() const { return Type; }

	NodeBlock* block() const;

	quint64 ptr();
	void setPtr(quint64);

    bool isConnected(NodeAttr*);

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
	NodeBlock *m_block;
	QString name;
	bool isOutput_;
	QGraphicsTextItem *label;
	int radius_;
	int margin;
    QVector<AttrConnection*> m_connections;
    int m_attrFlags;
	quint64 m_ptr;
};

#endif // QNEPORT_H
