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
/*
    if(povistka->isDilivered(person))
    {
        i=0;
        gotcha = true;
        sound->stop();
        end_fon->show();
        end_fon->setText("Попалась, вонючка?\nПопробуешь еще раз?");

        end_sound->play();

    }

*/
    }

}

void MainWindow::toStartPosition()
{

    person->set_x(10);
    person->set_y(0);
    person->stopAnimation();

    povistka->set_x(20);
    povistka->set_y(20);
    povistka->set_speed(0.2);

    for(int j=0;j<4;j++)//создаем каждый блок
    {
        blocks[j]->set_x(10+(j*25));
        blocks[j]->set_y(10+(j*20));
    }

    gotcha = false;

    end_sound->stop();
    sound->play();

    yes->hide();
    no->hide();
    end_fon->hide();
    end_fon->setStyleSheet("background-color: rgba(1,1,1, 0);color:white;");
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    lines = new QFrame*[100];//массив блоков

    for(int j=0;j<100;j++)//создаем каждый блок
    {

        lines[j] = new QFrame(this);
        lines[j]->hide();
    }


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
    terrain = new Terrain(10,":/img/terrain.jpg",ui->centralwidget);

    //создаем обьекты
    blocks = new Block*[4];//массив блоков



    bool ne_chentniy;
    for(int j=0;j<4;j++)//создаем каждый блок
    {
        ne_chentniy = (j % 2 != 0);
        blocks[j] = new Block(10+(j*25),10+(j*20),ne_chentniy,":/img/block.png",ui->centralwidget);
    }


    //соединяем их со слотами
    connect(blocks[0], SIGNAL(clicked()), this, SLOT(on_block1_clicked()));
    connect(blocks[1], SIGNAL(clicked()), this, SLOT(on_block2_clicked()));
    connect(blocks[2], SIGNAL(clicked()), this, SLOT(on_block3_clicked()));
    connect(blocks[3], SIGNAL(clicked()), this, SLOT(on_block4_clicked()));


    //создаем персонажа
    person = new Person(10,0,":/img/person_2.png",ui->centralwidget);
    person->setFrameShape(QFrame::Box);//добавляем наглядную рамку

    person->SetBlocksToStick(blocks,4);//добавляем блоки к которым будем прилипать

    //создаем повестку
    povistka = new Povistka(20,20,":/img/convert_2.jpg",ui->centralwidget);


    //создаем задний фон который делает
    end_fon = new Scene_object(0,0,"",ui->centralwidget);
    end_fon->setFont(QFont("Courier 10 Pitch",20,QFont::Bold));
    end_fon->setAlignment(Qt::AlignCenter);
    end_fon->setText("Правила игры:\n1)Прыгайте по блокам,\n кликая по ним\n2)Уворачивайтесь от\n повестки\nГотовы?");

    //просто this конструктор?
    end_fon->setStyleSheet("background-color: rgba(1,1,1, 1);color:white;");

    //end_fon->show();
//    end_fon->hide();


    //выбор при проигрыше
    //вместо блока добавить класс clickable object и занаследоваться от него в povistka и тут сделать
    yes = new Block(75,0,false,":/img/ok.png",ui->centralwidget);
    yes->set_height(10);
    yes->set_width_per_height(1);

    no = new Block(10,0,false,":/img/err.png",ui->centralwidget);
    no->set_height(10);
    no->set_width_per_height(1);

    connect(yes, SIGNAL(clicked()), this, SLOT(on_yes_clicked()));
    connect(no, SIGNAL(clicked()), this, SLOT(on_no_clicked()));

    //создаем перерисовочный таймер
    timer = new QTimer();

    //соединяем с слотом на форме
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(30);

    //создаем воспроизведение музыки
    sound = new QSound(":/music/main.wav",this);
    sound->setLoops(QSound::Infinite);//воспроизводим бесконечно
  //  sound->play();//говорим играть

    end_sound = new QSound(":/music/end.wav",this);
    end_sound->setLoops(QSound::Infinite);//воспроизводим бесконечно
    end_sound->stop();//говорим не играть

   // paint = new QPainter(this);//[100];//массив блоков


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
   end_fon->resize(event->size());

   for(int j=0;j<4;j++)
   {
       blocks[j]->new_resize();
   }

   person->new_resize();
   povistka->new_resize();
   terrain->new_resize();

   no->new_resize();
   yes->new_resize();

   repaint();

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
    person->set_x(person->get_x()+1);
}

void MainWindow::on_pushButton_4_clicked()
{
   // person_y--;
   // reprint(ui);
    //qDebug() << "y:" << person_y << endl;
}

void MainWindow::on_block1_clicked()
{
    person->set_StickNumber(1);
}

void MainWindow::on_block2_clicked()
{
    person->set_StickNumber(2);
}

void MainWindow::on_block3_clicked()
{

    person->set_StickNumber(3);
}

void MainWindow::on_block4_clicked()
{

     person->set_StickNumber(4);
}

void MainWindow::on_yes_clicked()
{
    //qDebug() << "Yes clicked. " << endl;
    if(want_exit)
    {

        close();
       // this->~MainWindow();

        //return;
    }
    else if(first_start)
    {
     ready_to_play = true;
     sound->play();//говорим играть
     i=0;
     end_fon->setText("");

     yes->hide();
     no->hide();
    }
    else
    {

        toStartPosition();
    }


}

void MainWindow::on_no_clicked()
{
    if(!want_exit)
    {
        end_fon->setText("Вы уверены что хотите выйти?");
        want_exit = true;
    }
    else
    {
        if(first_start)
           end_fon->setText("Правила игры:\n1)Прыгайте по блокам,\n кликая по ним\n2)Уворачивайтесь от\n повестки\nГотовы?");
        else
        end_fon->setText("Попалась, вонючка?\nПопробуешь еще раз?");

        want_exit = false;
    }
}

void MainWindow::slotTimerAlarm()
{

    if(first_start)
    {
        //qDebug() << "First start" << endl;
      if(ready_to_play)
        {


          for (int j=0;j<100;j++)
            lines[j]->show();

        if(i<0.95)//просветление по красоте
        {
            //qDebug() << "i: " << 0.99 - i << endl;
        end_fon->setStyleSheet(QString("background-color: rgba(1,1,1, %1);color:white;").arg((0.99-i)));
        i+=0.01;
        }
        else
        {
            end_fon->hide();
            i+=0.01;
            first_start = false;
        }
      }
    }else if(!gotcha){

    ui->block_old->setText(QString::number(i+=0.01));

    for(int j=0;j<4;j++)
    {
        blocks[j]->make_step();
    }

    povistka->make_step(person);

    reprint(ui);

    }//end gotcha
    else
    {
        if(i<0.95)//затемнение по красоте
        {
        end_fon->setStyleSheet(QString("background-color: rgba(1,1,1, %1);color:white;").arg(i));

        i+=0.01;
        }
        else{

            no->show();
            yes->show();
        }

    }

}

