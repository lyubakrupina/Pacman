#ifndef __PACMAN_H__ 
#define __PACMAN_H__
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "map.h" //подключили код с картой
using namespace sf;

///////////////////////////КЛАСС Pacman//////////////////////// 
////////////////////////////////////////////////////КЛАСС Pacman///////////////////////
class Pacman:public Entity { // класс Pacman
public:
	int playerScore;//эта переменная может быть только у игрока
	bool znachenie;
	//float timeBeforeShot; //переменная - время до выстрела
	Pacman(Image &image, float X, float Y, int W, int H, std::string Name);
	~Pacman();	
	void control();
	
	//Метод проверки столкновений с элементами карты 
	void checkCollisionWithMap(float Dx, float Dy);
	

	void update(float time); //метод "оживления/обновления" объекта класса.
};
#endif // __PACMAN_H__