#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QTimer>
#include <QSound>

#include "block.h"
#include "person.h"
#include "captures.h"
#include "povistka.h"
#include "terrain.h"

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = nullptr);
    ~MainScene();

private:
    Ui::MainScene *ui;

    void resizeEvent(QResizeEvent* event);

    void toStartPosition();
    bool first_start;
    bool ready_to_play;

    bool gotcha;//если конец игры
    bool want_exit;

    QTimer *timer;

    void reprint();

    Block **blocks;//mass blocks

    Person *person;
    Povistka *povistka;

    Terrain *terrain;

    Captures *titles;

    QSound *sound;
    QSound *end_sound;

private slots:

    void block1_clicked();
    void block2_clicked();
    void block3_clicked();
    void block4_clicked();

    void slotTimerAlarm();

    void yes_clicked();
    void no_clicked();

};

#endif // MAINSCENE_H
