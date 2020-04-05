#ifndef BLOCK_H
#define BLOCK_H
#include "moving_object.h"



class Block: public Moving_object
{
    Q_OBJECT
protected:
      void mousePressEvent(QMouseEvent* event);
      double i;

      bool animation;
public:

     explicit Block(int x,int y,bool direction,QString pixmap_path,QWidget* central_widget);

    void start_animation();
    void reprint();
signals:
    void clicked();
};

#endif // BLOCK_H
