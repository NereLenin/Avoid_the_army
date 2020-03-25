#ifndef TERRAIN_H
#define TERRAIN_H
#include "scene_object.h"

class Terrain: public Scene_object
{
  Q_OBJECT
private:

    int get_form_y();

public:
    explicit Terrain(int height,QString pixmap_path, QWidget* central_widget=0);
    void new_resize();

};

#endif // TERRAIN_H
