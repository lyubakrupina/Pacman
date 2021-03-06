#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Entity.h"
#include "Pacman.h"
#include "Enemy.h"
#include "Bullet.h"
#include "menu.h"
#include "map.h" //���������� ��� � ������
#include <list>
using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ sf::

void randomMapGenerate(){
//�������� ����������� ��������
int randomElementX = 0;//���������� ��� �������� ���������� �������� �� �����������
int randomElementY = 0;//���������� ��� �������� ���������� �������� �� ���������
srand(time(0));//������������� ���������� ��������� �����
int countStone = 3;//���������� ��������
while (countStone>0)
{ 
	randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������������� �������� �� �x� �� 1 �� 
//������ �����-1. ����������� ������� ����� �� �������� ����� ������� ����� 
randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� �y�
if (TileMap[randomElementY][randomElementX] == ' ') {
	//���� ��������� ������ ������, 
	TileMap[randomElementY][randomElementX] = 'h'; //�� ������ ���� ��������.
	countStone--; 
}
}
};


void randomMapGenerate1(){
//�������� ����������� ����� �������� �����
int randomElementX = 0;//���������� ��� �������� ���������� �������� �� �����������
int randomElementY = 0;//���������� ��� �������� ���������� �������� �� ���������
srand(time(0));//������������� ���������� ��������� �����
int countStone = 3;//���������� ��������
while (countStone>0)
{ 
	randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������������� �������� �� �x� �� 1 �� 
//������ �����-1. ����������� ������� ����� �� �������� ����� ������� ����� 
randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� �y�
if (TileMap[randomElementY][randomElementX] == ' ') {
	//���� ��������� ������ ������, 
	TileMap[randomElementY][randomElementX] = 'f'; //�� ������ ���� ��������.
	countStone--; 
}
}
};
				
