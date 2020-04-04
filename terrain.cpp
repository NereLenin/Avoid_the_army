#include "terrain.h"

Terrain::Terrain(int height,QString pixmap_path, QWidget* central_widget)
    : Scene_object(0,0,pixmap_path,central_widget)
{
    n_height = height;
}

void Terrain::new_resize()
{
    setGeometry(0,get_form_y(),parentWidget()->width(),get_form_height());
}

