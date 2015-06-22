#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cmath>

const int 	width	=   300,
			height	=	300,
			UPDATE_TIME = 125;
int rule1=0,rule2=0;

// Conway's Game of Life is 0b00001100=12 0b00001000=8

int main(int argc,char *argv[])
{
	srand(time(NULL));

    if(argc!=3){
        std::cout<<"This program must take two arguments, seed1 and seed2 (numbers between 0-512).\n";
        return 1;
    } else {
        std::stringstream ss;
        ss<<argv[1]<<' '<<argv[2];
        ss>>rule1;
        ss>>rule2;
    }

    sf::RenderWindow window(sf::VideoMode(width*2, height*2,16), "Cellular Automata");

    sf::Image img;
    img.create(width*2,height*2,sf::Color::White);

    std::vector<std::vector<bool> > now,next;
    now.assign(width,std::vector<bool>(height,false));
    
    for(int i=0;i<width;++i)
    	for(int j=0;j<height;++j){
    		if(rand()%10==0){
    			now[i][j]=true;
                img.setPixel(i*2,j*2,sf::Color::Black);
                img.setPixel(i*2+1,j*2,sf::Color::Black);
                img.setPixel(i*2,j*2+1,sf::Color::Black);
    			img.setPixel(i*2+1,j*2+1,sf::Color::Black);
    		}
    	}

    sf::Texture texture;
    texture.loadFromImage(img);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Clock clock;
    sf::Time elapsed=clock.getElapsedTime();
    int count;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed) ||
            	(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) )
                window.close();
        }

        elapsed=clock.getElapsedTime();
        if(elapsed.asMilliseconds()>=UPDATE_TIME){
        	clock.restart();
       		next=now;
        	for(int i=0;i<width;++i)
		    	for(int j=0;j<height;++j){

		    		count=0;
		    		if(i>0)						count+=now[i-1][j];
		    		if(i<width-1)				count+=now[i+1][j];
		    		if(j>0)						count+=now[i][j-1];
		    		if(j<height-1)				count+=now[i][j+1];
		    		if(i>0 && j>0)				count+=now[i-1][j-1];
		    		if(i>0 && j<height-1)		count+=now[i-1][j+1];
		    		if(i<width-1 && j>0)		count+=now[i+1][j-1];
		    		if(i<width-1 && j<height-1)	count+=now[i+1][j+1];
		    		
		    		if(now[i][j]) next[i][j]=rule1&(1<<count);
                    else next[i][j]=rule2&(1<<count);

                    if(next[i][j]){
                        img.setPixel(i*2,j*2,sf::Color::Black);
                        img.setPixel(i*2+1,j*2,sf::Color::Black);
                        img.setPixel(i*2,j*2+1,sf::Color::Black);
                        img.setPixel(i*2+1,j*2+1,sf::Color::Black);
                    }
                    else {
                        img.setPixel(i*2,j*2,sf::Color::White);
                        img.setPixel(i*2+1,j*2,sf::Color::White);
                        img.setPixel(i*2,j*2+1,sf::Color::White);
                        img.setPixel(i*2+1,j*2+1,sf::Color::White);
                    }
		   		}
		   	now=next;
        }
        texture.update(img);
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}