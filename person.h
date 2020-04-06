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
    bool direction_jump;
    int stick_number;

    Block **blocks;

    int block_count;

    QSound *jump_sound;

    QString sprite_straight;
    QString sprite_naklon;
    QString sprite_jump;

    QString sprite_straight_l;
    QString sprite_naklon_l;
    QString sprite_jump_l;


public:
    explicit Person(int x, int y, QString image_path, QString jump_sound_path, QWidget* central_widget);
    void setSprites(QString sprite_naklon, QString jump_sprite,
                    QString sprite_straight_l, QString sprite_naklon_l, QString sprite_jump_l);

    void set_StickNumber(int block_number);
    int get_StickNumber();

    void SetBlocksToStick(Block **blocks, int block_count);

    double get_form_y();

    void reprint();

    void stopAnimation();

};

#endif // PERSON_H
