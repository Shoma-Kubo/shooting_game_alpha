#include "pch.h"
#include "player.h"
#include "control.h"

PLAYER::PLAYER() {

  LoadDivGraph("pictures/player_01.png", 12, 3, 4, 32, 32, img);

  w = 32;
  h = 32;

  move_left = move_right = move_up = move_down = 0;

  //移動距離[px/F]
  move_distance = 6;
  movie = 0;

  x = 300;
  y = 240;

  alive = true;

  //弾初期化
  memset(shot, 0, sizeof(shot));

  int temp_img = LoadGraph("pictures/shot_player_01.png");
  int temp_w, temp_h;
  GetGraphSize(temp_img, &temp_w, &temp_h);

  for (int i = 0; i < NUM_OF_SHOT; i++) {

    shot[i].flag = false;
    shot[i].img  = temp_img;
    shot[i].w    = temp_w;
    shot[i].h    = temp_h;
  }

  count_shot = 0;
}

void PLAYER::Move() {

  move_distance = key[KEY_INPUT_LSHIFT] == 1 ? 2 : 6;

  if (key[KEY_INPUT_LEFT]) move_left = move_left > -move_distance ? move_left - 1 : -move_distance;
  else if (move_left < 0) move_left ++;

  if (key[KEY_INPUT_RIGHT]) move_right = move_right < move_distance ? move_right + 1 : move_distance;
  else if (move_right > 0) move_right --;

  if (key[KEY_INPUT_UP]) move_up = move_up > -move_distance ? move_up - 1 : -move_distance;
  else if (move_up < 0) move_up ++;

  if (key[KEY_INPUT_DOWN]) move_down = move_down < move_distance ? move_down + 1 : move_distance;
  else if (move_down > 0) move_down --;

  x += move_right + move_left;
  y += move_up + move_down;

  //描画範囲外の移動制限
  if (x < -16) {
    x = -16;
    move_left = 0;
  }
  if (x > 624) {
    x = 624;
    move_right = 0;
  }
  if (y < -16) {
    y = -16;
    move_up = 0;
  }
  if (y > 460) {
    y = 460;
    move_down = 0;
  }

  //自機アニメーションカウント
  movie = movie >= 20 ? 0 : movie + 1;
}

void PLAYER::Draw() {

  for (int i = 0; i < NUM_OF_SHOT; i++) {
    if (shot[i].flag) {
      DrawGraph(shot[i].x - shot[i].w / 2, shot[i].y - shot[i].h / 2, shot[i].img, TRUE);
    }
  }

  if (alive) {

    DrawGraph(x, y, img[9 + (movie / 7)], TRUE);
  }
}

void PLAYER::Shot() {

  //弾を発射
  if (key[KEY_INPUT_Z] == 1 && count_shot % 4 == 0) {
    for (int i = 0; i < NUM_OF_SHOT; i++) {
      if (!shot[i].flag) {
        shot[i].flag = true;
        shot[i].x = x;
        shot[i].y = y;
        break;
      }
    }
  }

  for (int i = 0; i < NUM_OF_SHOT; i++) {
    if (shot[i].flag) {
      shot[i].y -= SHOT_SPEED;
      if (shot[i].y < -10) {
        shot[i].flag = false;
      }
    }
  }
}

void PLAYER::All() {

  Move();
  Shot();
  Draw();

  count_shot = count_shot >= 99 ? 0 : count_shot + 1;
}
