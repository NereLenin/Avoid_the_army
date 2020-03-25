#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QDebug>
#include <QPixmap>
#include <QTimer>
#include <QSound>
#include "block.h"
#include "person.h"
#include "povistka.h"
#include "terrain.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_block2_linkActivated(const QString &link);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_block1_clicked();
    void on_block2_clicked();
    void on_block3_clicked();
    void on_block4_clicked();

    void slotTimerAlarm();

    void on_yes_clicked();
    void on_no_clicked();
private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent* event);

    void toStartPosition();
    bool first_start;
    bool ready_to_play;

    bool gotcha;//если конец игры
    bool want_exit;

    QTimer *timer;

    void reprint(Ui::MainWindow *ui);

    Block **blocks;//mass blocks

    Person *person;
    Povistka *povistka;

    Terrain *terrain;

    Scene_object *end_fon;

    Block *yes;
    Block *no;

    double i;

    QSound *sound;
    QSound *end_sound;

};
#endif // MAINWINDOW_H
