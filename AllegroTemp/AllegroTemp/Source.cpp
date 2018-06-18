#include "includes.h"

float cameraX;
float cameraY;

float mouseX;
float mouseY;

bool SPACE;
bool UP;
bool DOWN;
bool LEFT;
bool RIGHT;

int main() {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	al_init();
	al_init_primitives_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(width, height);
	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);

	bool redraw = true;

	ALLEGRO_FONT *font = NULL;
	font = al_create_builtin_font();

	Scene myScene = Scene();
	cameraX = 0;
	cameraY = 0;

	while (1) {

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (ev.keyboard.keycode == ALLEGRO_KEY_D)
				RIGHT = true;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
				SPACE = true;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A)
				LEFT = true;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_W)
				UP = true;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
				DOWN = true;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_X)
				myScene.Disparar();

			else if (ev.keyboard.keycode == ALLEGRO_KEY_Z)
				myScene.CambiarDireccionBalas();
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {

			if (ev.keyboard.keycode == ALLEGRO_KEY_D)
				RIGHT = false;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
				SPACE = false;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_A)
				LEFT = false;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_W)
				UP = false;
			else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
				DOWN = false;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			mouseX = (float)ev.mouse.x;
			mouseY = (float)ev.mouse.y;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			//click!
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {

			redraw = false;

			myScene.update(font);

			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);

	return 0;
}