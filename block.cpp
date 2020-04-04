#include "block.h"


Block::Block(int x, int y,bool direction,QString pixmap_path, QWidget* central_widget)
    : Moving_object(x, y, direction, pixmap_path,central_widget)

{
   n_height = 6;
   width_per_height = 4;

   speed =0.3;

   this->direction = direction;
}

void Block::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit clicked();
}
