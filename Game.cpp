#include "Game.h"

//TO DO
//SA IMPLEMENTEZ O FUNCTIONALITATE CARE DA PUNCTE PROPORTIONAL CU DE CATE ORI INCEARCA PLAYERUL
//SA FACA MATCH-UL
//SA SCRIE NUMELE TARII
//SA AIBA OPTIUNEA DE HINT
//OPTIUNEA DE QUIT DACA NU STIE O TARA PT A NU PIERDE PUNCTE
//SA SE AFISEZE SCORUL
//DE ADAUGAT IN CAZUL IN CARE NU FACE MATCH PLAYERUL, UN SPRITE CU X ROSU CU FUNDAL TRANSPARENT PESTE CEL DEJA DESENAT
//si cu bifa cand facem matchul


const int cell_size = 100;

int turned_sprite1_i, turned_sprite1_j, turned_sprite2_i, turned_sprite2_j;
int num_clicks = 0;
bool set_numbers[200]; //un vector caracteristic in care tinemi minte daca tilex unde x este un nr de la 1-195 (tarile lumii) a fost pusa deja in board sau nu

void Game::InitialiseVariables()
{
	this->end_game = false;
}

void Game::InitialiseWindow()
{
	this->video_mode = sf::VideoMode(1280, 720);
	this->window = new sf::RenderWindow(this->video_mode, "Learn the countries", sf::Style::Close | sf::Style::Titlebar);
}

void Game::InitialiseBackground()
{
	if (!background_image.texture1.loadFromFile("background_image.png"))
	{
		std::cout << "Nu s-a incarcat textura pentru background" << std::endl;
	}
	background_image.sprite.setTexture(background_image.texture1);
}

//CONSTRUCTORI
Game::Game()
{
	srand(static_cast<unsigned>(time(0)));
	this->InitialiseVariables();
	this->InitialiseWindow();
	this->InitialiseBackground();
	//this->InitialiseTexture2();
	this->SetUpBoard();
}


//FUNCTIONS


//in aceasta functie voi initializa textura doi a fiecarei piese din board cu o anumita tara
//trebuie sa am grija ca tara sa nu se repete
//trebuie sa am grija sa pun tara de doua ori si sa fie pe pozitii diferite din board

void Game::InitialiseTexture2() //nu e testata inca
{
	int number, i2, j2;
	char current_tile_path[60];
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
			if (!board[i][j].is_set)
			{
				
				//generam un numar corespunzator unei tari
				number = rand() % 195;
				while (set_numbers[number]) number = rand() % 195;
				//am setat tara ca fiind pusa in joc
				set_numbers[number] = 1;
				board[i][j].is_set = 1; //punem inainte pt a nu pune cumva pe ac poz
				//cautam un alt sprite pt i,j pt a putea avea doua sprite-uri la fel pt match
				i2 = rand() % 36;
				j2 = rand() % 36;
				while (board[i2][j2].is_set)
				{
					i2 = rand() % 36;
					j2 = rand() % 36;
				}
				//incarcam textura2 cu tara respectiva in cele doua sprite-uri
				sprintf_s(current_tile_path, "countries/tile%03d.png", number);
				if (!board[i][j].texture2.loadFromFile(current_tile_path))
				{
					std::cout << "Nu s-a incarcat o textura de tip tara" << std::endl;
					break;
				}
				if (!board[i2][j2].texture2.loadFromFile(current_tile_path))
				{
					std::cout << "Nu s-a incarcat o textura de tip tara" << std::endl;
					break;
				}
				//am adaugat o tara si am setat doua sprite-uri din board
				board[i2][j2].is_set = 1;
			
				board[i][j].pair_i = i2;
				board[i][j].pair_j = j2;
				board[i2][j2].pair_i = i;
				board[i2][j2].pair_j = j;


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
			if (!board[i][j].texture1.loadFromFile(texture_path)) {
				std::cout << "Nu s-a incarcat tile" << std::endl; // Error loading texture
				break;
			}
			if (!board[i][j].texture2.loadFromFile("tile2.png"))
			{
				std::cout << "Nu s-a incarcat tile2" << std::endl;
				break;
			}
			board[i][j].sprite.setTexture(board[i][j].texture1);
			board[i][j].sprite.setPosition(50+ j * (cell_size + 5),50 + i * (cell_size + 5));
		}
	}
}

void Game::CheckMatch()
{
	if (board[turned_sprite1_i][turned_sprite1_j].pair_i == turned_sprite2_i &&
		board[turned_sprite1_i][turned_sprite1_j].pair_j == turned_sprite2_j)
	{
		board[turned_sprite1_i][turned_sprite1_j].is_matched = 1;
		board[turned_sprite2_i][turned_sprite2_j].is_matched = 1;
		return;
	}


}

const bool Game::Running() const
{
	return this->window->isOpen(); //cat timp mai avem jocul deschis
}

void Game::PollEvents()
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
				if (num_clicks == 2) //inseamna ca s-au intors doua spriteuri
				{
					//CheckMatch();
					//in checkmatch o sa verific daca sprite-urile sunt la fel si daca nu le schimb textura la cea intiala
					//daca sunt la fel trebuie sa fac cumva sa nu se mai poata intoarce la click si cred ca voi face cu un bool
					num_clicks = 0; //dupa ce am verif revenim la 0 si trebuie sa intoarcem 2 si trebuie sa am grija sa reinitializez structura cu poz sprite-urilor
				}
				else //pun else deoarece dupa ce am setat textura sprite-urilor in checkmatch trebuie sa am grija sa desenez tabla la un frame adica dupa update sa se apeleze render
				{
					bool searching = false;
					sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
					for (int i = 0; i < board_size && !searching; i++)
						for (int j = 0; j < board_size && !searching; j++)
							if (!board[i][j].is_matched && board[i][j].sprite.getGlobalBounds().contains(mouse_position))
							{
								searching = true; //am gasit acel sprite pe care am dat click si actionam doar daca e cu textura1
								if (board[i][j].sprite.getTexture() == &board[i][j].texture1) //nu se intampla nimic daca dam click pe un sprite care contine textura2 pt ca e deja intors sau matched
								{
									//std::cout << "DA" << std::endl;
									board[i][j].sprite.setTexture(board[i][j].texture2);
									num_clicks++; //la 2 clickuri inseamna ca am intors doua sprite-uri
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
			}
			
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
	this->PollEvents();
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