#ifndef IMG_BUTTON_H
#define IMG_BUTTON_H
#include "scene_object.h"

class Img_button: public Scene_object
{
    Q_OBJECT
protected:
        void mousePressEvent(QMouseEvent* event);
public:
    Img_button(int x,int y,QString pixmap_path,QWidget *parent);

signals:
    void clicked();
};

#endif // IMG_BUTTON_H
