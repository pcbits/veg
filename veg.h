#define BLANK 0
#define PUMPKIN 1
#define BEET 2
#define TOMATO 3
#define VEG_MIN PUMPKIN
#define VEG_MAX TOMATO

void veg_select(int y, int x, int pair);
void veg_selected(int y, int x);
void veg_draw(int y, int x, int veg);
