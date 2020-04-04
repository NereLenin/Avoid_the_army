#include "person.h"

Person::Person(int x, int y,QString image_path, QWidget* central_widget)
    : Scene_object(x,y,"",central_widget)
{
    n_height = 20;
    width_per_height = 0.64;

    stick_number = 0;
    animation_frame = 0;

    Animation = false;

    setStyleSheet(QString("image:url(%1);").arg(image_path));
    setScaledContents(false);
    //show();
}

int Person::get_form_y()
{
    //10 - tirrain height
    return (parentWidget()->height())-((parentWidget()->height()/coord_max) * (10+n_y+(n_height*0.85)));
}
void Person::reprint()
{
    if(blocks != 0)
    {

    if(Animation)//если воспроизводится анимация, при перемещении на другой блок
    {

        //qDebug() << "animation true " << endl;

        animation_frame++;

        int t2_x,t2_y;

        //определяем конечные координаты
        t2_x = blocks[stick_number-1]->get_x() + (blocks[stick_number-1]->get_n_width()/5);
        t2_y = blocks[stick_number-1]->get_y() + (blocks[stick_number-1]->get_n_height());

        //идем часть 1/10 пути до конечной точки
        n_x = n_x + (((t2_x-n_x)/(11-animation_frame)));
        n_y = n_y + (((t2_y-n_y)/(11-animation_frame)));

        if(animation_frame >= 10)
        {
            //переносим в конечную точку(на всякий)
            n_x = blocks[stick_number-1]->get_x() + (blocks[stick_number-1]->get_n_width()/5);
            n_y = blocks[stick_number-1]->get_y() + (blocks[stick_number-1]->get_n_height());

            //заканчиваем анимацию
            Animation = false;
            animation_frame = 0;
        }

    }else if(stick_number != 0)//если анимации нет, но он привязан к блоку
    {
        //qDebug() << "stick yep" << endl;
        n_x = blocks[stick_number-1]->get_x() + (blocks[stick_number-1]->get_n_width()/5);
        n_y = blocks[stick_number-1]->get_y() + (blocks[stick_number-1]->get_n_height());

         //если блок ушел за пределы окна а мы на нем
        if( (((blocks[stick_number-1]->get_x()+blocks[stick_number-1]->get_n_width()) < 0)&& (!blocks[stick_number-1]->direction) )|| ( (blocks[stick_number-1]->get_x() > coord_max)&& (blocks[stick_number-1]->direction )) )
        {
            stick_number = 0;//то мы скидываемся с блока
        }
    }
    else
    {
        //qDebug() << "stick no " << endl;

        if(n_y >0)//если мы не к чему не привязаны и анимации нет
        {
            n_y-=2;//падаем вниз до нуля или блока

            for(int i=0;i<block_count;i++)//смотрим не упал ли на какой блок
            {
                if(blocks[i]->get_x() <= get_x() && blocks[i]->get_x()+blocks[i]->get_n_width() >= get_x() &&
                   blocks[i]->get_y() <= get_y())
                {
                    set_StickNumber(i+1);//если упал привязываем
                }
            }


        }

    }

    }//end blocks not null check

    if(n_x < 0)//если блок убегает влево вместе с нами
    {
        n_x = 0;
    }
    if(n_x+get_n_width() > coord_max)//если блок убегает вправо вместе с нами
    {
        n_x = coord_max-get_n_width();
    }


    setGeometry(get_form_x(),get_form_y(),get_form_width(),get_form_height());
}

void Person::set_StickNumber(int block_number)
{
    //если перемещаемся не на тот же самый блок
    //и уже анимация не запущена

    if(stick_number != block_number && !Animation)
    {
        stick_number = block_number;
         Animation = true;

        //Animation = (stick_number!=0);

    }

}

int Person::get_StickNumber()
{
    return stick_number;
}

void Person::SetBlocksToStick(Block **blocks, int block_count)
{
    this->blocks = blocks;
    this->block_count = block_count;
}

void Person::stopAnimation()
{
    stick_number = 0;
    Animation = false;
    animation_frame=0;
}
