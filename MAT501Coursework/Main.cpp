//
// Main.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include "UIManager.h"

int main()
{
	// Create window
	sf::RenderWindow window(
						sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
						"Racing Car Controller", 
						sf::Style::Titlebar | sf::Style::Close);	// Disable resize
	window.setFramerateLimit(60);

	// Initialize the AI Controller
	AIController* pAiController = new AIController();

	// Configure UI
	UIManager* pUIManager = new UIManager(window, pAiController);
	if (!pUIManager->Initialize())
	{
		return EXIT_FAILURE;
	}

	// Initialize the time
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;

	// Run the main loop until the window is closed
	while (window.isOpen())
	{
		// Handle window events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			pUIManager->HandleEvent(event);
		}

		// Update
		if (!pUIManager->IsPaused())
		{
			elapsedTime += clock.restart();
			pUIManager->HandleKeyboardInput();
			pUIManager->Update(elapsedTime); // AI techniques performed here
		}

		// Draw
		window.clear(COLOR_BACKGROUND);
		pUIManager->Draw();
		window.display();
	}

	SAFE_DELETE(pUIManager);
	SAFE_DELETE(pAiController);

	return EXIT_SUCCESS;
}
