#include "Game.h"
#include <cmath>
//TO DO
//SA SCRIE NUMELE TARII
//SA AIBA OPTIUNEA DE HINT
//sa am grija daca are 0 puncte ca nu poate cumpara hinturi
//SA SE AFISEZE SCORUL
//DE ADAUGAT IN CAZUL IN CARE NU FACE MATCH PLAYERUL, UN SPRITE CU X ROSU CU FUNDAL TRANSPARENT PESTE CEL DEJA DESENAT
//si cu bifa cand facem matchul

std::vector <std::string> all_countries = { "Afghanistan",
"Albania",
"Algeria",
"Andorra",
"Angola",
"Antigua and Barbuda",
"Argentina",
"Armenia",
"Australia",
"Austria",
"Azerbaijan",
"Bahamas",
"Bahrain",
"Bangladesh",
"Barbados",
"Belarus",
"Belgium",
"Belize",
"Benin",
"Bhutan",
"Bolivia",
"Bosnia and Herzegovina",
"Botswana",
"Brazil",
"Brunei Darussalam",
"Bulgaria",
"Burkina Faso",
"Burundi",
"Cabo Verde",
"Cambodia",
"Cameroon",
"Canada",
"Central African Republic",
"Chad",
"Chile",
"China",
"Colombia",
"Comoros",
"Congo",
"Costa Rica",
"Ivory Coast",
"Croatia",
"Cuba",
"Cyprus",
"Czech Republic",
"North Korea",
"Congo",
"Denmark",
"Djibouti",
"Dominica",
"Dominican Republic",
"Ecuador",
"Egypt",
"El Salvador",
"Equatorial Guinea",
"Eritrea",
"Estonia",
"Eswatini",
"Ethiopia",
"Fiji",
"Finland",
"France",
"Gabon",
"Gambia",
"Georgia",
"Germany",
"Ghana",
"Greece",
"Grenada",
"Guatemala",
"Guinea",
"Guinea-Bissau",
"Guyana",
"Haiti",
"Honduras",
"Hungary",
"Iceland",
"India",
"Indonesia",
"Iran",
"Iraq",
"Ireland",
"Israel",
"Italy",
"Jamaica",
"Japan",
"Jordan",
"Kazakhstan",
"Kenya",
"Kiribati",
"Kuwait",
"Kyrgyzstan",
"Lao",
"Latvia",
"Lebanon",
"Lesotho",
"Liberia",
"Libya",
"Liechtenstein",
"Lithuania",
"Luxembourg",
"Madagascar",
"Malawi",
"Malaysia",
"Maldives",
"Mali",
"Malta",
"Marshall Islands",
"Mauritania",
"Mauritius",
"Mexico",
"Micronesia",
"Monaco",
"Mongolia",
"Montenegro",
"Morocco",
"Mozambique",
"Myanmar",
"Namibia",
"Nauru",
"Nepal",
"Netherlands",
"New Zealand",
"Nicaragua",
"Niger",
"Nigeria",
"North Macedonia",
"Norway",
"Oman",
"Pakistan",
"Palau",
"Panama",
"Papua New Guinea",
"Paraguay",
"Peru",
"Philippines",
"Poland",
"Portugal",
"Qatar",
"South Korea",
"Republic of Moldova",
"Romania",
"Russian Federation",
"Rwanda",
"Saint Kitts and Nevis",
"Saint Lucia",
"Saint Vincent and the Grenadines",
"Samoa",
"San Marino",
"Sao Tome and Principe",
"Saudi Arabia",
"Senegal",
"Serbia",
"Seychelles",
"Sierra Leone",
"Singapore",
"Slovakia",
"Slovenia",
"Solomon Islands",
"Somalia",
"South Africa",
"South Sudan",
"Spain",
"Sri Lanka",
"Sudan",
"Suriname",
"Sweden",
"Switzerland",
"Syrian Arab Republic",
"Tajikistan",
"Thailand",
"Timor-Leste",
"Togo",
"Tonga",
"Trinidad and Tobago",
"Tunisia",
"Turkey",
"Turkmenistan",
"Tuvalu",
"Uganda",
"Ukraine",
"United Arab Emirates",
"United Kingdom",
"United Republic of Tanzania",
"United States of America",
"Uruguay",
"Uzbekistan",
"Vanuatu",
"Venezuela",
"Viet Nam",
"Yemen",
"Zambia",
"Zimbabwe",
"Holy See",
"State of Palestine"
};

