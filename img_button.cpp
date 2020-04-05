#include "img_button.h"

Img_button::Img_button(int x,int y,QString pixmap_path,QWidget *parent):
    Scene_object(x,y,pixmap_path,parent)
{
    n_height = 10;
    width_per_height = 1;
}

void Img_button::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit clicked();
}
