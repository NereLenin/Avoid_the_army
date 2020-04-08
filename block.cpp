#include "block.h"


Block::Block(int x, int y,bool direction,QString pixmap_path, QWidget* central_widget)
    : Moving_object(x, y, direction, pixmap_path,central_widget)

{
   i=0;
   n_height = 6;
   width_per_height = 4;

   speed =0.3;

   this->direction = direction;

   animation = false;
}

void Block::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit clicked();
}

void Block::start_animation()
{
    if(!animation)
        animation = true;
}

void Block::reprint()
{

    if(animation)
    {
            //qDebug() << n_height << " i " << i << endl;



            if(i < 4)
            {
                n_height+=0.125;
                i++;
            }else if(i < 8)
            {
                n_height-=0.125;
                i++;
            }
            else
            {
                animation = false;
                i=0;
            }

    }

    Moving_object::reprint();
}
