#include "person.h"

Person::Person(int x, int y,QString image_path, QString jump_sound_path, QWidget* central_widget)
    : Scene_object(x,y,"",central_widget)
{
    n_height = 20;
    width_per_height = 0.64;

    stick_number = 0;
    animation_frame = 0;

    Animation = false;
    direction_jump = true; //left, true - to right

    sprite_straight = image_path;//начинаем игру со стоящим спрайтом повернутым вправо

    sprite_naklon =  sprite_jump = "";//по умолчанию обнуляем все остальные

    sprite_jump_l = sprite_straight_l = sprite_naklon_l = "";

    setStyleSheet(QString("image:url(%1);").arg(image_path));
    setScaledContents(false);

    jump_sound = new QSound(jump_sound_path,this);
}

void Person::setSprites(QString sprite_naklon, QString jump_sprite,
                        QString sprite_straight_l, QString sprite_naklon_l, QString sprite_jump_l)
{
    this->sprite_naklon = sprite_naklon;
    this->sprite_jump = jump_sprite;

    this->sprite_straight_l = sprite_straight_l;
    this->sprite_naklon_l = sprite_naklon_l;
    this->sprite_jump_l = sprite_jump_l;

}

double Person::get_form_y()
{
    return (parentWidget()->height())-((parentWidget()->height()/coord_max) * (n_y+(n_height*0.85)));
}
void Person::reprint()
{
    if(blocks != 0)//если блоки заданы
    {

    if(Animation)//если воспроизводится анимация, при перемещении на другой блок
    {

        //qDebug() << "animation true " << endl;
        //
        if(sprite_naklon!="" && sprite_jump != ""&&
           sprite_straight_l!="" && sprite_naklon_l != ""&& sprite_jump_l != "")//если текстуры спрайтов заданы
        {
        //rewrite this
        switch (animation_frame) {//на каких фрэймах анимации прыжка какой спрайт использовать
            case 1:
            if(direction_jump) setStyleSheet(QString("image:url(%1);").arg(sprite_naklon));//ставим чтобы наклонялся
            else setStyleSheet(QString("image:url(%1);").arg(sprite_naklon_l));//если направление прыжка левое ставим налево
            break;
            case 4://ждем 4 фрэйма
            if(direction_jump) setStyleSheet(QString("image:url(%1);").arg(sprite_jump));//ставим полет/падение
            else setStyleSheet(QString("image:url(%1);").arg(sprite_jump_l));
            break;
            case 12://на предпоследнем фрэйме
            if(direction_jump) setStyleSheet(QString("image:url(%1);").arg(sprite_straight));//ставим прямо
            else setStyleSheet(QString("image:url(%1);").arg(sprite_straight_l));
            break;
        }
        }

        animation_frame++;//увеличиваем фрэйм

        double t2_x,t2_y;//временные переменные для расчета конечной координаты

        if(animation_frame>4)
        {
        //определяем конечные координаты
        t2_x = blocks[stick_number-1]->get_x() + (blocks[stick_number-1]->get_n_width()/2) - (get_n_width()/2);//конечная по x
        t2_y = blocks[stick_number-1]->get_y() + (blocks[stick_number-1]->get_n_height());//конечная по y

        //идем часть 1/13 пути до конечной точки
        n_x = n_x + (((t2_x-n_x)/(14-animation_frame)));
        n_y = n_y + (((t2_y-n_y)/(14-animation_frame)));

        if(animation_frame >= 13)//если анимация прыжка на блок кончилась
        {
            //переносим в конечную точку(на всякий)
            n_x = blocks[stick_number-1]->get_x() + (blocks[stick_number-1]->get_n_width()/2) - (get_n_width()/2);
            n_y = blocks[stick_number-1]->get_y() + (blocks[stick_number-1]->get_n_height());

            //заканчиваем анимацию
            Animation = false;
            animation_frame = 0;
        }
      }

    }else if(stick_number != 0)//если анимации нет, но он привязан к блоку
    {
        //qDebug() << "stick yep" << endl;
        n_x = blocks[stick_number-1]->get_x() + (blocks[stick_number-1]->get_n_width()/2) - (get_n_width()/2);
        n_y = blocks[stick_number-1]->get_y() + (blocks[stick_number-1]->get_n_height());

         //если блок ушел за пределы окна а мы на нем
        if( (((blocks[stick_number-1]->get_x()+(blocks[stick_number-1]->get_n_width())/3) < 0)&& (!blocks[stick_number-1]->get_direction()) )|| ( (blocks[stick_number-1]->get_x() > coord_max-(blocks[stick_number-1]->get_n_width())/3)&& (blocks[stick_number-1]->get_direction())) )
        {
            stick_number = 0;//то мы скидываемся с блока
        }
    }
    else
    {
        //qDebug() << "stick no " << endl;

        if(n_y >0)//если мы не к чему не привязаны и анимации нет
        {
            //показываем спрайтом что падаем вниз
            if(sprite_jump != "" && sprite_jump_l!="")
            {
                if(direction_jump) setStyleSheet(QString("image:url(%1);").arg(sprite_jump));
                else setStyleSheet(QString("image:url(%1);").arg(sprite_jump_l));
            }
            n_y-=2;//падаем вниз до нуля или блока

            for(int i=0;i<block_count;i++)//смотрим не упал ли на какой блок
            {

                if((get_x()+get_n_width() > blocks[i]->get_x()  && get_x() < blocks[i]->get_x()+blocks[i]->get_n_width()) &&
                   get_y()<= blocks[i]->get_y()+blocks[i]->get_n_height() &&
                   get_y() >= blocks[i]->get_y())
                   //get_y()+get_n_height() > blocks[i]->get_y()+blocks[i]->get_n_height())
                {
                    //здесь спрайтом показывать что мы привязались не нужно тк set_StickNumber ее сам отметит
                    stopAnimation();
                    //stick_number = i+1;
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

    if(n_y < 6) //если упали до земли
    {
        if(sprite_straight != "" && sprite_straight_l!="")
        {
            if(direction_jump) setStyleSheet(QString("image:url(%1);").arg(sprite_straight));//становим прямо
            else setStyleSheet(QString("image:url(%1);").arg(sprite_straight_l));
        }
        n_y = 6;
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

         jump_sound->play();//включаем звук прыжка

         //если x середины блока больше чем середина персонажа, поворачиваем направо
         //false - налево, true - направо
         direction_jump =  (blocks[stick_number-1]->get_x() + (blocks[stick_number-1]->get_n_width()/2)) >= (get_x()+(get_n_width()/2));

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
