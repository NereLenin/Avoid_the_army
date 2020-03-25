#ifndef POVISTKA_H
#define POVISTKA_H
#include "block.h"
#include "person.h"

class Povistka : public Block
{
    Q_OBJECT
private:
    void make_step();

public:
    explicit Povistka(int x,int y,QString pixmap_path, QWidget* central_widget=0);

    void SetRecipient(Person *person);

    void make_step(Person *person);

    bool isDilivered(Person *person);
};

#endif // POVISTKA_H
