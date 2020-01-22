#include <windows.h>

//SYSTEM

#define MSG(str) {\
  MessageBox(NULL, str, "Message", MB_OK);}

extern bool quit;

extern char key[256];

extern int gamecount;
extern int stage;

extern int  difficulty;
extern bool menu_opened;

extern int volume_bgm;
extern int volume_se;

extern int invincibleTime;
extern int dyingcount;

extern int img[50];
extern int imgW[50];
extern int imgH[50];

extern int  se[10];
extern int  bgm[10];
extern bool playSE[10];
extern bool playBGM[10];

//These may change
extern double *addx;
extern double *addy;
extern double* addx2;
extern double* addy2;
extern double* addx3;
extern double* addy3;

extern int debugAry[10];

#define LIMIT_L  10
#define LIMIT_R 940
#define LIMIT_U  10
#define LIMIT_D 950

#define CNT_MENU_MAX 120

#define DyingCountMax 50

struct SHOT {

  bool   flag;
  int    imgN;

  double x, y;
  double rad;
  double rota;
  int    speed;
};

struct ENEMY_SHOT {

  bool flag;
  int imgN;

  double x, y;
  double rad;
  double rota;
  int    speed;

  int    id;
  bool   getItem;
};

struct BOM {

  bool   flag;
  int    imgN;

  double x, y;
  double rad;
  double rota;
  int    speed;

  int    id;
  bool   getItem;
};

#define NUM_OF_SHOT 100
#define NUM_OF_ENEMY_SHOT 500
#define NUM_OF_BOMSHOT 3000

#define NUM_OF_ENEMY 1
#define NUM_OF_BOSS 3
