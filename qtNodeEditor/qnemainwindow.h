#ifndef QNEMAINWINDOW_H
#define QNEMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>


class NodeEditor;

class QNEMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit QNEMainWindow(QWidget *parent = 0);
	~QNEMainWindow();

private slots:
	void saveFile();
	void loadFile();
	void addBlock();

private:

	NodeEditor *nodesEditor;
    QMenu *fileMenu;
    QGraphicsView *view;
    QGraphicsScene *scene;
};

#endif // QNEMAINWINDOW_H
