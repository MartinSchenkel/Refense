#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "KeyBindings.h"
#include "Timer.h"

const std::string FRAG_SHADER = 
"#version 130\n\
\
uniform sampler2D texture; \
uniform float blur_radius; \
\
void main() \
{ \
	vec2 offx = vec2(blur_radius, 0.0);\
	vec2 offy = vec2(0.0, blur_radius);\
\
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)      * 30.0 + \
		texture2D(texture, gl_TexCoord[0].xy - offx)        * 5.0 + \
		texture2D(texture, gl_TexCoord[0].xy + offx)        * 5.0 + \
		texture2D(texture, gl_TexCoord[0].xy - offy)        * 5.0 + \
		texture2D(texture, gl_TexCoord[0].xy + offy)        * 5.0 + \
		texture2D(texture, gl_TexCoord[0].xy - offx - offy) * 1.0 + \
		texture2D(texture, gl_TexCoord[0].xy - offx + offy) * 1.0 + \
		texture2D(texture, gl_TexCoord[0].xy + offx - offy) * 1.0 + \
		texture2D(texture, gl_TexCoord[0].xy + offx + offy) * 1.0; \
 \
	gl_FragColor = gl_Color * (pixel / 30.0); \
} \
";

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Refense");
	window.setFramerateLimit(144);

	window.setKeyRepeatEnabled(true);

	Player p;

	KeyBindings *k = k->getInstance();
	Timer *t = t->getInstance();
	t->Reset();

	float deltaTime = 0.0f;


	sf::RenderTexture* rt = new sf::RenderTexture();
	rt->create(1280, 720);

	sf::Shader blurShader;
	blurShader.loadFromMemory(FRAG_SHADER, sf::Shader::Fragment);
	//set up the 'texture' variable in the shader
	blurShader.setUniform("texture", sf::Shader::CurrentTexture);
	blurShader.setUniform("blur_radius", 0.003f);

	while (window.isOpen())
	{

		deltaTime = t->getTimePassedInSec();
		//std::cout << std::floor(1/deltaTime) << std::endl;
		t->Reset();

		//handle events
		sf::Event event;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}


		sf::Vector2i moveDir;
		//Up
		if (sf::Keyboard::isKeyPressed(k->m_up))
		{
			moveDir.y = -1;
		}
		//Right
		if (sf::Keyboard::isKeyPressed(k->m_right))
		{
			moveDir.x = 1;
		}
		//Left
		if (sf::Keyboard::isKeyPressed(k->m_left))
		{
			moveDir.x = -1;
		}

		p.move(moveDir, deltaTime);

		//update GameLogic

		rt->clear();

		//draw
		p.drawTo(rt);
		
		rt->display();

		window.clear();

		sf::Sprite s(rt->getTexture());

		window.draw(s, &blurShader);

		window.display();
	}
}