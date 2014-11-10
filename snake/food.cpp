#include <QPainter>

#include "constants.h"
#include "food.h"

static const qreal FOOD_RADIUS = 3;

Food::Food(qreal x, qreal y)
{
	//设置焦点
    setPos(x, y);
    setData(GD_Type, GO_Food);
}

QRectF Food::boundingRect() const
{
	//创建一个矩形(以(-TILE_SIZE,-TILE_SIZE)为中心，边长为TILE_SIZE * 2的正方形，起到包裹的作用)
    return QRectF(-TILE_SIZE,    -TILE_SIZE,
                   TILE_SIZE * 2, TILE_SIZE * 2 );
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
	//调用重载过的shape()
    painter->fillPath(shape(), Qt::red);

    painter->restore();
}

//绘制一个椭圆形
QPainterPath Food::shape() const
{
    QPainterPath p;
    p.addEllipse(QPointF(TILE_SIZE / 2, TILE_SIZE / 2), FOOD_RADIUS, FOOD_RADIUS);
    return p;
}
