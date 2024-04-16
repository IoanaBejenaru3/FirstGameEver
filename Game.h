#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>

///std::vector <std::string> countries;
///int countries_number;

struct GameObject {

	sf::Sprite sprite;
	sf::Texture texture_unturned;
};

struct GameTile : GameObject {
	sf::Texture hover_texture;
	sf::Texture texture_turned;
	bool is_matched = 0; //playerul a gasit perechea
	bool is_set = 0; //a fost setata textura cu tara
	int country_number, number_of_turns = 0; //numarul tarii corespunzatoare si numarul de intoarceri al unui tile pentru a calcula punctele
	std::string denumire_tara;
};

const int board_size = 6;

class Game
{
private:
	sf::VideoMode video_mode;
	sf::RenderWindow* window;
	sf::Event sfml_event;
	GameObject background_image, check_mark, x_mark;
	GameTile board[board_size][board_size];
	sf::Sound wrong_sound, right_sound;
	bool end_game;
	int points = 0;

	void InitialiseSounds();
	void InitialiseBackground();
	void InitialiseTextureTurned();
	void InitialiseWindow();
	void InitialiseVariables();
	void SetUpBoard();

public:
	//CONSTRUCTORI
	Game();

	//GETTERS

	//SETTERS

	//OPERATORS

	//FUNCTIONS
	const bool Running() const;

	void CheckMatch();
	void DrawBackground();
	void DrawBoard();
	void PollEvents();
	void Update();
	void Render();
	//DESTRUCTOR 
	~Game();

};