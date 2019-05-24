#include "pch.h"
#include "background.h"

BACKGROUND::BACKGROUND() {

  img[0] = LoadGraph("pictures/background_01.png");

  x = 0;
  y = -450;
}

void BACKGROUND::Draw() {

  DrawGraph(x, y, img[0], FALSE);
}

void BACKGROUND::Move() {

  y = y >= 0 ? -450 : y + 2;
}

void BACKGROUND::All() {

  Draw();
  Move();
}
