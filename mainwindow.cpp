#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::reprint(Ui::MainWindow *ui)
{
    if(!gotcha)
    {

        for(int j=0;j<4;j++)
        {
            blocks[j]->reprint();
        }


    povistka->reprint();

    person->reprint();

    //qDebug() << "person " << person->get_x() << "," << person->get_y()<< " form" << person->get_form_x() << "," << person->get_form_y()  << "form width " << person->get_form_width() << "/" << person->width() << " per " << person->width_per_height << " width " << person->get_n_width() << endl;

 /*   if(povistka->isDilivered())
    {
        i=0;
        gotcha = true;
        sound->stop();
        titles->setText("Попалась, вонючка?\nПопробуешь еще раз?");
        titles->show_end_scene();
        end_sound->play();

    }
*/

    }

}

void MainWindow::toStartPosition()
{

    person->set_x(10);
    person->set_y(10);
    person->stopAnimation();
    povistka->set_x(30);
    povistka->set_y(30);
    povistka->reset_speed();

    for(int j=0;j<4;j++)//создаем каждый блок
    {
        blocks[j]->set_x(10+(j*23));
        blocks[j]->set_y(20+(j*19));
    }

    gotcha = false;

    end_sound->stop();
    sound->play();

  //  yes->hide();
 //   no->hide();
 //   end_fon->hide();
 //   end_fon->setStyleSheet("background-color: rgba(1,1,1, 0);color:white;");
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);



   // lines = new QFrame*[100];//массив блоков

  //  for(int j=0;j<100;j++)//массив линий
 //   {

  //      lines[j] = new QFrame(this);
 //       lines[j]->hide();
  //  }


    gotcha = want_exit = ready_to_play = false;

    first_start = true;

    i=0;

    //прячем старое
    ui->person->hide();
    ui->povistka->hide();
    ui->terrain->hide();
    ui->pushButton_2->hide();
    ui->pushButton_4->hide();
    ui->pushButton->hide();
  //  ui->pushButton_3->hide();

    //создаем землю
    terrain = new Terrain(11,":/img/terrain.png",ui->centralwidget);

    //создаем обьекты
    blocks = new Block*[4];//массив блоков



    bool ne_chentniy;
    for(int j=0;j<4;j++)//создаем каждый блок
    {
        ne_chentniy = (j % 2 != 0);
        blocks[j] = new Block(10+(j*23),20+(j*19),ne_chentniy,QString(":/img/block_%1.png").arg(j+1),ui->centralwidget);
    }


    //соединяем их со слотами
    connect(blocks[0], SIGNAL(clicked()), this, SLOT(on_block1_clicked()));
    connect(blocks[1], SIGNAL(clicked()), this, SLOT(on_block2_clicked()));
    connect(blocks[2], SIGNAL(clicked()), this, SLOT(on_block3_clicked()));
    connect(blocks[3], SIGNAL(clicked()), this, SLOT(on_block4_clicked()));


    //создаем персонажа
    person = new Person(10,7,":/img/person.png", ":/music/jump.wav" ,ui->centralwidget);
    //person->setFrameShape(QFrame::Box);//добавляем наглядную рамку

    person->SetBlocksToStick(blocks,4);//добавляем блоки к которым будем прилипать
    person->setSprites(":/img/person_2.png",":/img/person_3.png",
                       ":/img/person_l.png",":/img/person_l_2.png",":/img/person_l_3.png");
    //создаем повестку
    povistka = new Povistka(30,30,":/img/povistka.png",ui->centralwidget);
    povistka->SetRecipient(person);

    titles = new Captures(":/img/ok.png",":/img/err.png",ui->centralwidget);
    titles->setText("Правила игры:\n1)Прыгайте по блокам,\n кликая по ним\n2)Уворачивайтесь от\n повестки\nГотовы?");

    connect(titles->get_yes_btn(), SIGNAL(clicked()), this, SLOT(on_yes_clicked()));
    connect(titles->get_no_btn(), SIGNAL(clicked()), this, SLOT(on_no_clicked()));

    //создаем перерисовочный таймер


    timer = new QTimer();

    //соединяем с слотом на форме
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(30);//30

    //создаем воспроизведение музыки
    sound = new QSound(":/music/main.wav",this);
    sound->setLoops(QSound::Infinite);//воспроизводим бесконечно

    end_sound = new QSound(":/music/end.wav",this);
    end_sound->setLoops(QSound::Infinite);//воспроизводим бесконечно
    end_sound->stop();//говорим не играть

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::resizeEvent(QResizeEvent* event=0)//все это потом на таймер
{

    //сделать одну общую функцию reprint_scene()
    //которая будет использоваться и отсюда и из таймера
    //обновляет размеры и положения всех обьектов

   ui->background->resize(event->size());
   titles->new_resize();


   for(int j=0;j<4;j++)
   {
       blocks[j]->new_resize();
   }



   person->new_resize();
   povistka->new_resize();
   terrain->new_resize();


}

