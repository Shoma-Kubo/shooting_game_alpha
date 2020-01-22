class PLAYER {

  private:
	bool alive;
	double x, y;

    bool   canShoot;
    int    pimg[16], pimgW, pimgH;

    int    moveL, moveR, moveU, moveD;
    int    move_speed;
    int    movie;

    int    maxHP;
    double nowHP;
    double power;

    int    score;

    SHOT   shot[2][NUM_OF_SHOT];
    int    count_shot, shot_type, shot_change_count;
    int    shot_speed[1];
    double shot_power;

    BOM  bom[NUM_OF_BOMSHOT];
    bool boming;
    int  bom_type, count_bom;
    int  temp_x, temp_y;
    int  bom_time[10];

    double adding_rad, pre_adding_rad;

    int color_white  = GetColor(255, 255, 255);
    int color_red    = GetColor(255,  50,  50);
    int color_blue   = GetColor( 50,  50, 255);
    int color_yellow = GetColor(255, 255,  50);
    int color_HP;

  private:
    void Move();
    void Shot();
    void Draw();
    void DrawStatus();

  public:
    PLAYER();
    void GetStatus(int *max, double *now, double *power);
    void GetPosition(double *x,double *y);
    bool GetShotPosition(int i, int j, double* x, double* y);
    void All();
    void Reset();
};
