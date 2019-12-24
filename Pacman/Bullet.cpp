#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Entity.h"
using namespace sf;



	Bullet::Bullet(Image &image, float X, float Y, int W, int H, std::string Name, int dir) :Entity(image, X, Y, W, H, Name)
	{ 
			x = X; 
			y = Y; 
			direction = dir; 
			speed = 0.8; 
			w = h = 16; 
			life = true; //выше инициализация в конструкторе 
	}


void Bullet::update(float time) 
	{ 
		switch (direction) 
		{ 
		
		case 0: 
			dx = -speed; 
			dy = 0; 
			break;// state = left 
		
		case 1: 
			dx = speed; 
			dy = 0; 
			break;// state = right 
		
		case 2: 
			dx = 0; 
			dy = -speed; 
			break;// state = up 
		
		case 3: 
			dx = 0; 
			dy = speed; 
			break;// state = down 
		}

if (life)
{ 
	x += dx*time;//само движение пули по х 
	y += dy*time;//по у

	if (x <= 0) x = 20;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
	if (y <= 0) y = 20;
	if (x >= 800) x = 780;// задержка пули в правой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки (сервер может тормозить!)
	if (y >= 640) y = 620;
	
	for (int i = y / 40; i < (y + h) / 40; i++)//проходимся по элементам карты 
	
		for (int j = x / 40; j < (x + w) / 40; j++) 
		{ 
			if (TileMap[i][j] == '0' || TileMap[i][j] == 's'  )//если элемент наш тайлик земли, то 
				life = false;// то пуля умирает 
		}
sprite.setPosition(x + w , y + h );//задается позицию пули 
} 
}
