#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "menu.h"
void menu(RenderWindow & window) 
{
	
	Texture menuTexture1, menuTexture2, menuTexture3,menuTexture4, aboutTexture,upravTexture, menuBackground;
	menuTexture1.loadFromFile("images/image1menu.png");
	menuTexture2.loadFromFile("images/image2menu.png");
	menuTexture4.loadFromFile("images/image6menuupravlenie.png");
	menuTexture3.loadFromFile("images/image3menu.png");
	aboutTexture.loadFromFile("images/image5menuavtor.png");
	upravTexture.loadFromFile("images/image7menuupravlenie.png");
	menuBackground.loadFromFile("images/image4menufon.png");
	
	
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3),menu4(menuTexture4), about(aboutTexture),uprav(upravTexture), menuBg(menuBackground);
	
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(70, 30);
	menu2.setPosition(70, 150);
	menu4.setPosition(70, 250);
	menu3.setPosition(70, 365);
	menuBg.setPosition(0, 0);
	about.setPosition(150,70);
	uprav.setPosition(0,0);
 
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(0, 0, 0));
 
		if (IntRect(100, 160, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(100, 260, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
		if (IntRect(100, 460, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Red); menuNum = 3; }
		if (IntRect(100, 360, 300, 50).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Red); menuNum = 4; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 4) { window.draw(uprav); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3)  { window.close(); isMenu = false; }
 
		}
 
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		


		window.display();
	}
	////////////////////////////////////////////////////
}

