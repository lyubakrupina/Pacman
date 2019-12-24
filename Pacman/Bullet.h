#ifndef __BULLET_H__ 
#define __BULLET_H__
#include <SFML/Graphics.hpp>
#include "Pacman.h"
#include "Enemy.h"
#include "Entity.h"
#include "map.h" //подключили код с картой
using namespace sf;

////////////////////////////КЛАСС ПУЛИ//////////////////////// 
class Bullet :public Entity
{//класс пули 
public: 
	
	int direction;//направление пули //всё так же, только взяли в конце состояние игрока (int dir) //для задания направления полёта пули 
	
	Bullet(Image &image, float X, float Y, int W, int H, std::string Name, int dir) ;
	~Bullet();
		void update(float time) ;
	//	FloatRect getRect();
};
#endif // __BULLET_H__