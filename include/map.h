#ifndef MAP_H
#define MAP_H

#define WIDTH 20
#define HEIGHT 20

#include <allegro5/allegro5.h>

typedef enum
{
    PILL,
    WALL,
    SUPER_PILL,
} maps_objects_e;

class Map
{
public:
    Map(const char *);
    ~Map(void);

    void draw(ALLEGRO_BITMAP *, ALLEGRO_BITMAP *, ALLEGRO_BITMAP *);

private:
    int **scene;
    int pills = 0;
};

#endif // MAP_H
