#ifndef BLOCK_H
#define BLOCK_H
#include "scene_object.h"

class Block: public Scene_object
{
    Q_OBJECT
protected:
public:
    double block_speed;

    //to protection
    bool direction;//0-right to left, 1 left to right
public:
    explicit Block(int x,int y,bool direction,QString pixmap_path,QWidget* central_widget=0);
    virtual ~Block(){}

    void set_speed(double block_speed);//убрать?

    int get_speed();//убрать?
    bool get_direction();

    void make_step();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // BLOCK_H
