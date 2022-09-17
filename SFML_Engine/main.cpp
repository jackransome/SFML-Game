#include "Game.h"

// Style guide:
// 
// Class names: ClassName
// 
// Method names: MethodName
// 
// Argument names: argumentName
// 
// On stack variable name: stack_variable
// 
// Pointers: int *pPointer
//
// Source: https://users.ece.cmu.edu/~eno/coding/CppCodingStandard.html#names
//

int main()
{
    // sfml setup
    const float FPS = 60.0f;
    sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "SFML_ENGINE");
    window.setFramerateLimit(FPS);

    // Game setup
    Game game(&window);
    
    while (window.isOpen())
    {
        // Input
        game.HandleInput();

        // Logic
        game.Run();

        // Draw
        game.Draw();
        
        // sfml display window
        window.display();
    }
    game.finishAudio();

    return 0;
}