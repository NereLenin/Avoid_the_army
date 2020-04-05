#ifndef PERSON_H
#define PERSON_H

#include <QSound>
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

    QSound *jump_sound;

public:
    explicit Person(int x, int y, QString image_path, QString jump_sound_path, QWidget* central_widget);

    void set_StickNumber(int block_number);
    int get_StickNumber();

    void SetBlocksToStick(Block **blocks, int block_count);

    double get_form_y();

    void reprint();

    void stopAnimation();

};

#endif // PERSON_H
