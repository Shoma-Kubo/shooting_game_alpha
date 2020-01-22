#include "background.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "menu.h"

class CONTROL {

public:
  MENU *menu;
  BACKGROUND *background;
  PLAYER *player;
  ENEMY *enemy[NUM_OF_ENEMY];
  BOSS *boss[NUM_OF_BOSS];

public:
  CONTROL();
  ~CONTROL();

private:
  void LoadResources();
  void LoadEnemyData();
  void LoadBossData();
  void SoundAll();

public:
  void GetPlayerStatus(int *max, double *now, double *power);
  void GetPlayerPosition(double *x, double *y);
  void GetPlayersShotPosition(int i, int j, double *x, double *y);
  void GetEnemyPosition(int index, double *x, double *y);
  void All();
  void ResetAll();

  static CONTROL& GetInstance() {
    static CONTROL control;
    return control;
  }
};
