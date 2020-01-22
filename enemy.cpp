#include "pch.h"
#include "control.h"

ENEMY::ENEMY(char *char_filename, int *move_pattern, double x, double y, int in, int phase_out, int *shot_pattern, int hp, int item) {

  LoadDivGraph(char_filename, 16, 4, 4, 96, 96, img);

  w = 96;
  h = 96;

  alive = true;
  end   = false;
  stay  = false;
  phase = 0;
/*
  this -> move_pattern = move_pattern;
  this -> shot_pattern = shot_pattern;
*/
  this -> x = x;
  this -> y = y;

  this -> in        = in;
  this -> phase_out = phase_out;

  this -> hp    = hp;
  this -> item  = item;

  shot_pattern_index = 0;
  waiting = 0;

  e_movie = 0;

  for (int i = 0; i < NUM_OF_ENEMY_SHOT; i++) e_shot[i].flag = false;

  count_shot = 0;

  end = false;
}

void ENEMY::Move() {

  if (alive){
    phase ++;
    if (waiting > 0) {
      waiting -= 1;
    }
  }

  if (alive && !stay && stage == 0 && gamecount > in) {
    y += 4;
  }

  if (y > 100 && !stay) {
    stay  = true;
    phase = 1000;
  }

  if (phase < phase_out && y < -40) {
    end = true;
  }
}

void ENEMY::Shot() {

  CONTROL &control = CONTROL::GetInstance();
  double player_x, player_y;
  double temp_rad;

  if (alive /*&& phase > 1000*/) {

    /*switch (shot_pattern[0]) {

      case 0:*/

      /*if (phase % 10 == 0 && waiting == 0) {

		control.GetPlayerPosition(&player_x, &player_y);  
		temp_rad = atan2(player_y - y, player_x - x);
		temp_rad = 3.14;

        for (int i = 0; i < NUM_OF_ENEMY_SHOT; i++) {

          if (!e_shot[i].flag) {

            e_shot[i].flag  = true;
            e_shot[i].x     = x;
            e_shot[i].y     = y;
            e_shot[i].speed = 6;

            e_shot[i].imgN  = 10;
            e_shot[i].rad   = temp_rad;

            count_shot ++;

			break;
		  }
        }
      }
	  if (count_shot == 5) {
		  waiting = 50;
		  count_shot = 0;
	  }

      /*break;
    }*/
  }

  for (int i = 0; i < NUM_OF_ENEMY_SHOT; i++) {
    if(e_shot[i].flag) {
      e_shot[i].x += cos(e_shot[i].rad) * e_shot[i].speed;
      e_shot[i].y += sin(e_shot[i].rad) * e_shot[i].speed;
    }
    if (e_shot[i].y < LIMIT_U - 20 || e_shot[i].y > LIMIT_D + 20 || e_shot[i].x < LIMIT_L - 20 || e_shot[i].x > LIMIT_R + 20) {
      e_shot[i].flag = false;
    }
  }
}

void ENEMY::Draw() {

  for (int i = 0; i < NUM_OF_ENEMY_SHOT; i++) {
    if (e_shot[i].flag) {
      DrawRotaGraph(e_shot[i].x, e_shot[i].y, 1.0f, e_shot[i].rad, img[e_shot[i].imgN], TRUE);
    }
  }

  if (alive){
    DrawGraph(x - w / 2, y- h / 2, img[e_movie / 5], TRUE);
  }
}

void ENEMY::GetPosition(double *x, double *y) {
    *x = this -> x;
    *y = this -> y;
}

bool ENEMY::All() {

  Move();
  Shot();
  Draw();

  e_movie = e_movie < 19 ? e_movie + 1 : 0;

  return end;
}

void ENEMY::Reset() {

  alive = true;
  end   = false;
  stay  = false;
  phase = 0;

  shot_pattern_index = 0;
  waiting = 0;

  e_movie = 0;

  for (int i = 0; i < NUM_OF_ENEMY_SHOT; i++) e_shot[i].flag = false;

  count_shot = 0;

  end = false;
}
