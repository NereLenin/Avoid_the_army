#include "povistka.h"

Povistka::Povistka(int x, int y,QString pixmap_path, QWidget* central_widget)
    : Block(x,y,false,pixmap_path,central_widget)
{

   n_height = 9;
   width_per_height = 1.3;

}

void Povistka::make_step(Person *person=0)
{
    if(person == 0)
    {
        return;
    }

    Block::make_step();

    if((n_x >coord_max+5))
    {
      //  printf("yep\n");
        n_y = person->get_y() + (person->get_n_height()/3);
        block_speed+=0.01;
    }

}

bool Povistka::isDilivered(Person *person)
{

    //пересечение
    //если сейчас повестка перед ним
    //если после вычитания окажется за ним

    //если по высоте к игроку
    if( (n_y > (person->get_y()) && (n_y <(person->get_y())+(person->get_n_height()*0.6))))
    {
      //если пересекается ||
      //будет пересекаться на след шаге
      if((n_x <= (person->get_x() + (person->get_n_width()/2))&&(n_x >= person->get_x()))||
      ((n_x >= (person->get_x()))&&(n_x-block_speed <= (person->get_x()))) )
        {

            //n_x = person->get_x();
         //   qDebug() << "To reprint"<< endl;

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
