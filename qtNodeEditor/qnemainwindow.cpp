#include "qnemainwindow.h"
#include "ui_qnemainwindow.h"

#include "nodeBlock.h"
#include "nodeEditor.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileDialog>
#include <QTextEdit>

#include "attr.h"
#include "nodeAttr.h"

#include <QDebug>

QNEMainWindow::QNEMainWindow(QWidget *parent) :
    QMainWindow(parent)
{


    scene = new QGraphicsScene();


    QAction *quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    QAction *loadAct = new QAction(tr("&Load"), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Open a file"));
    connect(loadAct, SIGNAL(triggered()), this, SLOT(loadFile()));

    QAction *saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save a file"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    QAction *addAct = new QAction(tr("&Add"), this);
    addAct->setStatusTip(tr("Add a block"));
    connect(addAct, SIGNAL(triggered()), this, SLOT(addBlock()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addAct);
    fileMenu->addAction(loadAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    setWindowTitle(tr("Node Editor"));

    QDockWidget *dock = new QDockWidget(tr("Nodes"), this);
    view = new QGraphicsView(dock);
    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing, true);

    dock->setWidget(view);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    QDockWidget *dock1 = new QDockWidget(tr("Empty"), this);
    QDockWidget *dock2 = new QDockWidget(tr("Empty"), this);
    addDockWidget(Qt::RightDockWidgetArea, dock1);
    addDockWidget(Qt::RightDockWidgetArea, dock2);

    setDockOptions(AllowNestedDocks);
    setDockOptions(VerticalTabs);

    nodesEditor = new NodeEditor(this);
    nodesEditor->install(scene, view);

    AttrList * a1 = new AttrList();
    a1->addAttr(new Attr("i1", "inAtrr1",  Attr::FLOAT));
    a1->addAttr(new Attr("i2", "inAtrr2",  Attr::FLOAT));
    a1->addAttr(new Attr("i3", "inAtrr3",  Attr::FLOAT));
    a1->addAttr(new Attr("i4", "inAtrr4",  Attr::FLOAT));

    a1->addAttr(new Attr("o1", "outAtrr1", Attr::FLOAT, true));
    a1->addAttr(new Attr("o2", "outAtrr2", Attr::FLOAT, true));

    NodeBlock *b = new NodeBlock(a1, 0);
    scene->addItem(b);

    foreach(auto x , a1->orderVector){
      b->addAttr(x->longName, x->isOutput);
    }

    b = b->clone();
    b->setPos(150, 0);

    b = b->clone();
    b->setPos(150, 150);

}

QNEMainWindow::~QNEMainWindow()
{

}

void QNEMainWindow::saveFile()
{
	QString fname = QFileDialog::getSaveFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::WriteOnly);
	QDataStream ds(&f);
	nodesEditor->save(ds);
}

void QNEMainWindow::loadFile()
{
	QString fname = QFileDialog::getOpenFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::ReadOnly);
	QDataStream ds(&f);
	nodesEditor->load(ds);
}

void QNEMainWindow::addBlock()
{
    NodeBlock *b = new NodeBlock(0);

    scene->addItem(b);
	static const char* names[] = {"Vin", "Voutsadfasdf", "Imin", "Imax", "mul", "add", "sub", "div", "Conv", "FFT"};
	for (int i = 0; i < 4 + rand() % 3; i++)
	{
		b->addAttr(names[rand() % 10], rand() % 2, 0, 0);
        b->setPos(view->sceneRect().center().toPoint());
	}
}
