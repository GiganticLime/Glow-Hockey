#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
	//For rendering the game screen
	RenderWindow window(VideoMode(1280, 720), "Glow Hockey");
	window.setFramerateLimit(60);

	//Define button area
	FloatRect buttonArea(790, 193, 340, 80);
	FloatRect buttonAreaExit(790, 354, 340, 80);

	//For Soundfx
	Music startAudio;
	if (!startAudio.openFromFile("startAudioProper.WAV")) {
	}
	Music collision;
	if (!collision.openFromFile("paddleHit.WAV")) {
	}
	Music wallTouch;
	if (!wallTouch.openFromFile("wallTouch.WAV")) {
	}
	Music goalAudio;
	if (!goalAudio.openFromFile("goalAudio.WAV")) {
	}



	//Background Image
	Texture background;
	background.loadFromFile("backgroundd.jpg");
	Sprite backgroundS;
	backgroundS.setTexture(background);


	//Starting Screen Image
	Texture startScreen;
	startScreen.loadFromFile("startscreen.png");
	Sprite startingScreen;
	startingScreen.setTexture(startScreen);


	//Menu Image
	Texture menuT;
	menuT.loadFromFile("menu2.png");
	Sprite menu;
	menu.setTexture(menuT);

	//Score for player1
	int score_1 = 0;
	Font score_font;
	score_font.loadFromFile("neon.otf");
	Text score;
	score.setFont(score_font);
	score.setString(to_string(score_1));
	score.setCharacterSize(75);
	score.setPosition(400, 50);
	score.setFillColor(Color::Blue);


	//Score for player2
	int score_2 = 0;
	Text score2;
	score2.setFont(score_font);
	score2.setString(to_string(score_2));
	score2.setCharacterSize(75);
	score2.setPosition(800, 50);
	score2.setFillColor(Color::Red);

	//Red/Blue Win Text
	Text redWin;
	redWin.setFont(score_font);
	redWin.setString("Red Wins!");
	redWin.setCharacterSize(120);
	redWin.setFillColor(Color::Red);
	redWin.setPosition(640, 360);

	Text blueWin;
	blueWin.setFont(score_font);
	blueWin.setString("Blue Wins!");
	blueWin.setCharacterSize(120);
	blueWin.setFillColor(Color::Blue);
	blueWin.setPosition(640, 360);


	//Declaring Shapes 
	CircleShape circle;
	CircleShape paddle1;
	CircleShape paddle2;

	//Setting size and position of Circle
	Vector2f circlePosition(640, 360);
	Vector2f circlePositionAfterGoal1(440, 360);
	Vector2f circlePositionAfterGoal2(840, 360);
	circle.setPosition(circlePosition);
	circle.setRadius(25);
	circle.setOrigin(0, 0);
	circle.setFillColor(Color::White);
	circle.setOutlineThickness(10);
	circle.setOutlineColor(Color::Yellow);

	//Setting size and position of Paddle1
	Vector2f circlePosition1(60, 360);
	paddle1.setPosition(circlePosition1);
	paddle1.setRadius(20);
	paddle1.setFillColor(Color::Transparent);
	paddle1.setOutlineThickness(40);
	paddle1.setOutlineColor(Color::Blue);

	//Setting size and position of Paddle2
	Vector2f circlePosition2(1200, 360);
	paddle2.setPosition(circlePosition2);
	paddle2.setRadius(20);
	paddle2.setFillColor(Color::Transparent);
	paddle2.setOutlineThickness(40);
	paddle2.setOutlineColor(Color::Red);


	//setting speed for puck
	float xVelocity = 8;
	float yVelocity = 4;


	//Starting screen code
	bool gameStarted = false;
	bool gameMenu = false;

	//while loop to keep the game running
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		if (!gameStarted)
		{
			window.clear();
			window.draw(startingScreen);
			window.display();

			if (Keyboard::isKeyPressed(Keyboard::Space) || Mouse::isButtonPressed(Mouse::Left))
			{
				gameStarted = true;
			}
		}
		if (gameStarted)
		{
			if (!gameMenu)
			{
				window.clear();
				window.draw(menu);
				window.display();

				// Check for mouse click event
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::MouseButtonPressed) {
						if (event.mouseButton.button == sf::Mouse::Left) {
							sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
							if (buttonArea.contains(mousePosition.x, mousePosition.y)) {
								startAudio.play();
								gameMenu = true;
							}
							else  if (buttonAreaExit.contains(mousePosition.x, mousePosition.y))
							{
								window.close();
							}
							else
							{
								gameMenu = false;
							}
						}
					}
				}
			} 
			if (gameMenu)
			{
				//for movement of the puck
				circle.move(Vector2f(xVelocity, yVelocity));
				circlePosition = circle.getPosition();

				//movement for paddle 1
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					circlePosition1.y = circlePosition1.y - 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					circlePosition1.x = circlePosition1.x + 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					circlePosition1.y = circlePosition1.y + 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					circlePosition1.x = circlePosition1.x - 10;
				}
				paddle1.setPosition(circlePosition1);

				//movement for paddle 2
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					circlePosition2.y = circlePosition2.y - 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					circlePosition2.y = circlePosition2.y + 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					circlePosition2.x = circlePosition2.x - 10;
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					circlePosition2.x = circlePosition2.x + 10;
				}

				paddle2.setPosition(circlePosition2);


				// for collision with the edge of the screen & goaling system
				if (circlePosition.x < 40 || circlePosition.x > 1235)
				{
					if (circlePosition.x < 40 && circlePosition.y > 210 && circlePosition.y < 505)
					{
						score_2 = score_2 + 1;
						score2.setString(to_string(score_2));
						goalAudio.play();
						goalAudio.setPlayingOffset(Time::Zero);
						circlePosition1 = Vector2f(60, 360);
						circlePosition2 = Vector2f(1150, 360);
						circle.setPosition(circlePositionAfterGoal1);
						xVelocity = -xVelocity;
					}
					else if (circlePosition.x > 1235 && circlePosition.y > 210 && circlePosition.y < 505)
					{
						score_1 = score_1 + 1;
						score.setString(to_string(score_1));
						goalAudio.play();
						goalAudio.setPlayingOffset(Time::Zero);
						circlePosition1 = Vector2f(60, 360);
						circlePosition2 = Vector2f(1150, 360);
						circle.setPosition(circlePositionAfterGoal2);
						xVelocity = -xVelocity;
					}
					else
					{
						xVelocity = -xVelocity;
						wallTouch.play();
						wallTouch.setPlayingOffset(Time::Zero);
					}
					paddle1.setPosition(circlePosition1);
					paddle2.setPosition(circlePosition2);
				}
				if (circlePosition.y < 40 || circlePosition.y > 630)
				{
					yVelocity = -yVelocity;
					wallTouch.play();
					wallTouch.setPlayingOffset(Time::Zero);
				}

				// for collision with first paddle
				if (circle.getGlobalBounds().intersects(paddle1.getGlobalBounds()))
				{
					collision.play();
					collision.setPlayingOffset(Time::Zero);
					xVelocity = -xVelocity;
				}
				// for collision with second paddle
				if (circle.getGlobalBounds().intersects(paddle2.getGlobalBounds()))
				{
					collision.play();
					collision.setPlayingOffset(Time::Zero);
					xVelocity = -xVelocity;
				}

				//for displaying various shapes
				window.clear();
				window.draw(backgroundS);
				window.draw(circle);
				window.draw(paddle1);
				window.draw(paddle2);
				window.draw(score);
				window.draw(score2);
				if (score_1 == 5)
				{
					window.draw(blueWin);
					xVelocity = 0;
					yVelocity = 0;
				}
				else if (score_2 == 5)
				{
					window.draw(redWin);
					xVelocity = 0;
					yVelocity = 0;
				}
				window.display();
			}
		}
	}
}