#include "block.h"



Block::Block(int x, int y,bool direction,QString pixmap_path, QWidget* central_widget)
    : Scene_object(x,y,pixmap_path,central_widget)
{

   n_height = 6;
   width_per_height = 4;

   block_speed =0.2;

   this->direction = direction;
}





void Block::set_speed(double block_speed)
{
    this->block_speed = block_speed;
}

int Block::get_speed()
{
    return block_speed;
}


void Block::make_step()
{
      if(direction) n_x += block_speed;
    else n_x-=block_speed;
    //проверку на выход за границу можно сюда сунуть так то

    if((!direction)&&(n_x+get_n_width()) <=-10)
    {

       //int rand = 1+rand()%50;//потом

       n_x = coord_max+get_n_width();
    }

    if((direction)&& (n_x) >= coord_max+get_n_width())
    {

       //int rand = 1+rand()%50;//потом

       n_x = 0-get_n_width();
    }


}

/*Block::~Block()
{

}*/

void Block::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
