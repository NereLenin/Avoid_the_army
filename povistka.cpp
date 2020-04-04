#include "povistka.h"

Povistka::Povistka(int x, int y,QString pixmap_path, QWidget* central_widget)
    : Moving_object(x,y,false,pixmap_path,central_widget)
{

   recipient = 0;
   n_height = 9;
   width_per_height = 1.3;

}


void Povistka::SetRecipient(Person *person)
{
    if(person == 0) return;

    recipient = person;


}
void Povistka::reprint()
{
    if(recipient == 0)
    {
        return;
    }


    if((n_x >coord_max+5))
    {
        n_y = recipient->get_y() + (recipient->get_n_height()/3);
        speed+=0.01;
    }

    Moving_object::reprint();
}

bool Povistka::isDilivered()
{

    //пересечение
    //если сейчас повестка перед ним
    //если после вычитания окажется за ним

    //если по высоте к игроку
    if( (n_y > (recipient->get_y()) && (n_y <(recipient->get_y())+(recipient->get_n_height()*0.6))))
    {
      //если пересекается ||
      //будет пересекаться на след шаге
      if((n_x <= (recipient->get_x() + (recipient->get_n_width()/2))&&(n_x >= recipient->get_x()))||
      ((n_x >= (recipient->get_x()))&&(n_x-speed <= (recipient->get_x()))) )
        {

         //   qDebug() << "gotcha povistka x:" << n_x << " y:" << n_y << endl;
         //   qDebug() << "person x:" << person->get_x() << " y:" << person->get_y() << endl;

            return true;
        }
        else
        {
          //  qDebug() << "not gotcha povistka x:" << n_x << " y:" << n_y << endl;
          //  qDebug() << "person x:" << person->get_x() << " y:" << person->get_y() << endl;

        }
     }
    return false;
}


void Povistka::reset_speed()
{
    Moving_object::speed = 0.2;
}
