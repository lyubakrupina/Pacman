#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "Entity.h"
#include "Pacman.h"
#include "Enemy.h"
#include "Bullet.h"
#include "menu.h"

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




bool startGame(){
	//Создаём окно 
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	//RenderWindow window(sf::VideoMode(822, 600), "Kychka-pc.ru 31");
	sf::RenderWindow window(sf::VideoMode(800, 600, desktop.bitsPerPixel), "Pacman");

	
	menu(window);//вызов меню
	
	// ТЕКСТ В ИГРЕ
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("",font,23);
	text.setColor(Color::Red);//покрасили текст в красный 
	text.setStyle(Text::Bold);//жирный текст. 
	
    Music music;
	music.openFromFile("What.ogg");
	music.play();


	Image map_image;//объект изображения для карты 
	map_image.loadFromFile("images/Lanshaft 555.png");//загружаем файл для карты
	
	Texture map;//текстура карты 
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты 
	s_map.setTexture(map);//заливаем текстуру спрайтом
	
	Clock clock; //создаем переменную времени и одновременно запускаем часы!
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	std::list<Entity*> enemies;
	std::list<Entity*>::iterator it; // список врагов
	std::list<Entity*>::iterator it2; // для отталкивания между врагами
	std::list<Entity*> Bullets; //список пуль


	Image PackmanImage;
	Image EnemyImageSh1;
	Image EnemyImageSh2;
	Image EnemyImageSh3;
	Image BulletImage;//изображение для пули 
	
	PackmanImage.loadFromFile("images/Pacman2.png"); // загружаем изображение игрока
	EnemyImageSh1.loadFromFile("images/PSH1.png");
	EnemyImageSh2.loadFromFile("images/PSH2.png");
	EnemyImageSh3.loadFromFile("images/PSH3.png");
	BulletImage.loadFromFile("images/Bullet.png");
	
	
	const int ENEMY_COUNT = 2; //максимальное количество врагов в игре 
	int enemiesCount = 0; 

	for (int i = 0; i < ENEMY_COUNT; i++) 
		{ 
			float xr = 150 + rand() % 500; // случайная координата врага на поле игры по оси “x” 
			float yr = 150 + rand() % 350; // случайная координата врага на поле игры по оси “y”  //создаем врагов и помещаем в список  
			enemies.push_back(new Enemy(EnemyImageSh1, xr, yr, 40, 40, "PSH1"));  
			enemies.push_back(new Enemy(EnemyImageSh2, xr, yr, 40, 40, "PSH2"));
			enemies.push_back(new Enemy(EnemyImageSh3, xr, yr, 40, 40, "PSH3"));
			
			enemiesCount += 1; //увеличили счётчик врагов 
	} 

	
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
										
				
				if (p.znachenie == false)
			{	
				p.update(time); //обновляем его

				//p.timeBeforeShot += time; //приращаем время до выстрела
				
				if (event.type == sf::Event::KeyPressed) 
				{ 
					//if (p.timeBeforeShot<500){
					if (event.key.code == sf::Keyboard::P) 
					{	
						const int k=5;
						for (int i = 0; i < k; i++)
						{
							Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 16, 16, "Bullet", p.state)); 
							
							if (k>5)
							{
							  const int k=0;
							  p.znachenie = true;
							}
						} 
					
					
					}

				
				}
			}
		}
		

		if (Keyboard::isKeyPressed(sf::Keyboard::Tab))//перезагружаем игру
		{
			return true;
		}
		
		if (Keyboard::isKeyPressed(sf::Keyboard::Escape))//выходим из игры
		{
			return false;
		}
		
		
		p.update(time);//оживляем объект “p” класса “Player” с помощью времени sfml // передавая время в качестве параметра функции update.
		

		//ОЖИВЛЯЕМ ВРАГОВ
		for  (it = enemies.begin(); it != enemies.end(); it++)   
			{   
				(*it)->update(time); //запускаем метод update()  
			} 
		
		
		//ОЖИВЛЯЕМ ПУЛИ
		for (it = Bullets.begin(); it != Bullets.end(); it++) 
		{ 
			(*it)->update(time); //запускаем метод update() 
		}


		//Проверяем список на наличие "мертвых" пуль и удаляем их 
		for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца 
		{// если этот объект мертв, то удаляем его 
			if ((*it)-> life == false) 
			{ 
				delete (*it);
				it = Bullets.erase(it); 
			} 
			else it++; //и идем курсором (итератором) к след объекту. 
		}


		if (p.life == true)
			{//если игрок жив  
				for (it = enemies.begin(); it != enemies.end(); it++)
					{//бежим по списку врагов   
						if ((p.getRect().intersects((*it)->getRect())))     
							{      
								p.health = 0;  
								p.life = false;
								std::cout << "you are lose";  
							}    
					}  		
		}
	
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

		


		//ТЕКСТ В ИГРЕ объявили переменную здоровья,времени и баллов 
		std::ostringstream playerHealthString, gameTimeString, playerScoreString;
		
		playerHealthString << p.health; 
		gameTimeString << gameTime; //формируем строку 
		playerScoreString << p.playerScore; 
		text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str() + "\nБаллы: " + playerScoreString.str());//задаем строку тексту 
		text.setPosition(3, 0);//задаем позицию текста 
		window.draw(text);//рисуем этот текст
		window.draw(p.sprite);//выводим спрайт на экран




		//	for (it2 = enemies.begin(); it2 != enemies.end(); it2++)
		//	{
		//		if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники
		//		if (((((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "PSH1") && ((*it2)->name == "PSH2")) && ((*it2)->name == "PSH3")))//если столкнулись два объекта и они враги
		//		{
		//			(*it)->dx *= -0.05;//меняем направление движения врага
		//			(*it)->sprite.scale(-1, 1);//отражаем спрайт по горизонтали
			//	}
			//}


		//РИСУЕМ ВРАГОВ
		for (it = enemies.begin(); it != enemies.end(); it++)
			{ 
				if ((*it)->life)
				window.draw((*it)->sprite); //рисуем enemies объекты 
			}

		//РИСУЕМ ПУЛИ
		for (it = Bullets.begin(); it != Bullets.end(); it++) 
			{ 

				if ((*it)->life) //если пули живы 
				window.draw((*it)->sprite); //рисуем объекты
			}

		



		window.display(); 
		
	}

}

void gameRunning() //функция перезагружает игру
{
	if (startGame()) 
	{
		gameRunning();
		

	}
}
int main() 
{
	gameRunning();
	
	return 0;
}