#ifndef __PACMAN_H__ 
#define __PACMAN_H__
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "map.h" //���������� ��� � ������
using namespace sf;

///////////////////////////����� Pacman//////////////////////// 
////////////////////////////////////////////////////����� Pacman///////////////////////
class Pacman:public Entity { // ����� Pacman
public:
	int playerScore;//��� ���������� ����� ���� ������ � ������
	bool znachenie;
	//float timeBeforeShot; //���������� - ����� �� ��������
	Pacman(Image &image, float X, float Y, int W, int H, std::string Name);
	~Pacman();	
	void control();
	
	//����� �������� ������������ � ���������� ����� 
	void checkCollisionWithMap(float Dx, float Dy);
	

	void update(float time); //����� "���������/����������" ������� ������.
};
#endif // __PACMAN_H__