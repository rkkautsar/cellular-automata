#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

const int 	width	=   300,
			height	=	300,
			UPDATE_TIME = 125;

int main()
{
	srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(width*2, height*2,16), "Cellular Automata");

    sf::Image img;
    img.create(width*2,height*2,sf::Color::White);
    std::vector<std::vector<bool> > now,next;
    now.assign(height,std::vector<bool>(width,false));
    
    for(int i=0;i<height;++i)
    	for(int j=0;j<width;++j){
    		if(rand()%10==0){
    			now[i][j]=true;
    			img.setPixel(j*2,i*2,sf::Color::Black);
    			img.setPixel(j*2,i*2+1,sf::Color::Black);
    			img.setPixel(j*2+1,i*2,sf::Color::Black);
    			img.setPixel(j*2+1,i*2+1,sf::Color::Black);
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
        	for(int i=0;i<height;++i)
		    	for(int j=0;j<width;++j){

		    		count=0;
		    		if(i>0)						count+=now[i-1][j];
		    		if(i<height-1)				count+=now[i+1][j];
		    		if(j>0)						count+=now[i][j-1];
		    		if(j<width-1)				count+=now[i][j+1];
		    		if(i>0 && j>0)				count+=now[i-1][j-1];
		    		if(i>0 && j<width-1)		count+=now[i-1][j+1];
		    		if(i<height-1 && j>0)		count+=now[i+1][j-1];
		    		if(i<height-1 && j<width-1)	count+=now[i+1][j+1];
		    		
		    		if(now[i][j] && count>=2 && count<=3){
		    			img.setPixel(j*2,i*2,sf::Color::Black);
		    			img.setPixel(j*2,i*2+1,sf::Color::Black);
		    			img.setPixel(j*2+1,i*2,sf::Color::Black);
		    			img.setPixel(j*2+1,i*2+1,sf::Color::Black);
		    			next[i][j]=true;
		    		} else if(!now[i][j] && count==3){
		    			img.setPixel(j*2,i*2,sf::Color::Black);
		    			img.setPixel(j*2,i*2+1,sf::Color::Black);
		    			img.setPixel(j*2+1,i*2,sf::Color::Black);
		    			img.setPixel(j*2+1,i*2+1,sf::Color::Black);
		    			next[i][j]=true;
		    		}
		    		else{
		    			img.setPixel(j*2,i*2,sf::Color::White);
		    			img.setPixel(j*2,i*2+1,sf::Color::White);
		    			img.setPixel(j*2+1,i*2,sf::Color::White);
		    			img.setPixel(j*2+1,i*2+1,sf::Color::White);
		    			next[i][j]=false;
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