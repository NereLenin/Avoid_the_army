#ifndef PERSON_H
#define PERSON_H
#include "scene_object.h"
#include "block.h"

class Person : public Scene_object
{
    Q_OBJECT
private:
    int animation_frame;
    bool Animation;
    int stick_number;

    Block **blocks;

    int block_count;

public:
    explicit Person(int x, int y, QString image_path,QWidget* central_widget=0);

    void set_StickNumber(int block_number);
    int get_StickNumber();

    void SetBlocksToStick(Block **blocks, int block_count);

    int get_form_y();

    void reprint();

    void stopAnimation();

};

#endif // PERSON_H
