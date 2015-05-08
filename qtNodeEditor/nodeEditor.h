#ifndef QNODESEDITOR_H
#define QNODESEDITOR_H

#include <QObject>
#include <QGraphicsView>

class QGraphicsScene;
class AttrConnection;
class QGraphicsItem;
class QPointF;
class NodeBlock;

class NodeEditor : public QObject
{
	Q_OBJECT
public:
    explicit NodeEditor(QObject *parent = 0);

    void install(QGraphicsScene *scene, QGraphicsView *v);

	bool eventFilter(QObject *, QEvent *);

	void save(QDataStream &ds);
	void load(QDataStream &ds);

private:
	QGraphicsItem *itemAt(const QPointF&);

private:
	QGraphicsScene *scene;
    QGraphicsView  *view;
    AttrConnection *conn;
	// QNEBlock *selBlock;
};

#endif // QNODESEDITOR_H
