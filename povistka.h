#ifndef POVISTKA_H
#define POVISTKA_H
#include "moving_object.h"
#include "person.h"

class Povistka : public Moving_object
{
    Q_OBJECT
private:

    Person *recipient;
    void make_step();
    QLabel* avoid_count_label;

    int avoid_count;

public:

    int get_avoid_count();
    void set_avoid_count(int new_count);

    explicit Povistka(int x,int y,QString pixmap_path, QWidget* central_widget);

    void SetRecipient(Person *person);

    void reset_speed();

    void reprint();

    bool isDilivered();
};

#endif // POVISTKA_H
