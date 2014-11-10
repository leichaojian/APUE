#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;

class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

//信号处理函数
private slots:
    void adjustViewSize();

private:
    void initScene();
    void initSceneBackground();

	//能够管理元素的非 GUI 容器
    QGraphicsScene *scene;
	//能够观察场景的可视化组件视图
    QGraphicsView *view;

    GameController *game;
};

#endif // MAINWINDOW_H
