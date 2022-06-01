#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

int main() {
	al_init();
	al_install_keyboard();

	ALLEGRO_TIMER *tempo = al_create_timer(1.0 / 30.0);
	ALLEGRO_EVENT_QUEUE *fila = al_create_event_queue();
	ALLEGRO_DISPLAY *tela = al_create_display(800, 600);
	ALLEGRO_FONT *fonte = al_create_builtin_font();

	al_register_event_source(fila, al_get_keyboard_event_source());
	al_register_event_source(fila, al_get_display_event_source(tela));
	al_register_event_source(fila, al_get_timer_event_source(tempo));

	bool redesenha = true;
	ALLEGRO_EVENT evento;

	al_start_timer(tempo);
	while (true) {
		al_wait_for_event(fila, &evento);

		if (evento.type == ALLEGRO_EVENT_TIMER) redesenha = true;
		else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

		if (redesenha and al_is_event_queue_empty(fila)) {
			al_clear_to_color(al_map_rgb(255, 0, 0));
			al_draw_text(fonte, al_map_rgb(0, 0, 255), 0 ,0, 0, "Eae, Monark aqui!");
			al_flip_display();

			redesenha = false;
		}
	}

	al_destroy_font(fonte);
	al_destroy_display(tela);
	al_destroy_timer(tempo);
	al_destroy_event_queue(fila);

	return 0;
}
