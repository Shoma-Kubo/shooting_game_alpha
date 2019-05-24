#include "pch.h"
#include "control.h"

CONTROL::CONTROL() {

  player = new PLAYER;
  background = new BACKGROUND;
}


CONTROL::~CONTROL() {

  delete player;
  delete background;
}


void CONTROL::All() {

  background -> All();
  player -> All();
}
