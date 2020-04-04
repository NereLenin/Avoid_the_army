#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H
#include "scene_object.h"

class Moving_object : public Scene_object
{
    Q_OBJECT
protected:
    double speed;

    bool direction;//0-right to left, 1 left to right

public:
    explicit Moving_object(int x,int y,bool direction,QString pixmap_path,QWidget* central_widget);

    virtual ~Moving_object(){};

    bool get_direction();
    void reprint();

};

#endif // MOVING_OBJECT_H
