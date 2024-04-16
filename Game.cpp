#include "Game.h"
#include <cmath>
//TO DO
//SA IMPLEMENTEZ O FUNCTIONALITATE CARE DA PUNCTE PROPORTIONAL CU DE CATE ORI INCEARCA PLAYERUL
//SA FACA MATCH-UL
//SA SCRIE NUMELE TARII
//SA AIBA OPTIUNEA DE HINT
//OPTIUNEA DE QUIT DACA NU STIE O TARA PT A NU PIERDE PUNCTE
//SA SE AFISEZE SCORUL
//DE ADAUGAT IN CAZUL IN CARE NU FACE MATCH PLAYERUL, UN SPRITE CU X ROSU CU FUNDAL TRANSPARENT PESTE CEL DEJA DESENAT
//si cu bifa cand facem matchul
//sa vad cum fac cu denumirile tarilor sa stiu cui i le atribui


const int perfect_match_points = 1000;
const int cell_size = 100;

int turned_sprite1_i, turned_sprite1_j, turned_sprite2_i, turned_sprite2_j;
int num_clicks = 0;
bool set_numbers[200]; //un vector caracteristic in care tinemi minte daca tilex unde x este un nr de la 1-195 (tarile lumii) a fost pusa deja in board sau nu

void Game::InitialiseSounds()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("cute-level-up-3-189853.mp3"))
	{
		std::cout << "Nu s-a incarcat un sound pt corect" << std::endl;
		return;
	}
	this->right_sound.setBuffer(buffer);
	if (!buffer.loadFromFile("error-126627.mp3"))
	{
		std::cout << "Nu s-a incarcat un sound pt gresit" << std::endl;
		return;
	}
	this->wrong_sound.setBuffer(buffer);
	std::cout << "AM REUSITTTT" << std::endl;
}

void Game::InitialiseVariables()
{
	this->end_game = false;

	/*if (!check_mark.texture_unturned.loadFromFile("bifa.png"))
	{
		std::cout << "Nu s-a incarcat textura pentru bifa" << std::endl;
	}
	check_mark.sprite.setTexture(check_mark.texture_unturned);

	if (!x_mark.texture_unturned.loadFromFile("xmark.png"))
	{
		std::cout << "Nu s-a incarcat textura pentru X" << std::endl;
	}
	x_mark.sprite.setTexture(x_mark.texture_unturned);*/
}

void Game::InitialiseWindow()
{
	this->video_mode = sf::VideoMode(1280, 720);
	this->window = new sf::RenderWindow(this->video_mode, "Learn the countries", sf::Style::Close | sf::Style::Titlebar);
}

void Game::InitialiseBackground()
{
	if (!background_image.texture_unturned.loadFromFile("background_image.png"))
	{
		std::cout << "Nu s-a incarcat textura pentru background" << std::endl;
	}
	background_image.sprite.setTexture(background_image.texture_unturned);
}

//CONSTRUCTORI
Game::Game()
{
	srand(static_cast<unsigned>(time(0)));
	this->InitialiseSounds();
	this->InitialiseVariables();
	this->InitialiseWindow();
	this->InitialiseBackground();
	this->InitialiseTextureTurned();
	this->SetUpBoard();
}


//FUNCTIONS


//in aceasta functie voi initializa textura doi a fiecarei piese din board cu o anumita tara
//trebuie sa am grija ca tara sa nu se repete
//trebuie sa am grija sa pun tara de doua ori si sa fie pe pozitii diferite din board

void Game::InitialiseTextureTurned() //nu e testata inca
{
	int number, i2, j2;
	char current_tile_path[60];
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
			if (!board[i][j].is_set) //doar daca nu e inca setat acest tile
			{

				//generam un numar corespunzator unei tari
				number = rand() % 18;
				while (set_numbers[number]) number = rand() % 18; //cat timp numarul ala a fost deja folosit
				//am setat tara ca fiind pusa in joc
				set_numbers[number] = 1; //am pus acea tara o data in joc, nu vrem sa se repete
				board[i][j].is_set = 1; //punem inainte pt a nu pune cumva pe ac poz
				//cautam un alt sprite pt i,j pt a putea avea doua sprite-uri la fel pt match
				i2 = rand() % 6;
				j2 = rand() % 6;
				while (board[i2][j2].is_set)
				{
					i2 = rand() % 6;
					j2 = rand() % 6;
				}
				//incarcam textura2 cu tara respectiva in cele doua sprite-uri
				sprintf_s(current_tile_path, "countries/tile%03d.png", number);
				if (!board[i][j].texture_turned.loadFromFile(current_tile_path))
				{
					std::cout << "Nu s-a incarcat o textura de tip tara" << std::endl;
					break;
				}
				if (!board[i2][j2].texture_turned.loadFromFile(current_tile_path))
				{
					std::cout << "Nu s-a incarcat o textura de tip tara" << std::endl;
					break;
				}
				//am adaugat o tara si am setat doua sprite-uri din board
				board[i2][j2].is_set = 1;

				board[i][j].country_number = number;
				board[i2][j2].country_number = number;


			}
	}
}


