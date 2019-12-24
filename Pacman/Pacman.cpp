#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pacman.h"
#include "Bullet.h"
using namespace sf;
using namespace std;
		Pacman::Pacman(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name){
		playerScore = 0; 
		state = stay;
		znachenie = true;
		if (name == "Packman")
		{ 
			//Задаем спрайту один прямоугольник для //вывода одного игрока. IntRect – для приведения типов 
			//image.createMaskFromColor(Color(255, 255, 255));
		//image.createMaskFromColor(Color(0, 0, 0));
		sprite.setTextureRect(IntRect(0, 0, w, h)); 
			//sprite.setTextureRect(IntRect(0, 0, 40, 40));//получили нужный прямоугольник
			
		}
	}
		Pacman::~Pacman()
		{
			cout << "udalilas igrok";
			system("pause");
		}

	void 	Pacman::control(){
		/////////////////////////////Управление персонажем с анимацией///////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{ 
			state = left;
			speed = 0.1;
		}
		//координата Y, на которой герой изображен идущем вправо равна 0
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{ 
			state = right;
			speed = 0.1;
		}
		//координата Y на которой герой изображен идущим вверх равна 80
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			state = up;
			speed = 0.1;//направление вверх
		}
		//координата 0, это верхняя часть изображения с героем, от нее и отталкиваемся 
		//ровными квадратиками по 40.
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			state = down;
			speed = 0.1;//направление вниз
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down))&(Keyboard::isKeyPressed(Keyboard::Left)))
		{
			state = stay;
			speed = 0;
			dx=0;
			dy=0;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down))&(Keyboard::isKeyPressed(Keyboard::Right)))
		{
			state = stay;
			speed = 0;
			dx=0;
			dy=0;

		}
		if ((Keyboard::isKeyPressed(Keyboard::Up))&(Keyboard::isKeyPressed(Keyboard::Left)))
		{
			state = stay;
			speed = 0;
			dx=0;
			dy=0;

		}
		if ((Keyboard::isKeyPressed(Keyboard::Up))&(Keyboard::isKeyPressed(Keyboard::Right)))
		{
			state = stay;
			speed = 0;
			dx=0;
			dy=0;

		}
		if ((Keyboard::isKeyPressed(Keyboard::Down))&(Keyboard::isKeyPressed(Keyboard::Up)))
		{
			state = stay;
			speed = 0;
			dx=0;
			dy=0;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right))&(Keyboard::isKeyPressed(Keyboard::Left)))
		{
			state = stay;
			speed = 0;
			dx=0;
			dy=0;
		}
	}
	
	//Метод проверки столкновений с элементами карты 
	void 	Pacman::checkCollisionWithMap(float Dx, float Dy) {
		for (int i = y / 40; i < (y + h) / 40; i++) 
			for (int j = x / 40; j<(x + w) / 40; j++)
			{
				//”x” делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается.
				//Он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких тайлах 
				//Кроме того, j<(x + w)/32 - условие ограничения координат по “x”, т.е. координата самого 
				//правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева 
				// направо по иксу, проходя от левого квадрата (соприкасающегося с героем), до правого 
				// квадрата (соприкасающегося с героем)
				if ((TileMap[i][j] == '0') || (TileMap[i][j] == 's'))//если наш квадратик соответствует символу “0” 
					//(стена), то проверяем "направление скорости" персонажа: 
				{ 
					if (Dy>0)
					{
						//если мы шли вниз,
						y = i * 40 - h;//то стопорим (-h) координату “y” персонажа.
						//сначала получаем координату “i” нашего квадратика на карте и
						//затем вычитаем из высоты спрайта персонажа.
						dy = 0;
					}
					if (Dy<0)
					{ 
						y = i * 40 + 40;//аналогично с движением вверх.
						dy = 0;
					}
					if (Dx>0)
					{ 
						x = j * 40 - w;//если идем вправо, то координата “x” равна 
						//стена (символ 0) минус ширина персонажа 
						dx = 0;
					}
					if (Dx < 0)
					{ 
						x = j * 40 + 40; //аналогично идем влево
						dx = 0;
					}
								
					
				}
				if (TileMap[i][j] == 'f')//таблетки
				{
					znachenie = false;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'h')//точки 
				{
					playerScore ++; 
					TileMap[i][j] = ' ';
				}
			}
			

	}
	

	void 	Pacman::update(float time) //метод "оживления/обновления" объекта класса.
	
	{if (life) {//проверяем, жив ли герой

		control();//функция управления персонажем 
		switch (state)//делаются различные действия в зависимости от состояния 
		{ 
			case right: 
				{
					dx = speed; 
					CurrentFrame += 0.005*time; 
					if (CurrentFrame > 3) CurrentFrame -= 3;
					//проходим по координатам Х. получается 0
					sprite.setTextureRect(IntRect(40* int(CurrentFrame), 0, 40, 40));
					break; 
				}
			case left:
				{//состояние идти влево
					 dx = -speed;
					 CurrentFrame += 0.005*time;
					//служит для прохождения по "кадрам". переменная доходит до трех, суммируя произведение
					//времени и скорости. Изменив 0.005, можно изменить скорость анимации
					if (CurrentFrame > 3) CurrentFrame -= 3; //если пришли к третьему кадру откатываемся назад. 
					sprite.setTextureRect(IntRect(40* int(CurrentFrame), 40, 40, 40)); 
					break; 
				}
			case up:
				{//идти вверх
					dy = -speed; 
					CurrentFrame += 0.005*time; 
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(40* int(CurrentFrame), 80, 40, 40));
					//проходим по координатам Х. получается 80,0*2,80*3 и опять 80
					break;
				}
			case down:
				{//идти вниз
					dy = speed;
					CurrentFrame += 0.005*time; 
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(40* int(CurrentFrame), 120, 40, 40));
					break;
				}
			case stay:
				{//стоим 	
					dy = speed; dx = speed;
					break;
				}
			
		}
		
		x += dx*time; //движение по “X” 
		checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		y += dy*time; //движение по “Y” 
		checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		speed = 0; //обнуляем скорость, чтобы персонаж остановился. 
		sprite.setPosition(x, y); //выводим спрайт в позицию (x, y). 
			//бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
	}
	}