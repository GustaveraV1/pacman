#include <iostream>
#include <cstdlib>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>

#include "map.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

void must_init(bool status, const char *entity)
{
    if (!status)
    {
        std::cerr << "error: couldn't initialize " << entity << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int main()
{
    must_init(al_init(), "allegro");
    must_init(al_init_image_addon(), "image");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER *time = al_create_timer(1.0 / 30.0);
    must_init(time, "time");

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    must_init(event_queue, "event queue");

    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    must_init(display, "display");

    must_init(al_init_image_addon(), "image addon");

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(time));

    bool done = false, redraw = true;

    ALLEGRO_BITMAP *wall = al_load_bitmap("assets/map/wall.png");
    ALLEGRO_BITMAP *pill = al_load_bitmap("assets/map/pill.png");
    ALLEGRO_BITMAP *super_pill = al_load_bitmap("assets/map/super_pill.png");

    Map esqueme = Map("data/map/classic.map");

    ALLEGRO_EVENT event;

    al_start_timer(time);
    while (true)
    {
        al_wait_for_event(event_queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done) break;

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            al_draw_bitmap(wall, 0, 0, 0);
            al_draw_bitmap(pill, 20, 20, 0);
            esqueme.draw(wall, pill, super_pill);
            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_bitmap(wall);
    al_destroy_bitmap(pill);
    al_destroy_bitmap(super_pill);
    al_destroy_timer(time);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return 0;
}
