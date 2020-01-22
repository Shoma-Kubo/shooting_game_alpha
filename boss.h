class BOSS {

  private:
    bool alive;
    bool stay;

    int bimg;
    int bimgH;
    int bimgW;

    double x, y;

    int    maxHP;
    double nowHP;
    int    color_HP;

    int ptn_item;
    int ptn_move;
    int ptn_bom;

    int phase;
    int cnt_bom;
    int cooltime;

    BOM  bom[NUM_OF_BOMSHOT];
    bool boming;
    int  bomtype;

	int waiting;
	int cnt_shot;

  private:
    void Move();
    void Bom();
    void Damage();
    void Draw();
    void DrawStatus();

  public:
    bool All();
    BOSS(int imgN, double x, double y, int maxHP, double nowHP, int ptn_item, int ptn_move, int ptn_bom);
    void Reset();
};
