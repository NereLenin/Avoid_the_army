#ifndef CAPTURES_H
#define CAPTURES_H
#include "scene_object.h"
#include "img_button.h"

class Captures: public Scene_object
{
    Q_OBJECT
protected:
    bool start_scene;
    bool end_scene;

    double i;
    Img_button *yes;
    Img_button *no;



public:
    Captures(QString yes_img, QString no_img, QWidget *parent);

    Img_button* get_yes_btn();
    Img_button* get_no_btn();

    void set_current_text(QString text);

    bool get_start_scene();
    bool get_end_scene();

    void reprint();
    void new_resize();

    void show_start_scene();
    void show_end_scene();

    void hide();
};

#endif // CAPTURES_H
