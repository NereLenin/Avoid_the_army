#include "captures.h"
#include <QDebug>

Captures::Captures(QString yes_img, QString no_img,QWidget *parent) :
    Scene_object(0,0,"",parent)
{
    //this->start_text = start_text;
    //this->end_text = end_text;

    setFont(QFont("Courier 10 Pitch",20,QFont::Bold));
    setAlignment(Qt::AlignCenter);

    //просто this конструктор?
    setStyleSheet("background-color: rgba(1,1,1, 0.99);color:white;");
    start_scene = end_scene = false;
    i=0;

    yes = new Img_button(75,10,yes_img,this);
    no = new Img_button(10,10,no_img,this);
    yes->show();
    no->show();
}

Img_button* Captures::get_yes_btn()
{
    return yes;
}


Img_button* Captures::get_no_btn()
{
    return no;
}

void Captures::set_current_text(QString text)
{
    setText(text);
}

void Captures::new_resize()
{

    resize(parentWidget()->size());

    yes->new_resize();
    no->new_resize();
}

void Captures::reprint()
{


    if(start_scene)
    {
         if(i<0.95)//просветление по красоте
        {
           yes->hide();
           no->hide();
          setStyleSheet(QString("background-color: rgba(1,1,1, %1);color:white;").arg((0.99-i)));
        i+=0.01;
        }
        else
        {
            hide();
            i=0;
            start_scene = false;
        }
    }else if(end_scene)
    {
        if(i<0.99)//затемнение по красоте
        {
        setStyleSheet(QString("background-color: rgba(1,1,1, %1);color:white;").arg(i));

        i+=0.01;
        }
        else{

            yes->show();
            no->show();
            end_scene = false;
            i=0;
        }
    }


}
void Captures::hide()
{
    yes->hide();
    no->hide();

    QLabel::hide();
}

bool Captures::get_start_scene()
{
    return  start_scene;
}


bool Captures::get_end_scene()
{
    return  end_scene;
}

void Captures::show_start_scene()
{
    start_scene = true;
    end_scene = false;
    show();
}

void Captures::show_end_scene()
{
    start_scene = false;
    end_scene = true;
    setStyleSheet("background-color: rgba(1,1,1, 0);color:white;");
    show();
}
