#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
using namespace sf;
using namespace std;

		Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
		{
		
		if ((name == "PSH1")||(name == "PSH2")||(name == "PSH3"))
		{ 
			//������ ������� ���� ������������� ��� //������ ������ ������. IntRect � ��� ���������� ����� 
			//image.createMaskFromColor(Color(255, 255, 255));
		//image.createMaskFromColor(Color(0, 0, 0));
		
			sprite.setTextureRect(IntRect(0, 0, w, h)); 
			direction = rand() % (3);
			health=100;
			speed = 0.05;
				dx = speed;
		}
		
		}
		Enemy::~Enemy()
		{
			cout << "udalilas vrag";
			
		}

	void Enemy::checkCollisionWithMap (float Dx, float Dy)
	{
		for (int i = y / 40; i < (y + h) / 40; i++)//���������� �� ��������� �����    
			for (int j = x / 40; j<(x + w) / 40; j++) 
 
		{     if ((TileMap[i][j] == '0')||(TileMap[i][j] == 's'))//���� ������� - ������ �����    
				{      if (Dy > 0) 
						{      
							y = i * 40 - h; 
							dy = -0.05;        
							direction = rand() % (3); //����������� �������� �����       
						}//�� Y       
					   if (Dy < 0) 
						{		
							y = i * 40 + 40; 
							dy = 0.05;        
							direction = rand() % (3);//����������� �������� �����        
						}//������������ � �������� ������       
					   if (Dx > 0) 
						{       
							x = j * 40 - w; 
							dx = -0.05;        
							direction = rand() % (3);//����������� �������� �����        
						}//� ������ ����� �����      
					   if (Dx < 0) 
						{       
							x = j * 40 + 40; 
							dx = 0.05;        
							direction = rand() % (3); //����������� �������� �����       
					   }// � ����� ����� �����     
				}    
		}  
	}
	void Enemy::update(float time)  
	{   
		if ((name == "PSH1")||(name == "PSH2")||(name == "PSH3"))
		{  //��� ��������� � ����� ������ ������ ����� ����� 
 
		if (life) 
		{//���������, ��� �� �����   
			switch (direction)//�������� ��������� �������� � ����������� �� ���������  
			
			{   case 0:
					{//��������� ���� ������   
						state=right;
						dx = speed;   
						CurrentFrame += 0.005*time;   
						if (CurrentFrame > 3) CurrentFrame -= 3;  
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 40));   
						break;  
					}   
				case 1:
					{//��������� ���� �����   
						state=left;
						dx = -speed;   
						CurrentFrame += 0.005*time;  
						if (CurrentFrame > 3) CurrentFrame -= 3;   
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 40, 40, 40));  
						break;   
					}   
				case 2:
					{//���� ����� 
						state=up;
						dy = -speed;   
						CurrentFrame += 0.005*time;  
						if (CurrentFrame > 3) CurrentFrame -= 3;  
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 80, 40, 40)); 
						break;  
					}   
				case 3:
					{//���� ����  
						state=down;
						dy = speed;  
						CurrentFrame += 0.005*time;  
						if (CurrentFrame > 3) CurrentFrame -= 3;   
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 120, 40, 40));  
						break;   
					}  
			} 
 


 x += dx*time; //�������� �� �X�   
 checkCollisionWithMap(dx, 0);//������������ ������������ �� � 
 
 y += dy*time; //�������� �� �Y� 
 checkCollisionWithMap(0, dy);//������������ ������������ �� Y 
 
 sprite.setPosition(x, y); //������ � ������� (x, y). 
 
 if (health <= 0)
		{ 
			life = false;
		}//���� ������ ������ 0, ���� ����� 0, �� �������  
	}  
	} 
	} 
//����� Enemy ������ 
	
