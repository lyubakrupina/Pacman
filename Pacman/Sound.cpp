#include <SFML\Audio.hpp>
#include "Sound.h"
using namespace sf;
void sound()
{

sf::SoundBuffer buffer; 
	buffer.loadFromFile("Shoot.ogg");// ��� ��������� � ����� ��� ��
	sf::Sound shoot;
	shoot.setBuffer(buffer);
}