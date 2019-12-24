#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Entity.h"
#include "Pacman.h"
#include "map.h" //подключили код с картой
#include <list>
using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::

void randomMapGenerate(){
//рандомно расставляем камни
int randomElementX = 0;//переменная для хранения случайного элемента по горизонтали
int randomElementY = 0;//переменная для хранения случайного элемента по вертикали
srand(time(0));//Инициализация генератора случайных чисел
int countStone = 3;//количество таблеток
while (countStone>0)
{ 
	randomElementX = 1 + rand() % (WIDTH_MAP - 1);//псевдослучайное значение по “x” от 1 до 
//ширина карты-1. Ограничение введено чтобы не получать числа бордюра карты 
randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по “y”
if (TileMap[randomElementY][randomElementX] == ' ') {
	//если встретили символ пробел, 
	TileMap[randomElementY][randomElementX] = 'h'; //то ставим туда таблетку.
	countStone--; 
}
}
};


void randomMapGenerate1(){
//рандомно расставляем камни
int randomElementX = 0;//переменная для хранения случайного элемента по горизонтали
int randomElementY = 0;//переменная для хранения случайного элемента по вертикали
srand(time(0));//Инициализация генератора случайных чисел
int countStone = 3;//количество таблеток
while (countStone>0)
{ 
	randomElementX = 1 + rand() % (WIDTH_MAP - 1);//псевдослучайное значение по “x” от 1 до 
//ширина карты-1. Ограничение введено чтобы не получать числа бордюра карты 
randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по “y”
if (TileMap[randomElementY][randomElementX] == ' ') {
	//если встретили символ пробел, 
	TileMap[randomElementY][randomElementX] = 'f'; //то ставим туда таблетку.
	countStone--; 
}
}
};
				

int main() 
{
	//Создаём окно 
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(800, 600, desktop.bitsPerPixel), "Pacman");


	Image map_image;//объект изображения для карты 
	map_image.loadFromFile("images/Lanshaft 555.png");//загружаем файл для карты
	
	Texture map;//текстура карты 
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты 
	s_map.setTexture(map);//заливаем текстуру спрайтом
	
	Clock clock; //создаем переменную времени и одновременно запускаем часы!
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	Image PackmanImage;
	PackmanImage.loadFromFile("images/Pacman.png"); // загружаем изображение игрока

	Pacman p(PackmanImage, 80, 80, 40.0, 40.0,"Packman");//создаем объект p класса player, задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	
	int createObjectForMapTimer = 0;//Переменная под время для генерирования камней
	int createObjectForMapTimer1 = 0;//Переменная под время для генерирования камней
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart(); 
		time = time / 800;


		createObjectForMapTimer += time;//наращиваем таймер
		if (createObjectForMapTimer>2000)
		{ 
			randomMapGenerate();//генерация камней
			createObjectForMapTimer = 0;//обнуляем таймер
		}

		createObjectForMapTimer1 += time;//наращиваем таймер
		if (createObjectForMapTimer1>3000)
		{ 
			randomMapGenerate1();//генерация камней
			createObjectForMapTimer1 = 0;//обнуляем таймер
		}
		sf::Event event; 
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
				window.close(); 
		}
		
		
		
		
		p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml, // передавая время в качестве параметра функции update.
		window.clear(); 

		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
				{ 
					if (TileMap[i][j] == ' ') 
						s_map.setTextureRect(IntRect(0, 0, 40, 40)); //если
					//встретили символ пробел, то рисуем 1-й квадратик 
					if (TileMap[i][j] == 's') 
						s_map.setTextureRect(IntRect(40, 0, 40, 40));//если
					//встретили символ s, то рисуем 2й квадратик
					if ((TileMap[i][j] == '0')) 
						s_map.setTextureRect(IntRect(80, 0, 40, 40));//если
					//встретили символ 0, то рисуем 3й квадратик
				if ((TileMap[i][j] == 'f')) 
				
					s_map.setTextureRect(IntRect(120, 0, 40, 40));
					
				
					if ((TileMap[i][j] == 'h')) 
						s_map.setTextureRect(IntRect(200, 0, 40, 40));
						s_map.setPosition(j * 40, i * 40);//раскладываем квадратики в карту.
						window.draw(s_map);//рисуем квадратики на экран
			}


		window.draw(p.sprite);//выводим спрайт на экран
		window.display(); 
	}
return 0;
}