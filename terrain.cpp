#include "terrain.h"

Terrain::Terrain(int height,QString pixmap_path, QWidget* central_widget)
    : Scene_object(0,height,pixmap_path,central_widget)
{
    n_height = n_y = height;

}

void Terrain::new_resize()
{
    //resize(get_form_width(),get_form_height());
    setGeometry(0,get_form_y(),parentWidget()->width(),get_form_height());
}

int Terrain::get_form_y()
{
    return (parentWidget()->height())-((parentWidget()->height()/coord_max) * (n_y));
}
