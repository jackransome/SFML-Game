#include "Game.h"

#include <chrono>
#include <iostream>
#include <ctime>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

// Style guide:
// 
// Class names: ClassName
// 
// Method names: MethodName
// 
// Argument names: argumentName
// 
//// On stack variable name: stack_variable
// 
// Pointers: int *pPointer
//
// Source: https://users.ece.cmu.edu/~eno/coding/CppCodingStandard.html#names
//


int main()
{
    // sfml setup
    const float FPS = 60.0f;
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width * .75, sf::VideoMode::getDesktopMode().height * .75, 32), "SFML_ENGINE", sf::Style::Default);
    window.setFramerateLimit(FPS);
    
    window.setView(sf::View(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width*.75, sf::VideoMode::getDesktopMode().height * .75)));
    // Game setup
    Game game(&window);
    
    while (window.isOpen())
    {
        int start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        
        // Input
        game.HandleInput();

        // Logic
        game.Run();

        // Draw
        game.Draw();
        
        // sfml display window
        window.display();
        std::cout << "FPS: " << 1000.0f/(float)((int)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - start) << "\n";
    }
    game.finishAudio();

    return 0;
}