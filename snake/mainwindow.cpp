#include <QGraphicsView>
#include <QTimer>

#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(*scene, this))
{
    setCentralWidget(view);
    resize(600, 600);

    initScene();
    initSceneBackground();

	//在0msec后，执行this中的adjustViewSize函数
    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::adjustViewSize()
{
	//将矩形填充到整个场景中(initSceneBackground)---做测试的时候，可以把这句话屏蔽掉，确认此函数的功能是不是达到填充的作用
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
	//场景范围：左上角(-100, -100)，长和宽都是200的场景坐标系
    scene->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initSceneBackground()
{
	//TILE_SIZE为常量10，而整个场景的范围大小为200 * 200，所以总共有20 * 20个矩形
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
	//绘制左上角在(x, y)并且宽为w、高为h的矩形：drawRect(x, y, w, h)
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}
