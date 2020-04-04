#include "scene_object.h"

Scene_object::Scene_object(int x, int y,QString pixmap_path,QWidget* central_widget)
    : QLabel(central_widget)
{

    n_x=x;
    n_y=y;

    n_height = 1;
    width_per_height = 1;

    coord_max = 100;

    setScaledContents(true);
    setPixmap(QPixmap(pixmap_path));
    show();
}


void Scene_object::set_x(double x)
{
    n_x = x;
}
void Scene_object::set_y(double y)
{
    n_y = y;
}

void Scene_object::set_height(double height)
{
    n_height = height;
}

void Scene_object::set_width_per_height(double width_per_height)
{
    this->width_per_height = width_per_height;
}
double Scene_object::get_form_x()
{

    return (parentWidget()->width()/coord_max) * (n_x);
}

double Scene_object::get_form_y()
{
    return (parentWidget()->height())-((parentWidget()->height()/coord_max) * (n_y+n_height));
}


double Scene_object::get_x()
{
    return n_x;
}

double Scene_object::get_y()
{
    return n_y;
}

double Scene_object::get_form_width()//make width per height
{
        return (width_per_height*n_height)*((parentWidget()->height())/coord_max);
}

double Scene_object::get_form_height()
{

        return (n_height)*((parentWidget()->height())/coord_max);

}


double Scene_object::get_n_width()
{
        return get_form_width()/(parentWidget()->width()/coord_max);
}

double Scene_object::get_n_height()
{
    return n_height;
}
void Scene_object::new_resize()//убрать?
{
    setGeometry(get_form_x(),get_form_y(),get_form_width(),get_form_height());
}

void Scene_object::reprint()
{
    setGeometry(get_form_x(),get_form_y(),get_form_width(),get_form_height());
}

