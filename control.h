#include "player.h"
#include "background.h"

class CONTROL {

private:
  PLAYER *player;
  BACKGROUND *background;

public:
  CONTROL();
  ~CONTROL();
  void All();
};
