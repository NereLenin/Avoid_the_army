#include "moving_object.h"

Moving_object::Moving_object(int x, int y,bool direction,QString pixmap_path, QWidget* central_widget)
    : Scene_object(x,y,pixmap_path,central_widget)
{

   speed =0.2;

   this->direction = direction;
}


bool Moving_object::get_direction()
{
    return  direction;
}

void Moving_object::reprint()
{
    if(direction) n_x += speed;
    else n_x-=speed;
  //проверку на выход за границу можно сюда сунуть так то

  if((!direction)&&(n_x+get_n_width()) <=0-get_n_width())
  {

     //int rand = 1+rand()%50;//потом

     n_x = coord_max+get_n_width();
  }

  if((direction)&& (n_x) >= coord_max+get_n_width())
  {

     //int rand = 1+rand()%50;//потом

     n_x = 0-get_n_width();
  }

    Scene_object::reprint();
}