const int perfect_match_points = 1000;
const int cell_size = 100;

int turned_sprite1_i, turned_sprite1_j, turned_sprite2_i, turned_sprite2_j;
int num_clicks = 0;
bool set_numbers[200]; //un vector caracteristic in care tinem minte daca tilex unde x este un nr de la 1-195 (tarile lumii) a fost pusa deja in board sau nu

int match1, match2; //sa tin evidenta perechilor mathc-uite, ma ajuta si sa stiu cee variante scriu si cand
int guessed;

bool ok; //sa stiu daca maii am voie sa dau click pe board sau nu, daca nu inseamnca ca s a facut un meci si am voie sa dau click doar pe text si pe butoane

std::vector <int> put_options;

/*void Game::InitialiseSounds()
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
}*/

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

void Game::InitialiseButtons()
{
	if (!check_button.texture_unturned.loadFromFile("CHECK_GREEN.png")) {
		std::cout << "Nu s-a incarcat tile" << std::endl; // Error loading texture
	}
	check_button.sprite.setTexture(check_button.texture_unturned);
	check_button.sprite.setPosition(1060, 530);

	if (!pass_button.texture_unturned.loadFromFile("PASS_RED.png")) {
		std::cout << "Nu s-a incarcat tile" << std::endl; // Error loading texture
	}
	pass_button.sprite.setTexture(pass_button.texture_unturned);
	pass_button.sprite.setPosition(750, 530);

	if (!hint_button.texture_unturned.loadFromFile("HINT_YELLOW.png")) {
		std::cout << "Nu s-a incarcat tile" << std::endl; // Error loading texture
	}
	hint_button.sprite.setTexture(hint_button.texture_unturned);
	hint_button.sprite.setPosition(905, 530);
	
	if (!score.texture_unturned.loadFromFile("SCORE.png")) {
		std::cout << "Nu s-a incarcat score" << std::endl; // Error loading texture
	}
	score.sprite.setTexture(score.texture_unturned);
	score.sprite.setPosition(750, 50);
}

void Game::InitialiseText()
{
	if (!font.loadFromFile("NerkoOne-Regular.ttf"))
	{
		std::cout << "Nu s-a incarcat fontul pentru scor!\n";
	}
	this->text.setFont(font);
	this->text.setString("0");
	this->text.setCharacterSize(60);
	this->text.setFillColor(sf::Color::Black);
	this->text.setPosition(1080, 80);
}
//CONSTRUCTORI



Game::Game()
{ 
	//facem un random seed pentru alegerea tarilor care vor aparea in joc
	srand(static_cast<unsigned>(time(0)));
	this->DescribeRules();
	this->InitialiseButtons();
	//this->InitialiseSounds();
	this->InitialiseVariables();
	this->InitialiseWindow();
	this->InitialiseText();
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
				number = rand() % 59;
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
				board[i][j].country_name = all_countries[number];
				board[i2][j2].country_name = all_countries[number];
			}
	}
}

