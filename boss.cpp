#include "pch.h"
#include "control.h"

BOSS::BOSS(int imgN, double x, double y, int maxHP, double nowHP, int ptn_item, int ptn_move, int ptn_bom) {

  bimg  = img[imgN];
  bimgH = imgH[imgN];
  bimgW = imgW[imgN];

  alive = false;
  stay  = false;

  this -> x = x;
  this -> y = y;

  this -> maxHP = maxHP;
  this -> nowHP = nowHP;

  this -> ptn_item = ptn_item;
  this -> ptn_move = ptn_move;
  this -> ptn_bom  = ptn_bom;

  phase    = 0;
  cnt_bom  = 0;
  cooltime = 0;

  boming  = false;
  bomtype = 0;

  waiting  = 0;
  cnt_shot = 0;

  for (int i = 0; i < NUM_OF_ENEMY_SHOT; i++) bom[i].flag = false;
}

void BOSS::Move() {

  if (waiting > 0) {
    waiting -= 1;
  }

  switch(ptn_move) {

    case 0:
      if (phase == 0 && gamecount > 100 && y < 200) {
        alive = true;
        y += 2;
      }
  }

}

void BOSS::Bom() {

  CONTROL &control = CONTROL::GetInstance();
  double player_x, player_y;
  double temp_rad;

  if (alive /*&& phase > 1000*/) {

    /*switch (shot_pattern[0]) {

      case 0:*/

      if (waiting == 0) {

		if (gamecount % 5 == 0) {

          for (int i = 0; i < NUM_OF_BOMSHOT; i++) {

            if (!bom[i].flag) {

			  control.GetPlayerPosition(&player_x, &player_y);
		      temp_rad = atan2(player_y - y, player_x - x);

			  //debug
			  debugAry[0] = player_x;
			  debugAry[1] = player_y;

              bom[i].flag  = true;
              bom[i].x     = x;
              bom[i].y     = y;
              bom[i].speed = 6;

              bom[i].imgN  = 10;
              bom[i].rad   = temp_rad;

              cnt_shot ++;
			  break;
			}
	      }
	    }
      }

      if (cnt_shot == 5) {
        waiting    = 50;
        cnt_shot = 0;
      }
    //}
  }

  for (int i = 0; i < NUM_OF_BOMSHOT; i++) {

	int tmp = 0;
	
    if(bom[i].flag) {
      bom[i].x += cos(bom[i].rad) * bom[i].speed;
      bom[i].y += sin(bom[i].rad) * bom[i].speed;
	  tmp ++;
    }

	debugAry[0] = tmp;

    if (bom[i].y < LIMIT_U - 20 || bom[i].y > LIMIT_D + 20 || bom[i].x < LIMIT_L - 20 || bom[i].x > LIMIT_R + 20) {
      bom[i].flag = false;
    }
  }

}

void BOSS::Damage() {

}

void BOSS::Draw() {

  if (true){
    DrawGraph(x - bimgW / 2, y - bimgH / 2, bimg, TRUE);
  }

  for (int i = 0; i < NUM_OF_BOMSHOT; i++) {
    if (bom[i].flag) {
      DrawRotaGraph(bom[i].x, bom[i].y, 1.0f, bom[i].rad, img[bom[i].imgN], TRUE);
    }
  }
}

void BOSS::DrawStatus() {

  SetDrawArea(10, 10, 1270, 950);
  SetFontSize(30);

  double hp_rate = nowHP / maxHP;
  DrawBox(LIMIT_L, LIMIT_U, hp_rate * (LIMIT_R - LIMIT_L) + LIMIT_L, LIMIT_U + 5, GetColor( 50,  50, 255), TRUE);
}

bool BOSS::All() {

  Move();
  Bom();
  Draw();
  DrawStatus();

  return false;
}

void BOSS::Reset() {

  alive = false;
  stay  = false;

  nowHP = maxHP;
  
  phase    = 0;
  cnt_bom  = 0;
  cooltime = 0;

  boming  = false;
  bomtype = 0;
}
