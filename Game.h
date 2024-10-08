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
	std::string country_name;
};

const int board_size = 6;


//interfata - orice joc trebeuie sa aiba functii pt a-l "manageria" 
class IGame {
public:
	virtual void DescribeTypeOfGame() const = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual ~IGame() {}
};

//clasa abstracta - TriviaGame este un tip de joc deci mostenim interfata
//dar asa cum spune si numele este un joc abstracat : exista multe tipuri de triva game
//deci nu va fi o clasa instantiabila trebuie sa definim o clasa specifica
//care este joculetul pe care incerc sa-l creez 
class TriviaGame: public IGame{
public:
    void DescribeTypeOfGame() const override
	{
		std::cout << "A trivia game is a quiz-style game where players answer questions on various topics to test their knowledge and compete for points." << std::endl;
	} 
	virtual void DescribeRules() = 0;
	virtual void Update() override = 0;
	virtual void Render() override = 0;
	virtual ~TriviaGame() {} 
};

class Game : public TriviaGame
{
private:
	sf::VideoMode video_mode;
	sf::RenderWindow* window;
	sf::Event sfml_event;
	sf::Text text, text2;
	sf::Font font;
	GameObject check_button, hint_button, pass_button, score;
	GameObject background_image, check_mark, x_mark;
	GameTile board[board_size][board_size];
	//sf::Sound wrong_sound, right_sound;
	bool end_game;
	int points;

	void InitialiseText();
	void InitialiseButtons();
	void InitialiseSounds();
	void InitialiseBackground();
	void InitialiseTextureTurned();
	void InitialiseWindow();
	void InitialiseVariables();
	void SetUpBoard();

public:
	
	//CONSTRUCTORI
	Game();
	//constructor de copiere
	Game(const Game& other);
	//GETTERS

	//SETTERS

	//OPERATORS

	//operator de atribuire prin copiere
	Game& operator=(const Game& other);

	//operator de atribuire prin mutare
	Game& operator=(const Game&& other);

	//FUNCTIONS
	const bool Running() const;

	void DescribeRules() override;
	void DrawButtons();
	void CheckMatch();
	void DrawBackground();
	void DrawBoard();
	void DrawOptions();
	void DrawText();
	void PollEvents();
	void Update() override;
	void Render() override;
	//DESTRUCTOR 
	~Game();
};

