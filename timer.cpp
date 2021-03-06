#include <string>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include <libnotify/notify.h>

using namespace sf;
using namespace std;

int main(){
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    

    RenderWindow window(VideoMode(700, 300), "Timer",Style::Resize, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);
    window.setPosition(Vector2i(1000, 50));

    Font font;
    font.loadFromFile("Roboto.ttf");
    Color background(40, 40, 40);
    Color foreground(215, 153, 33);

    Clock clock;
    int offset_sec = 0;

    int running = 1;

    Text label_time;
    label_time.setFont(font);
    label_time.setFillColor(foreground);
    label_time.setCharacterSize(200);
    label_time.setPosition(50, 30);

    while(window.isOpen()){
        int secs = offset_sec + int(clock.getElapsedTime().asSeconds());
        
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return){
                    running++;
                    running %= 2;

                    if(!running){
                        offset_sec = secs;
                    }
                    else{
                        clock.restart();
                        secs = offset_sec + int(clock.getElapsedTime().asSeconds());
                    }
                }
            }
        }	

        window.clear(background);

        if(running){
            if(secs > 5){
                clock.restart();
                offset_sec = 0;
                notify_init("Timer");
                NotifyNotification* n = notify_notification_new ("Timer", "Session finished", 0);
                notify_notification_set_timeout(n, 0);
                notify_notification_show(n, 0);
                continue;
            }

            int mins = secs / 60;
            secs %= 60;

            string l_secs = to_string(secs);
            string l_mins = to_string(mins);

            if(l_secs.size() == 1)
                l_secs = "0" + l_secs;
            if(l_mins.size() == 1)
                l_mins = "0" + l_mins;

            label_time.setString(l_mins + ":" + l_secs);
        }

        window.draw(label_time);
        window.display();
    }
    
    return 0;
}
