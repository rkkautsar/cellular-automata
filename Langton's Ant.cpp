#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

int dx[4]={1,0,-1,0},
    dy[4]={0,1,0,-1};

const int 	width	=   200,
			height	=	200,
			UPDATE_TIME = 1;

int main()
{
	srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(width, height,16), "Cellular Automata");

    sf::Image img;
    img.create(width,height,sf::Color::White);

    std::vector<std::vector<bool> > now;
    now.assign(width,std::vector<bool>(height,false));
    
    int x=width/2,y=height/2;
    int dir=TOP;

    sf::Texture texture;
    texture.loadFromImage(img);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) ||
            	(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) )
                window.close();
        }

        
        if(!now[x][y]){ //white
            if(dir==LEFT) dir=TOP;
            else ++dir;
            now[x][y]=!now[x][y];
            img.setPixel(x,y,sf::Color::Black);
        } else {
            if(dir==TOP) dir=LEFT;
            else --dir;
            now[x][y]=!now[x][y];
            img.setPixel(x,y,sf::Color::White);
        }
        if(x+dx[dir]>=0 && x+dx[dir]<width) x+=dx[dir];
        else x-=dx[dir];
        if(y+dy[dir]>=0 && y+dy[dir]<height) y+=dy[dir]; 
        else y-=dy[dir];    

        texture.update(img);
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}