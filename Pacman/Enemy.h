#ifndef __ENEMY__ 
#define __ENEMY__
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "map.h" //подключили код с картой
using namespace sf;

class Enemy:public Entity { 
public:

	int direction;
	
	Enemy(Image &image, float X, float Y, int W, int H, std::string Name);
	~Enemy();	
	
	
	//Метод проверки столкновений с элементами карты 
	void checkCollisionWithMap(float Dx, float Dy);
	

	void update(float time); //метод "оживления/обновления" объекта класса.
};
#endif // __ENTITY_H__