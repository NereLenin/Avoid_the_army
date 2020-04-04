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

public:
    explicit Povistka(int x,int y,QString pixmap_path, QWidget* central_widget);

    void SetRecipient(Person *person);

    void reset_speed();

    void reprint();

    bool isDilivered();
};

#endif // POVISTKA_H
