//Para esconder la consola
#if _WIN32_WINNT < 0x0500
#undef _WIN32_WINNT
#define _WIN32_WINNT   0x0500
#endif

#include "includes.h"

float mouseX;
float mouseY;

bool CLICK;

bool SPACE;
bool UP;
bool DOWN;
bool LEFT;
bool RIGHT;
bool ELEX;
bool DEL;

bool key[26];
bool num[10];

int main() {

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	for (int i = 0; i < 26; i++) key[i] = false;
	for (int i = 0; i < 10; i++) num[i] = false;
	CLICK = false;

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

	al_hide_mouse_cursor(display);

	bool redraw = true;

	ALLEGRO_FONT *font = NULL;
	font = al_create_builtin_font();

	CJuego *ojuego = NULL;

	bool enMenu = true;
	ALLEGRO_BITMAP *bgmen;
	bgmen = al_load_bitmap("img/fondo2.png");
	
	Menu MyM = Menu();

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
				ojuego->Disparar();

			
			else if (ev.keyboard.keycode == ALLEGRO_KEY_P)
				ojuego->PersonajeCome();
			else if (ev.keyboard.keycode == ALLEGRO_KEY_O)
				ojuego->PersonajeTomarAgua();
			else if (ev.keyboard.keycode == ALLEGRO_KEY_L)
				ojuego->PersonajeCompraBalas();
			else if (ev.keyboard.keycode == ALLEGRO_KEY_B)
				ELEX = true;
			else if (ev.keyboard.keycode == 63)
				DEL = true;
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_A: key[0] = true; break;
			case ALLEGRO_KEY_B: key[1] = true; break;
			case ALLEGRO_KEY_C: key[2] = true; break;
			case ALLEGRO_KEY_D: key[3] = true; break;
			case ALLEGRO_KEY_E: key[4] = true; break;
			case ALLEGRO_KEY_F: key[5] = true; break;
			case ALLEGRO_KEY_G: key[6] = true; break;
			case ALLEGRO_KEY_H: key[7] = true; break;
			case ALLEGRO_KEY_I: key[8] = true; break;
			case ALLEGRO_KEY_J: key[9] = true; break;
			case ALLEGRO_KEY_K: key[10] = true; break;
			case ALLEGRO_KEY_L: key[11] = true; break;
			case ALLEGRO_KEY_M: key[12] = true; break;
			case ALLEGRO_KEY_N: key[13] = true; break;
			case ALLEGRO_KEY_O: key[14] = true; break;
			case ALLEGRO_KEY_P: key[15] = true; break;
			case ALLEGRO_KEY_Q: key[16] = true; break;
			case ALLEGRO_KEY_R: key[17] = true; break;
			case ALLEGRO_KEY_S: key[18] = true; break;
			case ALLEGRO_KEY_T: key[19] = true; break;
			case ALLEGRO_KEY_U: key[20] = true; break;
			case ALLEGRO_KEY_V: key[21] = true; break;
			case ALLEGRO_KEY_W: key[22] = true; break;
			case ALLEGRO_KEY_X: key[23] = true; break;
			case ALLEGRO_KEY_Y: key[24] = true; break;
			case ALLEGRO_KEY_Z: key[25] = true; break;
			case ALLEGRO_KEY_0: num[0] = true; break;
			case ALLEGRO_KEY_1: num[1] = true; break;
			case ALLEGRO_KEY_2: num[2] = true; break;
			case ALLEGRO_KEY_3: num[3] = true; break;
			case ALLEGRO_KEY_4: num[4] = true; break;
			case ALLEGRO_KEY_5: num[5] = true; break;
			case ALLEGRO_KEY_6: num[6] = true; break;
			case ALLEGRO_KEY_7: num[7] = true; break;
			case ALLEGRO_KEY_8: num[8] = true; break;
			case ALLEGRO_KEY_9: num[9] = true; break;
			}
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

			else if (ev.keyboard.keycode == 63)
				DEL = false;
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_A: key[0] = false; break;
			case ALLEGRO_KEY_B: key[1] = false; break;
			case ALLEGRO_KEY_C: key[2] = false; break;
			case ALLEGRO_KEY_D: key[3] = false; break;
			case ALLEGRO_KEY_E: key[4] = false; break;
			case ALLEGRO_KEY_F: key[5] = false; break;
			case ALLEGRO_KEY_G: key[6] = false; break;
			case ALLEGRO_KEY_H: key[7] = false; break;
			case ALLEGRO_KEY_I: key[8] = false; break;
			case ALLEGRO_KEY_J: key[9] = false; break;
			case ALLEGRO_KEY_K: key[10] = false; break;
			case ALLEGRO_KEY_L: key[11] = false; break;
			case ALLEGRO_KEY_M: key[12] = false; break;
			case ALLEGRO_KEY_N: key[13] = false; break;
			case ALLEGRO_KEY_O: key[14] = false; break;
			case ALLEGRO_KEY_P: key[15] = false; break;
			case ALLEGRO_KEY_Q: key[16] = false; break;
			case ALLEGRO_KEY_R: key[17] = false; break;
			case ALLEGRO_KEY_S: key[18] = false; break;
			case ALLEGRO_KEY_T: key[19] = false; break;
			case ALLEGRO_KEY_U: key[20] = false; break;
			case ALLEGRO_KEY_V: key[21] = false; break;
			case ALLEGRO_KEY_W: key[22] = false; break;
			case ALLEGRO_KEY_X: key[23] = false; break;
			case ALLEGRO_KEY_Y: key[24] = false; break;
			case ALLEGRO_KEY_Z: key[25] = false; break;
			case ALLEGRO_KEY_0: num[0] = false; break;
			case ALLEGRO_KEY_1: num[1] = false; break;
			case ALLEGRO_KEY_2: num[2] = false; break;
			case ALLEGRO_KEY_3: num[3] = false; break;
			case ALLEGRO_KEY_4: num[4] = false; break;
			case ALLEGRO_KEY_5: num[5] = false; break;
			case ALLEGRO_KEY_6: num[6] = false; break;
			case ALLEGRO_KEY_7: num[7] = false; break;
			case ALLEGRO_KEY_8: num[8] = false; break;
			case ALLEGRO_KEY_9: num[9] = false; break;
			}
		
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

			mouseX = (float)ev.mouse.x;
			mouseY = (float)ev.mouse.y;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			CLICK = true;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {

			redraw = false;

			bool c = CLICK;

			if (!enMenu) {
				if (ojuego != NULL)
					ojuego->Run(font);
			}
			else {

				MyM.update(bgmen, font, ojuego);

				if (MyM.getJugar()) {
					enMenu = false;
					ojuego = new CJuego();
				}

				if (MyM.getSalir()) break;
			}

			if (c)
				al_draw_circle(mouseX, mouseY, 5, al_map_rgb(255, 255, 255), 1);
			else
				al_draw_filled_circle(mouseX, mouseY, 5, al_map_rgb(255, 255, 255));

			CLICK = false;
			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_font(font);

	al_destroy_bitmap(bgmen);

	return 0;
}
