#ifndef BLOCK_H
#define BLOCK_H
#include "moving_object.h"



class Block: public Moving_object
{
    Q_OBJECT
protected:
        void mousePressEvent(QMouseEvent* event);
public:
     explicit Block(int x,int y,bool direction,QString pixmap_path,QWidget* central_widget);
signals:
    void clicked();
};

#endif // BLOCK_H
