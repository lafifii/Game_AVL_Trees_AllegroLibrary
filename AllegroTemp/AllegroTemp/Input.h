#pragma once

class Input {
	string in;
	float x, y;
	int maxSize;
	int lastKey;
public:

	Input(float x = 0, float y = 0) : x(x), y(y) {

		lastKey = -1;
		maxSize = 10;
		x = width - 50;
	}
	
	void update(ALLEGRO_FONT *f) {

		al_draw_filled_rectangle(x - 4, y - 4, x + (maxSize * 9), y + 8, al_map_rgb(0, 0, 0));
		al_draw_text(f, al_map_rgb(255, 255, 255), x, y, ALLEGRO_ALIGN_LEFT, in.c_str());
		
		if(in.size() < maxSize){
			for (int i = 0; i < 25; i++) {

				if (key[i]) {
					key[i] = false;
					if('A'+i !='B')
						in.push_back('A' + i);
					break;
				}
			}
			if (SPACE) {
				in.push_back(' ');
				SPACE = false;
			}
			for (int i = 0; i < 10; i++) {

				if (num[i]) {
					num[i] = false;
					in.push_back('0' + i);
					break;
				}
			}
		}

		if (DEL) {
			if(!in.empty())
				in.erase(in.begin() + (in.size() - 1));
			DEL = false;
		}
	}
	string getString() { return in; }


};