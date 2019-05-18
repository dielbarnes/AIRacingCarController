//
// UIManager.h
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#ifndef UIMANAGER_H
#define UIMANAGER_H

// Use TGUI library for SFML
// https://tgui.eu
// https://www.sfml-dev.org
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <math.h>
#include "AIController.h"
#include "RacingLine.h"
#include "Car.h"
#include "Utils.h"

#define RESOURCE_PATH_THEME "Resources/Theme.txt"
#define RESOURCE_PATH_FONT "Resources/DejaVuSans.ttf"
#define RESOURCE_PATH_CAR1 "Resources/car.png"
#define RESOURCE_PATH_CAR2 "Resources/car2.png"
#define RESOURCE_PATH_PAUSED "Resources/paused.png"

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 813
#define WINDOW_PADDING 20
#define WINDOW_ITEM_SPACING 10
#define TEXTFIELD_WIDTH 70
#define TEXTFIELD_HEIGHT 25
#define TEXT_SIZE 15
#define BUTTON_HEIGHT TEXTFIELD_HEIGHT
#define CANVAS_PADDING 10

#define COLOR_BACKGROUND sf::Color(15, 15, 30, 255)
#define COLOR_DARK_BACKGROUND sf::Color(7, 7, 15, 255)
#define COLOR_LIGHT_GRAY sf::Color(150, 150, 150, 255)
#define COLOR_RED sf::Color(255, 23, 68, 255)
#define COLOR_CYAN sf::Color(66, 255, 255, 255)

#define LOG_INTERVAL 100 // Milliseconds

#define MIN_LINE_RATEOFCHANGE -9.0f
#define MAX_LINE_RATEOFCHANGE 9.0f
#define MIN_CAR_STEERINGFACTOR -12.0f
#define MAX_CAR_STEERINGFACTOR 12.0f

class UIManager
{
public:
	UIManager(sf::RenderWindow &rWindow, AIController* &rAiController);
	~UIManager();

	bool Initialize();
	void HandleEvent(sf::Event event);
	bool IsPaused();
	void HandleKeyboardInput();
	void Update(sf::Time elapsedTime);
	void Draw();

private:
	AIController* m_pAiController;
	tgui::Gui* m_pGui;
	tgui::EditBox::Ptr m_spDistanceTextField;
	tgui::EditBox::Ptr m_spRateOfChangeTextField;
	bool m_bDidApplyRateOfChange;
	float m_fRateOfChangeApplied;
	tgui::Button::Ptr m_spApplyButton;
	tgui::Button::Ptr m_spPauseButton;
	bool m_bIsPaused;
	tgui::Button::Ptr m_spRestartButton;
	sf::Font m_font;
	tgui::Canvas::Ptr m_spCanvases[MODULE_COUNT];
	sf::Text m_moduleNames[MODULE_COUNT];
	RacingLine* m_pRacingLines[MODULE_COUNT];
	Car* m_pCars[MODULE_COUNT];
	float m_fMinX;
	float m_fMaxX;
	sf::Texture m_pausedTexture;
	sf::Sprite m_pausedSprites[MODULE_COUNT];
	tgui::Button::Ptr m_spClearButton;
	tgui::ChatBox::Ptr m_spLogTextBoxes[MODULE_COUNT];
	sf::Time m_lastLoggedTime;

	bool InputsAreValid();
	void PrintLog(int iModuleIndex);
};

#endif
