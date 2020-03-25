
#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H
#include <QLabel>
#include <QDebug>
class Scene_object : public QLabel
{
   Q_OBJECT
protected:
    double n_x;
    double n_y;


    double get_form_x();
    double get_form_y();

    double width_per_height;
    double n_height;

    int hard_width;

    double get_form_width();
    double get_form_height();

    int coord_max;//change?

public:
    explicit Scene_object(int x,int y,QString pixmap_path,QWidget* central_widget=0);
    virtual ~Scene_object(){}

    double get_x();
    double get_y();

    void set_x(double x);
    void set_y(double y);

    void set_height(double height);
    void set_width_per_height(double width_per_height);

    void set_hard_width(int width);

    double get_n_width();
    double get_n_height();

    void new_resize();

    void reprint();
};

#endif // SCENE_OBJECT_H
