// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	//Text and Font
	Text text;
	Font font;
	if (!font.loadFromFile("LoveDays-2v7Oe.ttf"))
	{
		throw("Font failed to load");
	}
	text.setFont(font);
	text.setCharacterSize(16);
	text.setColor(Color::Blue);
	text.setString("1. Left click 3 points to outline a triangle\n\n2. Left click one more time in the encompassed outline");

	

	//Declarations
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	//double randomVertex = rand() % 3;                 //Doesn't work?
	//double randomPrev = randomVertex;		    //Doesn't work?   See line 95

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < 3)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
				points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
		double count = points.size() - 1;
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    
		    double count = points.size() - 1;
		    //while (randomVertex == randomPrev)
		   // {
			 double randomVertex = rand() % 3;
		   // }
		  //  randomPrev = randomVertex;       //For some reason the fractal doesn't work properly if I declare randomVertex and randomPrev stuff above
							// I thought I needed the previous vertex so that I could confirm no match between the last and current vertex
							// But it works perfectly like this? Didn't find out why yet but just glad it works
			
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
		    double midpointX = (vertices.at(randomVertex).x + points.at(count).x) * 0.5;
		    double midpointY = (vertices.at(randomVertex).y + points.at(count).y) * 0.5;
		    points.push_back(Vector2f(midpointX, midpointY));
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(text);
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		for(int i = 0; i < points.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(points[i].x, points[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		window.display();
	}
}
