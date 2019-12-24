#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Bullet.h"
using namespace sf;

		Enemy::Enemy(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
		
		//if (name == "Psh1")
		//{ 
			//Задаем спрайту один прямоугольник для //вывода одного игрока. IntRect – для приведения типов 
			//image.createMaskFromColor(Color(255, 255, 255));
		//image.createMaskFromColor(Color(0, 0, 0));
		
			sprite.setTextureRect(IntRect(0, 0, w, h)); 
			direction = rand() % (3);
			
			speed = 0.05;
				dx = speed;
		//}
	}
	void Enemy::checkCollisionWithMap (float Dx, float Dy)
	{
		for (int i = y / 40; i < (y + h) / 40; i++)//проходимся по элементам карты    
			for (int j = x / 40; j<(x + w) / 40; j++) 
 
		{     if ((TileMap[i][j] == '0')||(TileMap[i][j] == 's'))//если элемент - тайлик земли    
				{      if (Dy > 0) 
						{      
							y = i * 40 - h; 
							dy = -0.05;        
							direction = rand() % (3); //Направление движения врага       
						}//по Y       
					   if (Dy < 0) 
						{		
							y = i * 40 + 40; 
							dy = 0.05;        
							direction = rand() % (3);//Направление движения врага        
						}//столкновение с верхними краями       
					   if (Dx > 0) 
						{       
							x = j * 40 - w; 
							dx = -0.05;        
							direction = rand() % (3);//Направление движения врага        
						}//с правым краем карты      
					   if (Dx < 0) 
						{       
							x = j * 40 + 40; 
							dx = 0.05;        
							direction = rand() % (3); //Направление движения врага       
					   }// с левым краем карты     
				}    
		}  
	}
	void Enemy::update(float time)  
	{   
		//if (name == "EasyEnemy")
		//{//для персонажа с таким именем логика будет такой 
 
		if (life) 
		{//проверяем, жив ли герой   
			switch (direction)//делаются различные действия в зависимости от состояния  
			
			{   case 0:
					{//состояние идти вправо   
						dx = speed;   
						CurrentFrame += 0.005*time;   
						if (CurrentFrame > 3) CurrentFrame -= 3;  
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 0, 40, 40));   
						break;  
					}   
				case 1:
					{//состояние идти влево   
						dx = -speed;   
						CurrentFrame += 0.005*time;  
						if (CurrentFrame > 3) CurrentFrame -= 3;   
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 40, 40, 40));  
						break;   
					}   
				case 2:
					{//идти вверх   
						dy = -speed;   
						CurrentFrame += 0.005*time;  
						if (CurrentFrame > 3) CurrentFrame -= 3;  
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 80, 40, 40)); 
						break;  
					}   
				case 3:
					{//идти вниз  
						dy = speed;  
						CurrentFrame += 0.005*time;  
						if (CurrentFrame > 3) CurrentFrame -= 3;   
						sprite.setTextureRect(IntRect(40 * int(CurrentFrame), 120, 40, 40));  
						break;   
					}  
			} 
 


 x += dx*time; //движение по “X”   
 checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х 
 
 y += dy*time; //движение по “Y” 
 checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y 
 
 sprite.setPosition(x, y); //спрайт в позиции (x, y). 
 
 if (health <= 0)
		{ 
			life = false;
		}//если жизней меньше 0, либо равно 0, то умираем  
//	}  
	} 
	} //класс Enemy закрыт 