#include "pch.h"
#include "background.h"

BACKGROUND::BACKGROUND() {

  img[0] = LoadGraph("pictures/background_01.png");

  x = 10;
  y = -930;
}

void BACKGROUND::Draw() {

  SetDrawArea(10, 10, 1270, 950);
  DrawGraph(x, y, img[0], FALSE);
}

void BACKGROUND::Move() {

  y = y >= 0 ? -930 : y + 4;
}

void BACKGROUND::All() {

  Draw();
  Move();
}