void Game::SetUpBoard()
{
	std::string texture_path = "greytile.png";
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			if (!board[i][j].texture_unturned.loadFromFile(texture_path)) {
				std::cout << "Nu s-a incarcat tile" << std::endl; // Error loading texture
				break;
			}
			if (!board[i][j].hover_texture.loadFromFile("hover.png"))
			{
				std::cout << "Nu s-a incarcat hover-ul" << std::endl;
				break;
			}
			board[i][j].sprite.setTexture(board[i][j].texture_unturned);
			board[i][j].sprite.setPosition(50 + j * (cell_size + 5), 50 + i * (cell_size + 5));
		}
	}
}

void Game::CheckMatch()
{
	if (board[turned_sprite1_i][turned_sprite1_j].country_number == board[turned_sprite2_i][turned_sprite2_j].country_number)
	{
		this->right_sound.play();
		while (this->right_sound.getStatus() == sf::Sound::Playing)
		{
			std::cout << "DADA" << std::endl;
		}
		board[turned_sprite1_i][turned_sprite1_j].is_matched = 1;
		board[turned_sprite2_i][turned_sprite2_j].is_matched = 1;
		this->points += ceil(perfect_match_points / (board[turned_sprite1_i][turned_sprite1_j].number_of_turns + board[turned_sprite2_i][turned_sprite2_j].number_of_turns));
		std::cout << this->points << std::endl;
		return;
	}
	//TO ADD: daca nu sunt matched vreau un sound si un sprite cu un X si fundal transparent care sa apara
	/*for (int i = 0; i < 1200; i++) //asta e o solutie temporara pentru ca apare o pb - daca dau render o sg data asta se intampla la un frame si 
		this->Render();*/    //e prea rapid pentru ochiul uman si pentru joc (ca sa retii tile- urile pt ca pana la urma e memory game)
	
	//alternativ mai buna
	sf::sleep(sf::seconds(1));
	
	board[turned_sprite1_i][turned_sprite1_j].sprite.setTexture(board[turned_sprite1_i][turned_sprite1_j].texture_unturned);
	board[turned_sprite2_i][turned_sprite2_j].sprite.setTexture(board[turned_sprite2_i][turned_sprite2_j].texture_unturned);
}

const bool Game::Running() const
{
	return this->window->isOpen(); //cat timp mai avem jocul deschis
}

void Game::PollEvents() //cum poate interactiona playerul cu fereastra jocului
{
	while (this->window->pollEvent(this->sfml_event))
	{
		switch (this->sfml_event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfml_event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (this->sfml_event.mouseButton.button == sf::Mouse::Left)
			{
				bool searching = false;
				sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
				for (int i = 0; i < board_size && !searching; i++)
					for (int j = 0; j < board_size && !searching; j++)
						if (!board[i][j].is_matched && board[i][j].sprite.getGlobalBounds().contains(mouse_position))
						{
							//crestem contorul pt de cate ori s-a intors tile-ul
							board[i][j].number_of_turns++;
							searching = true; //am gasit acel sprite pe care am dat click si actionam doar daca e cu textura1
							if (board[i][j].sprite.getTexture() == &board[i][j].hover_texture) //nu se intampla nimic daca dam click pe un sprite care contine textura2 pt ca e deja intors sau matched
							{
								//std::cout << "DA" << std::endl;
								board[i][j].sprite.setTexture(board[i][j].texture_turned);
								num_clicks++; //la 2 clickuri inseamna ca am intors doua sprite-uri
								std::cout << num_clicks << std::endl;
								if (num_clicks == 1)
								{
									turned_sprite1_i = i;
									turned_sprite1_j = j;
								}
								else
								{
									turned_sprite2_i = i;
									turned_sprite2_j = j;
								}

							}
						}
			}
		case::sf::Event::MouseMoved:
			sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
			for (int i = 0; i < board_size; i++)
				for (int j = 0; j < board_size; j++)
					if (board[i][j].sprite.getGlobalBounds().contains(mouse_position))
					{
						if (board[i][j].sprite.getTexture() == &board[i][j].texture_unturned)
							board[i][j].sprite.setTexture(board[i][j].hover_texture);
					}
					else if (board[i][j].sprite.getTexture() == &board[i][j].hover_texture)
						board[i][j].sprite.setTexture(board[i][j].texture_unturned);
		}
	}
}

void Game::DrawBackground()
{
	this->window->draw(background_image.sprite);
}

void Game::DrawBoard()
{
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			this->window->draw(board[i][j].sprite);
		}
	}
}

void Game::Update()
{
	if (num_clicks == 2) { CheckMatch(); num_clicks = 0; }
	else this->PollEvents();
}

void Game::Render()
{
	this->window->clear(sf::Color(245, 245, 220));

	//RENDER LUCRURI
	this->DrawBackground();

	this->DrawBoard();

	this->window->display();

}


//DESTRUCTOR
Game::~Game()
{
	delete this->window;
}