bool startGame(){
	srand (time(NULL));
	//int DeadEnemyGame=0;
	//������ ���� 
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(800, 600, desktop.bitsPerPixel), "Pacman");

	
	menu(window);//����� ����
	
	// ����� � ����
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("",font,23);
	text.setColor(Color::Red);//��������� ����� � ������� 
	text.setStyle(Text::Bold);//������ �����. 
  

	Image map_image;//������ ����������� ��� ����� 
	map_image.loadFromFile("images/Lanshaft 555.png");//��������� ���� ��� �����
	
	Texture map;//�������� ����� 
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� ����� 
	s_map.setTexture(map);//�������� �������� ��������
	
	Clock clock; //������� ���������� ������� � ������������ ��������� ����!
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.


	Image PackmanImage;
	Image EnemyImageSh1;
	Image EnemyImageSh2;
	Image EnemyImageSh3;
	Image BulletImage;//����������� ��� ���� 
	
	PackmanImage.loadFromFile("images/Pacman2.png"); // ��������� ����������� ������
	EnemyImageSh1.loadFromFile("images/PSH1.png");
	EnemyImageSh2.loadFromFile("images/PSH2.png");
	EnemyImageSh3.loadFromFile("images/PSH3.png");
	BulletImage.loadFromFile("images/Bullet.png");


	Texture loseTexture;
	loseTexture.loadFromFile("images/lose.png");
	Sprite lose(loseTexture);

	Texture winTexture;
	winTexture.loadFromFile("images/win.png");
	Sprite win(winTexture);
	int KolPriv=0;
	Pacman p(PackmanImage, 80, 80, 40.0, 40.0,"Packman");//������� ������ p ������ player, ������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.
	
	std::list<Entity*> enemies;//������ ������
	std::list<Entity*>::iterator it; // ��������
	std::list<Entity*>::iterator it2; // �������� 
	std::list<Entity*> Bullets; //������ ����
	std::list<Entity*> Bullets2; //������ ���� �����


	

	
	const int ENEMY_COUNT = 2; //������������ ���������� ������ � ���� 
	int enemiesCount = 0; //������� ��� ������ � ����


	for (int i = 0; i < ENEMY_COUNT; i++) 
		{ 
			float xr = 150 + rand() % 500; // ��������� ���������� ����� �� ���� ���� �� ��� �x� 
			float yr = 150 + rand() % 350; // ��������� ���������� ����� �� ���� ���� �� ��� �y�  //������� ������ � �������� � ������  
			enemies.push_back(new Enemy(EnemyImageSh1, xr, yr, 40, 40, "PSH1"));  
			//float pr = 150 + rand() % 450; // ��������� ���������� ����� �� ���� ���� �� ��� �x� 
			//float lr = 150 + rand() % 500;
			enemies.push_back(new Enemy(EnemyImageSh2, xr, yr, 40, 40, "PSH2"));
			//float er = 150 + rand() % 350; // ��������� ���������� ����� �� ���� ���� �� ��� �x� 
			//float dr = 150 + rand() % 460;
			enemies.push_back(new Enemy(EnemyImageSh3, xr, yr, 40, 40, "PSH3"));
			
			enemiesCount += 1; //��������� ������� ������ 
	} 










	int createObjectForMapTimer = 0;//���������� ��� ����� ��� ������������� ������
	int createObjectForMapTimer1 = 0;//���������� ��� ����� ��� ������������� ������
	int createObjectForMapTimer2 = 0;//���������� ��� ����� ��� ������������� ������
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		

		if (p.life) gameTime =gameTimeClock.getElapsedTime().asSeconds();
		clock.restart(); 
		time = time / 800;


		createObjectForMapTimer += time;//���������� ������
		if (createObjectForMapTimer>800)
		{
			
			for (it =enemies.begin();it!=enemies.end();it++)
			{
				
				if ((*it)->life){
					Bullets2.push_back(new Bullet(BulletImage, (*it)->x, (*it)->y, 16, 16, "Bullet", (*it)->state)); 
				}
			}

			createObjectForMapTimer=0;
		}

			createObjectForMapTimer2 += time;//���������� ������
		if (createObjectForMapTimer2>2000)
		{ 
			randomMapGenerate();//��������� ��������
			createObjectForMapTimer2 = 0;//�������� ������
		}

		createObjectForMapTimer1 += time;//���������� ������
		if (createObjectForMapTimer1>3000)
		{ 
			randomMapGenerate1();//��������� �������� �����
			createObjectForMapTimer1 = 0;//�������� ������
		}
	
		sf::Event event; 
		while (window.pollEvent(event)) 
		{ 
			if (event.type == sf::Event::Closed) 
				window.close();
										
				
				if (p.znachenie == false)
			{	
				p.update(time); //��������� ���

				
				if (event.type == sf::Event::KeyPressed) 
				{ 
					
					if (event.key.code == sf::Keyboard::P) 


			

					{	
					
							Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 16, 16, "Bullet", p.state)); 
							
							  p.znachenie = true;
											
					} 

				}
			} 				
					
		}

			
	
	

		if (Keyboard::isKeyPressed(sf::Keyboard::Tab))//������������� ����
		{
			return true;
		}

		if (Keyboard::isKeyPressed(sf::Keyboard::Escape))//������� �� ����
		{
			return false;
		}
		
		
		p.update(time);//�������� ������ �p� ������ �Player� � ������� ������� sfml // ��������� ����� � �������� ��������� ������� update.
		


		//�������� ������
		for  (it = enemies.begin(); it != enemies.end(); it++)   
			{   
				(*it)->update(time); //��������� ����� update()  
				
			} 
		
		
		//�������� ����
		for (it = Bullets.begin(); it != Bullets.end(); it++) 
		{ 
			(*it)->update(time); //��������� ����� update() 
		}


		//�������� ����22
		for (it2 = Bullets2.begin(); it2 != Bullets2.end(); it2++) 
	{ 
			(*it2)->update(time); //��������� ����� update() 
			
		}
		
		//��������� ������ �� ������� "�������" ���� � ������� �� 
		for (it = Bullets.begin(); it != Bullets.end(); )//������� ��� ���������� �� ������ �� ����� 
		{// ���� ���� ������ �����, �� ������� ��� 
			if ((*it)-> life == false) 
			{ 
				delete (*it);
				it = Bullets.erase(it); 
			} 
			else it++; //� ���� �������� (����������) � ���� �������. 
		}

		//2222
		for (it2 = Bullets2.begin(); it2 != Bullets2.end(); )//������� ��� ���������� �� ������ �� ����� 
		{// ���� ���� ������ �����, �� ������� ��� 
			if ((*it2)-> life == false) 
			{ 
				delete (*it2);
				it2 = Bullets2.erase(it2); 
			} 
			else it2++; //� ���� �������� (����������) � ���� �������. 
		}

		//��������� ������ �� ������� "�������" ������
		for (it = enemies.begin(); it != enemies.end(); )//������� ��� ���������� �� ������ �� ����� 
		{// ���� ���� ������ �����, �� ������� ��� 
			if ((*it)-> life == false) 
			{ 
				delete (*it);
				it = enemies.erase(it); 
			} 
			else it++; //� ���� �������� (����������) � ���� �������. 
		}

	

		if (p.life == true)
			{//���� ����� ���  
				for (it = enemies.begin(); it != enemies.end(); it++)
					{//����� �� ������ ������   
						if ((p.getRect().intersects((*it)->getRect())))     
							{      
								p.health = 0;  
								p.life = false;
								std::cout << "you are lose";  

								//����� ������ ������
								lose.setPosition(0,0);
								window.draw(lose); 
								window.display();
								while (!Keyboard::isKeyPressed(Keyboard::Escape));
								window.close();
								startGame();
							}    
					}  		
		}
	
	


		if (p.health<=0)
		{		
				//std::cout << p.health;
				p.health = 0;  
				p.life = false;
				std::cout << "you are lose";  
				
				//����� ������ ������
				lose.setPosition(0,0);
				window.draw(lose); 
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape));
				window.close();
				startGame();
		}

		
	
		for (it2 = Bullets.begin(); it2 != Bullets.end(); it2++)//���� ��������
			{
				for (it =enemies.begin(); it !=enemies.end(); it++){//�����
					if ((*it)->getRect().intersects((*it2)->getRect()))
					{
						KolPriv++;
						(*it)->life=0;
					}
				}
			}
			//����������� ���� ����� � ��������
			if (p.life == true)
			{
			for (it2 = Bullets2.begin(); it2 != Bullets2.end(); it2++)//���� ������
			{
					if (p.getRect().intersects((*it2)->getRect()))
					{
						p.health = p.health-20;  
						//p.life=0;
						(*it2)->life=0;
					}
			
			}
			}

			for (it2 = Bullets.begin(); it2 != Bullets.end(); it2++)//���� ��������
			{
				for (it =Bullets2.begin(); it !=Bullets2.end(); it++){//�����
					if ((*it)->getRect().intersects((*it2)->getRect()))
					{
						(*it2)->life=0;
						(*it)->life=0;
					}
				}
			}
			if ((p.playerScore>=40)&& (KolPriv==6))
					{


							//����� ������ ������
							win.setPosition(0,0);
							window.draw(win); 
							window.display();
							while (!Keyboard::isKeyPressed(Keyboard::Escape));
							window.close();
							startGame();
			
					}

		window.clear(); 


		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
				{ 
					if (TileMap[i][j] == ' ') 
						s_map.setTextureRect(IntRect(0, 0, 40, 40)); //����
					//��������� ������ ������, �� ������ 1-� ��������� 
					if (TileMap[i][j] == 's') 
						s_map.setTextureRect(IntRect(40, 0, 40, 40));//����
					//��������� ������ s, �� ������ 2� ���������
					if ((TileMap[i][j] == '0')) 
						s_map.setTextureRect(IntRect(80, 0, 40, 40));//����
					//��������� ������ 0, �� ������ 3� ���������
					if ((TileMap[i][j] == 'f')) 
				
					s_map.setTextureRect(IntRect(120, 0, 40, 40));
					
				
					if ((TileMap[i][j] == 'h')) 
						s_map.setTextureRect(IntRect(200, 0, 40, 40));
						s_map.setPosition(j * 40, i * 40);//������������ ���������� � �����.
						window.draw(s_map);//������ ���������� �� �����
			}

		

		//����� � ���� �������� ���������� ��������,������� � ������ 
		std::ostringstream playerHealthString, gameTimeString, playerScoreString;
		
		playerHealthString << p.health; 
		 gameTimeString << gameTime; //��������� ������ //��������� ������ 
		playerScoreString << p.playerScore; 
		text.setString("��������: " + playerHealthString.str() + "\n����� ����: " + gameTimeString.str() + "\n�����: " + playerScoreString.str());//������ ������ ������ 
		text.setPosition(3, 0);//������ ������� ������ 
		window.draw(text);//������ ���� �����
		window.draw(p.sprite);//������� ������ �� �����










			

		//������ ������
		for (it = enemies.begin(); it != enemies.end(); it++)
			{ 
				if ((*it)->life)
				window.draw((*it)->sprite); //������ enemies ������� 
			}

		//������ ����
		for (it = Bullets.begin(); it != Bullets.end(); it++) 
			{ 

				if ((*it)->life) //���� ���� ���� 
				window.draw((*it)->sprite); //������ �������
			}


		
		//������ ����2
		for (it2 = Bullets2.begin(); it2 != Bullets2.end(); it2++) 
			{ 

				if ((*it2)->life) //���� ���� ���� 
				window.draw((*it2)->sprite); //������ �������
			}
		
		window.display(); 
		
	}
}


void gameRunning() //������� ������������� ����
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