void MainWindow::on_pushButton_2_clicked()
{
   // person_x++;
   // reprint(ui);
}

void MainWindow::on_block2_linkActivated(const QString &link)
{

}

void MainWindow::on_pushButton_clicked()
{
   // person_x--;
   // reprint(ui);
}

void MainWindow::on_pushButton_3_clicked()
{
    //toStartPosition();

    //person_y+=10;
    //reprint(ui);
   // qDebug() << "y:" << person_y << endl;
    person->stopAnimation();
    person->set_StickNumber(0);
    person->set_x(person->get_x()+1);
    person->set_y(person->get_y()-30);
}

void MainWindow::on_pushButton_4_clicked()
{
   // person_y--;
   // reprint(ui);
    //qDebug() << "y:" << person_y << endl;
}

void MainWindow::on_block1_clicked()
{
    if(person->get_StickNumber()!=1)
       blocks[0]->start_animation();

    person->set_StickNumber(1);

}

void MainWindow::on_block2_clicked()
{
    if(person->get_StickNumber()!=2)
       blocks[1]->start_animation();

    person->set_StickNumber(2);
}

void MainWindow::on_block3_clicked()
{
    if(person->get_StickNumber()!=3)
       blocks[2]->start_animation();

    person->set_StickNumber(3);
\
}

void MainWindow::on_block4_clicked()
{

    if(person->get_StickNumber()!=4)
       blocks[3]->start_animation();

     person->set_StickNumber(4);

}

void MainWindow::on_yes_clicked()
{

    if(want_exit)
    {

        close();
    }
    else if(first_start)
    {
     ready_to_play = true;
     sound->play();//говорим играть

     titles->setText("");
     titles->show_start_scene();

    }
    else
    {
        toStartPosition();
        titles->hide();
    }


}

void MainWindow::on_no_clicked()
{
    if(!want_exit)
    {
        titles->setText("Вы уверены что хотите выйти?");
        want_exit = true;
    }
    else
    {
        if(first_start)
           titles->setText("Правила игры:\n1)Прыгайте по блокам,\n кликая по ним\n2)Уворачивайтесь от\n повестки\nГотовы?");
        else
        titles->setText("Попалась, вонючка?\nПопробуешь еще раз?");

        want_exit = false;
    }
}

void MainWindow::slotTimerAlarm()
{

    if(first_start)//если запустили первый раз
    {
      if(ready_to_play)//если нажали да и готовы игать
        {

            //show_start_scene
            if(!titles->get_start_scene())//если сцена закончилась
                first_start = false;//как только стартовая сцена закончена говорим шо больше не первый раз запускаем

            titles->reprint();//перерисовываем титры
        }

    }else if(!gotcha){//если не первый старт и игра не закончена

    ui->block_old->setText(QString::number(i+=0.01));

    reprint(ui);//перересовываем сцену

    }
    else//Если попался
    {
       titles->reprint();//перересовываем титры
    }

}