void Game::DescribeRules()
{
	//trebuie sa fac un ecran care explica regulile la inceputul jocului si sa adaug un sprite pe care daca apesi sa apara si in timpul jocului
	//momentan las asa pentru intelegere
	std::cout << "REGULI JOC" << std::endl;
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
		/*this->right_sound.play();
		while (this->right_sound.getStatus() == sf::Sound::Playing)
		{
			std::cout << "DADA" << std::endl;
		}*/
		board[turned_sprite1_i][turned_sprite1_j].is_matched = 1;
		board[turned_sprite2_i][turned_sprite2_j].is_matched = 1;
		this->points += ceil(perfect_match_points / (board[turned_sprite1_i][turned_sprite1_j].number_of_turns + board[turned_sprite2_i][turned_sprite2_j].number_of_turns));
		std::cout << this->points << std::endl;
		match1++;
		guessed = board[turned_sprite1_i][turned_sprite1_j].country_number;
		return;
	}
	//TO ADD: daca nu sunt matched vreau un sound si un sprite cu un X si fundal transparent care sa apara
	/*for (int i = 0; i < 1200; i++) //asta e o solutie temporara pentru ca apare o pb - daca dau render o sg data asta se intampla la un frame si 
		this->Render();*/    //e prea rapid pentru ochiul uman si pentru joc (ca sa retii tile- urile pt ca pana la urma e memory game)
	
	//alternativa mai buna
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
				if(!ok)
				{
					bool searching = false;
					sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
					//std::cout << mouse_position.x << " " << mouse_position.y << std::endl;
					for (int i = 0; i < board_size && !searching; i++)
						for (int j = 0; j < board_size && !searching; j++)
							if (!board[i][j].is_matched && board[i][j].sprite.getGlobalBounds().contains(mouse_position))
							{
								//crestem contorul pt de cate ori s-a intors tile-ul
								board[i][j].number_of_turns++;
								searching = true; //am gasit acel sprite pe care am dat click si actionam doar daca e cu textura1
								if (board[i][j].sprite.getTexture() == &board[i][j].hover_texture) //nu se intampla nimic daca dam click pe un sprite care contine textura2 pt ca e deja intors sau matched
								{
									//std::cout << board[i][j].country_name << std::endl;
									board[i][j].sprite.setTexture(board[i][j].texture_turned);
									num_clicks++; //la 2 clickuri inseamna ca am intors doua sprite-uri
									//std::cout << num_clicks << std::endl;
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
				else
				{
					sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
					if (pass_button.sprite.getGlobalBounds().contains(mouse_position))
					{
						ok = 0;
						put_options.clear();
						guessed = -1;
					}
					else if (hint_button.sprite.getGlobalBounds().contains(mouse_position))
					{
						points -= 250;

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

void Game::DrawButtons()
{
	//std::cout << "BUTON VERDE" << std::endl;
	this->window->draw(pass_button.sprite);
	this->window->draw(hint_button.sprite);
	this->window->draw(check_button.sprite);
	this->window->draw(score.sprite);
}

void Game::DrawBoard()
{
	//std::cout << "BOARD" << std::endl;
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			this->window->draw(board[i][j].sprite);
		}
	}
}

void Game::DrawText()
{
	std::string text_for_score = "";
	int points_copy = points;
	while (points_copy != 0)
	{
		char c = points_copy % 10 + 48;
		if (text_for_score == "")
			text_for_score.push_back(c);
		else text_for_score.insert(0, 1, c);
		points_copy /= 10;
	}
	this->text.setString(text_for_score);
	this->window->draw(text);
}

void Game::DrawOptions()
{

	text2.setFont(font);
	text2.setCharacterSize(60);
	text2.setFillColor(sf::Color::Black);
	int begin1 = 750, begin2 = 200;

	if (put_options.size() == 0 && guessed > 0)
	{
		put_options.push_back(guessed);
		int correct = rand() % 4;
		

		for (int i = 0; i < 4; i++)
		{
			text2.setPosition(begin1, begin2);
			begin2 += 70;
			if (i == correct)
				text2.setString(all_countries[guessed]);
			else
			{
				int possible_option = rand() % 59;
				bool found = 1;
				while (found)
				{
					found = 0;
					for (int i = 0; i < put_options.size(); i++)
						if (put_options[i] == possible_option)
						{
							found = 1; possible_option = rand() % 59; break;
						}
				}
				put_options.push_back(possible_option);
				text2.setString(all_countries[possible_option]);
			}

			this->window->draw(text2);

			/*for (int i = 0; i < put_options.size(); i++)
				std::cout << put_options[i] << " ";
			std::cout << "\n";*/
		}
	}
	else
	{
		for (int i = 0; i < put_options.size(); i++)
		{
			text2.setPosition(begin1, begin2);
			begin2 += 70;
			text2.setString(all_countries[put_options[i]]);
			this->window->draw(text2);
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
	//RENDER LUCRURI

	this->window->clear();

	this->DrawBackground();

	this->DrawBoard();

	this->DrawText();

	this->DrawButtons();

	if (match1 != match2)
	{
		match2++; ok = 1; put_options.clear();
	}

	if(match1 >= 1) this->DrawOptions();

	this->window->display();

}


//DESTRUCTOR
Game::~Game()
{
	delete this->window;
}


