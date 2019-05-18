//
// UIManager.cpp
// Copyright © 2018 Diel Barnes. All rights reserved.
//

#include "UIManager.h"

#pragma region Init

UIManager::UIManager(sf::RenderWindow &rWindow, AIController* &rAiController)
{
	m_pGui = new tgui::Gui(rWindow);
	m_pAiController = rAiController;
	m_bDidApplyRateOfChange = false;
	m_fRateOfChangeApplied = 0.0f;
	m_bIsPaused = false;
	m_fMinX = 0.0f;
	m_fMaxX = 0.0f;
	m_lastLoggedTime = sf::Time::Zero;
}

UIManager::~UIManager()
{
	SAFE_DELETE(m_pGui);
}

bool UIManager::Initialize()
{
	try
	{
		// Load theme
		tgui::Theme theme{RESOURCE_PATH_THEME};

		// Add a label for the instructions
		auto label = tgui::Label::create();
		label->setRenderer(theme.getRenderer("Label"));
		label->setPosition(WINDOW_PADDING, WINDOW_PADDING + 3);
		label->setText("Press left/right arrow keys to move the line. Combine with numerical keys to change the rate of movement.");
		label->setTextSize(TEXT_SIZE);
		m_pGui->add(label);

		float fCanvasWidth = WINDOW_WIDTH * 0.7f;

		// Add a restart button
		float fRestartButtonWidth = 80.0f;
		m_spRestartButton = tgui::Button::create();
		m_spRestartButton->setRenderer(theme.getRenderer("Button"));
		m_spRestartButton->setPosition(WINDOW_WIDTH - WINDOW_PADDING - fRestartButtonWidth, WINDOW_PADDING);
		m_spRestartButton->setSize(fRestartButtonWidth, BUTTON_HEIGHT);
		m_spRestartButton->setText("Restart");
		m_spRestartButton->setTextSize(TEXT_SIZE);
		m_spRestartButton->connect("pressed", [&]()
		{
			m_spDistanceTextField->setText("");
			m_spRateOfChangeTextField->setText("");

			for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
			{
				float fCarPositionY = m_pCars[iModuleIndex]->GetSprite().getPosition().y;
				m_pCars[iModuleIndex]->GetSprite().setPosition(0.0f, fCarPositionY);
				float fLinePositionX = (m_spCanvases[0]->getSize().x - LINE_WIDTH) / 2;
				m_pRacingLines[iModuleIndex]->GetShape().setPosition(fLinePositionX, 0.0f);
				m_spLogTextBoxes[iModuleIndex]->removeAllLines();
			}

			m_lastLoggedTime = sf::Time::Zero;
		});
		m_pGui->add(m_spRestartButton);

		// Add UI elements for getting user input

		float fTopSpace = BUTTON_HEIGHT + (WINDOW_PADDING * 2);

		label = tgui::Label::create();
		label->setRenderer(theme.getRenderer("Label"));
		label->setPosition(WINDOW_PADDING, fTopSpace + 3);
		label->setText("Alternately, enter values manually.");
		label->setTextSize(TEXT_SIZE);
		m_pGui->add(label);

		m_spDistanceTextField = tgui::EditBox::create();
		m_spDistanceTextField->setRenderer(theme.getRenderer("EditBox"));
		m_spDistanceTextField->setPosition(label->getPosition().x + label->getSize().x + (WINDOW_ITEM_SPACING * 2), fTopSpace);
		m_spDistanceTextField->setSize(TEXTFIELD_WIDTH, TEXTFIELD_HEIGHT);
		m_spDistanceTextField->setDefaultText("0");
		m_spDistanceTextField->setTextSize(TEXT_SIZE);
		m_spDistanceTextField->setAlignment(tgui::EditBox::Alignment::Center);
		m_pGui->add(m_spDistanceTextField);

		label = tgui::Label::create();
		label->setRenderer(theme.getRenderer("Label"));
		label->setPosition(m_spDistanceTextField->getPosition().x + m_spDistanceTextField->getSize().x + WINDOW_ITEM_SPACING, fTopSpace + 3);
		label->setText("Distance");
		label->setTextSize(TEXT_SIZE);
		m_pGui->add(label);

		m_spRateOfChangeTextField = tgui::EditBox::create();
		m_spRateOfChangeTextField->setRenderer(theme.getRenderer("EditBox"));
		m_spRateOfChangeTextField->setPosition(label->getPosition().x + label->getSize().x + (WINDOW_ITEM_SPACING * 2), fTopSpace);
		m_spRateOfChangeTextField->setSize(TEXTFIELD_WIDTH, TEXTFIELD_HEIGHT);
		m_spRateOfChangeTextField->setDefaultText("0");
		m_spRateOfChangeTextField->setTextSize(TEXT_SIZE);
		m_spRateOfChangeTextField->setAlignment(tgui::EditBox::Alignment::Center);
		m_pGui->add(m_spRateOfChangeTextField);

		label = tgui::Label::create();
		label->setRenderer(theme.getRenderer("Label"));
		label->setPosition(m_spRateOfChangeTextField->getPosition().x + m_spRateOfChangeTextField->getSize().x + WINDOW_ITEM_SPACING, fTopSpace + 3);
		label->setText("Rate of Change of Distance");
		label->setTextSize(TEXT_SIZE);
		m_pGui->add(label);

		m_spApplyButton = tgui::Button::create();
		m_spApplyButton->setRenderer(theme.getRenderer("Button"));
		m_spApplyButton->setPosition(label->getPosition().x + label->getSize().x + (WINDOW_ITEM_SPACING * 3), fTopSpace);
		m_spApplyButton->setSize(70.0f, BUTTON_HEIGHT);
		m_spApplyButton->setText("Apply");
		m_spApplyButton->setTextSize(TEXT_SIZE);
		m_spApplyButton->connect("pressed", [&]()
		{
			if (InputsAreValid())
			{
				std::string strDistance = m_spDistanceTextField->getText();
				float fDistance = strDistance.empty() ? 0 : std::stof(strDistance);

				std::string strRateOfChangeOfDistance = m_spRateOfChangeTextField->getText();
				float fRateOfChangeOfDistance = strRateOfChangeOfDistance.empty() ? 0 : std::stof(strRateOfChangeOfDistance);

				m_bDidApplyRateOfChange = true;
				m_fRateOfChangeApplied = fRateOfChangeOfDistance;

				m_lastLoggedTime = sf::Time::Zero;

				for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
				{
					if (fDistance == 0)
					{
						m_pRacingLines[iModuleIndex]->GetShape().setPosition(m_pCars[iModuleIndex]->GetCenterX() - (LINE_WIDTH / 2), 0.0f);
					}
					else
					{
						float fCurrentDistance = m_pRacingLines[iModuleIndex]->GetCenterX() - m_pCars[iModuleIndex]->GetCenterX();
						float fDeltaX = fDistance - std::abs(fCurrentDistance);
						m_pRacingLines[iModuleIndex]->GetShape().move(fDeltaX, 0.0f);
					}

					m_pRacingLines[iModuleIndex]->SetRateOfChangeOfDistance(fRateOfChangeOfDistance);
				}
			}
		});
		m_pGui->add(m_spApplyButton);

		// Add a pause button
		float fPauseButtonWidth = 70.0f;
		m_spPauseButton = tgui::Button::create();
		m_spPauseButton->setRenderer(theme.getRenderer("Button"));
		m_spPauseButton->setPosition(m_spApplyButton->getPosition().x + m_spApplyButton->getSize().x + (WINDOW_ITEM_SPACING * 2), fTopSpace);
		m_spPauseButton->setSize(fPauseButtonWidth, BUTTON_HEIGHT);
		m_spPauseButton->setText("Pause");
		m_spPauseButton->setTextSize(TEXT_SIZE);
		m_spPauseButton->connect("pressed", [&]()
		{
			m_bIsPaused = !m_bIsPaused;
			if (m_bIsPaused)
			{
				m_spPauseButton->setText("Play");
			}
			else
			{
				m_spPauseButton->setText("Pause");
			}
		});
		m_pGui->add(m_spPauseButton);

		fTopSpace += BUTTON_HEIGHT + WINDOW_PADDING;
		float fCanvasHeight = (WINDOW_HEIGHT - fTopSpace - (WINDOW_PADDING * 2)) / 2;
		float fLinePositionX = (fCanvasWidth - LINE_WIDTH) / 2;
		float fCarWidth = 0.0f;
		float fTextBoxWidth = WINDOW_WIDTH - fCanvasWidth - (WINDOW_PADDING * 3);

		m_font.loadFromFile(RESOURCE_PATH_FONT);

		m_pausedTexture.loadFromFile(RESOURCE_PATH_PAUSED);

		// Create one UI element/game object for each AI module
		// Use the same mapping the AI Controller uses (i.e. ModuleIndex)
		for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
		{
			// Create a canvas where the game objects will be drawn
			m_spCanvases[iModuleIndex] = tgui::Canvas::create({ fCanvasWidth, fCanvasHeight});
			m_pGui->add(m_spCanvases[iModuleIndex]);

			// Add an indicator for the paused state
			m_pausedSprites[iModuleIndex].setTexture(m_pausedTexture);
			float fPausedWidth = (fCanvasWidth - m_pausedTexture.getSize().x) / 2;
			float fPausedHeight = (fCanvasHeight - m_pausedTexture.getSize().y) / 2;
			m_pausedSprites[iModuleIndex].setPosition((int)fPausedWidth, (int)fPausedHeight);

			sf::Texture carTexture;
			float fTextBoxPositionY;

			// Module-specific UI configurations here
			switch (iModuleIndex)
			{
			case ModuleIndex::FuzzyLogic:
				m_spCanvases[iModuleIndex]->setPosition(WINDOW_PADDING, fTopSpace);
				m_moduleNames[iModuleIndex].setString("Fuzzy Logic");
				m_moduleNames[iModuleIndex].setFillColor(COLOR_RED);
				carTexture.loadFromFile(RESOURCE_PATH_CAR1);
				fTextBoxPositionY = fTopSpace;
				break;

			case ModuleIndex::PathFollowing:
				m_spCanvases[iModuleIndex]->setPosition(WINDOW_PADDING, (int)(m_spCanvases[ModuleIndex::FuzzyLogic]->getPosition().y + m_spCanvases[ModuleIndex::FuzzyLogic]->getSize().y + WINDOW_PADDING));
				m_moduleNames[iModuleIndex].setString("Path Following");
				m_moduleNames[iModuleIndex].setFillColor(COLOR_CYAN);
				carTexture.loadFromFile(RESOURCE_PATH_CAR2);
				fTextBoxPositionY = m_spLogTextBoxes[ModuleIndex::FuzzyLogic]->getPosition().y + m_spLogTextBoxes[ModuleIndex::FuzzyLogic]->getSize().y + WINDOW_PADDING;
				break;
			}

			// Add a label for the module name
			m_moduleNames[iModuleIndex].setFont(m_font);
			m_moduleNames[iModuleIndex].setCharacterSize(TEXT_SIZE);
			m_moduleNames[iModuleIndex].setPosition(CANVAS_PADDING, CANVAS_PADDING);

			// Create a racing line
			m_pRacingLines[iModuleIndex] = new RacingLine(COLOR_LIGHT_GRAY, LINE_WIDTH, fCanvasHeight, fLinePositionX, 0, DEFAULT_VELOCITY);

			// Create a car
			fCarWidth = carTexture.getSize().x;
			unsigned int uiCarHeight = carTexture.getSize().y;
			float fCarPositionY = (fCanvasHeight - (float)uiCarHeight) / 2;
			m_pCars[iModuleIndex] = new Car(carTexture, 0.0f, fCarPositionY, DEFAULT_VELOCITY);

			// Create a text box for displaying logs
			float fTextBoxPositionX = fCanvasWidth + (WINDOW_PADDING * 2);
			m_spLogTextBoxes[iModuleIndex] = tgui::ChatBox::create();
			m_spLogTextBoxes[iModuleIndex]->setRenderer(theme.getRenderer("ChatBox"));
			m_spLogTextBoxes[iModuleIndex]->setPosition(fTextBoxPositionX, fTextBoxPositionY);
			m_spLogTextBoxes[iModuleIndex]->setSize(fTextBoxWidth, fCanvasHeight);
			m_spLogTextBoxes[iModuleIndex]->setTextSize(TEXT_SIZE);
			m_spLogTextBoxes[iModuleIndex]->setLineLimit(100);
			m_spLogTextBoxes[iModuleIndex]->setLinesStartFromTop();
			m_pGui->add(m_spLogTextBoxes[iModuleIndex]);
		}

		// Add a label for the logs
		label = tgui::Label::create();
		label->setRenderer(theme.getRenderer("Label"));
		label->setPosition(m_spLogTextBoxes[0]->getPosition().x, m_spApplyButton->getPosition().y + 3);
		label->setText("Logs");
		label->setTextSize(TEXT_SIZE);
		m_pGui->add(label);

		// Create a button for clearing the logs
		float fClearButtonWidth = 80.0f;
		m_spClearButton = tgui::Button::create();
		m_spClearButton->setRenderer(theme.getRenderer("Button"));
		m_spClearButton->setPosition(WINDOW_WIDTH - WINDOW_PADDING - fClearButtonWidth, label->getPosition().y);
		m_spClearButton->setSize(fClearButtonWidth, BUTTON_HEIGHT);
		m_spClearButton->setText("Clear");
		m_spClearButton->setTextSize(TEXT_SIZE);
		m_spClearButton->connect("pressed", [&]()
		{
			for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
			{
				m_spLogTextBoxes[iModuleIndex]->removeAllLines();
			}
		});
		m_pGui->add(m_spClearButton);

		// Set minimum and maximum values of inputs
		// Minimum and maximum distance are bounded by the canvas width
		// Minimum rate of change of distance is -9 (left arrow key + 9 number key)
		// Maximum rate of change of distance is 9 (right arrow key + 9 number key)
		// Increase range of output so that the car can catch up to the line
		m_fMinX = (fCarWidth / 2) - (LINE_WIDTH / 2);
		m_fMaxX = fCanvasWidth - (fCarWidth / 2) - (LINE_WIDTH / 2);
		float fMaxDistance = m_fMaxX - m_fMinX;
		m_pAiController->SetMinValues(-fMaxDistance, MIN_LINE_RATEOFCHANGE, MIN_CAR_STEERINGFACTOR);
		m_pAiController->SetMaxValues(fMaxDistance, MAX_LINE_RATEOFCHANGE, MAX_CAR_STEERINGFACTOR);
	}
	catch (const tgui::Exception& e)
	{
		Utils::ShowMessage("Failed to configure UI.", e.what());
		return false;
	}

	return true;
}

#pragma endregion

#pragma region Update/Draw

bool UIManager::IsPaused()
{
	return m_bIsPaused;
}

void UIManager::Update(sf::Time elapsedTime)
{
	bool bDidPrintLog = false;

	for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
	{
		// Pass inputs to the AI Controller
		m_pAiController->UpdateRacingLine(iModuleIndex, m_pRacingLines[iModuleIndex]->GetCenterX(), m_pRacingLines[iModuleIndex]->GetVelocity(), m_pRacingLines[iModuleIndex]->GetRateOfChangeOfDistance());
		m_pAiController->UpdateCar(iModuleIndex, m_pCars[iModuleIndex]->GetCenterX(), m_pCars[iModuleIndex]->GetVelocity());

		// Get the output
		float fSteeringFactor = m_pAiController->GetCarSteeringFactor(iModuleIndex);
		m_pCars[iModuleIndex]->SetSteeringFactor(fSteeringFactor);

		// Log output every interval
		if (elapsedTime - m_lastLoggedTime >= sf::milliseconds(LOG_INTERVAL))
		{
			PrintLog(iModuleIndex);
			bDidPrintLog = true;
		}

		// Apply the output to the movement of the car
		m_pCars[iModuleIndex]->GetSprite().move(m_pCars[iModuleIndex]->GetVelocity() * fSteeringFactor, 0.0f);
	}

	if (bDidPrintLog)
	{
		m_lastLoggedTime = elapsedTime;
	}
}

void UIManager::Draw()
{
	for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
	{
		m_spCanvases[iModuleIndex]->clear(COLOR_DARK_BACKGROUND);
		m_spCanvases[iModuleIndex]->draw(m_pRacingLines[iModuleIndex]->GetShape());
		m_spCanvases[iModuleIndex]->draw(m_moduleNames[iModuleIndex]);
		m_spCanvases[iModuleIndex]->draw(m_pCars[iModuleIndex]->GetSprite());
		if (m_bIsPaused)
		{
			m_spCanvases[iModuleIndex]->draw(m_pausedSprites[iModuleIndex]);
		}

		m_spCanvases[iModuleIndex]->display();
	}

	m_pGui->draw();
}

void UIManager::PrintLog(int iModuleIndex)
{
	sf::Color color;
	switch (iModuleIndex)
	{
	case ModuleIndex::FuzzyLogic:
		color = COLOR_RED;
		break;
	case ModuleIndex::PathFollowing:
		color = COLOR_CYAN;
		break;
	}

	float fMaxDistance = m_fMaxX - m_fMinX;
	float fDistance = (m_pRacingLines[iModuleIndex]->GetCenterX() - m_pCars[iModuleIndex]->GetCenterX()); // / fMaxDistance;
	float fRateOfChangeOfDistance = m_pRacingLines[iModuleIndex]->GetRateOfChangeOfDistance(); // / MAX_LINE_RATEOFCHANGE;
	float fOutput = m_pCars[iModuleIndex]->GetSteeringFactor(); // / MAX_CAR_STEERINGFACTOR;

	if (m_bDidApplyRateOfChange)
	{
		fRateOfChangeOfDistance = m_fRateOfChangeApplied;
		if (iModuleIndex == ModuleIndex::PathFollowing)
		{
			m_bDidApplyRateOfChange = false;
		}
	}

	m_spLogTextBoxes[iModuleIndex]->addLine("Distance: " + std::to_string(fDistance), color);
	m_spLogTextBoxes[iModuleIndex]->addLine("Rate of Change of Distance: " + std::to_string(fRateOfChangeOfDistance), color);
	m_spLogTextBoxes[iModuleIndex]->addLine("Output: " + std::to_string(fOutput), color);

	m_spLogTextBoxes[iModuleIndex]->addLine("", COLOR_DARK_BACKGROUND);
}

#pragma endregion

#pragma region Handle Events/Input

void UIManager::HandleEvent(sf::Event event)
{
	m_pGui->handleEvent(event);
}

void UIManager::HandleKeyboardInput()
{
	int iDirection = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		iDirection = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		iDirection = 1;
	}

	float fRateOfChangeOfDistance = iDirection != 0 ? 1.0f : 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		fRateOfChangeOfDistance = 0.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		fRateOfChangeOfDistance = 1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		fRateOfChangeOfDistance = 2.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		fRateOfChangeOfDistance = 3.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		fRateOfChangeOfDistance = 4.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		fRateOfChangeOfDistance = 5.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		fRateOfChangeOfDistance = 6.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		fRateOfChangeOfDistance = 7.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		fRateOfChangeOfDistance = 8.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		fRateOfChangeOfDistance = 9.0f;
	}
	
	if (iDirection == 0 || fRateOfChangeOfDistance == 0.0f)
	{
		// Reset the rate of change of distance for each module if the lines are not moving
		for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
		{
			m_pRacingLines[iModuleIndex]->SetRateOfChangeOfDistance(0.0f);
		}
	}
	else
	{
		// Move the racing line for each module
		for (int iModuleIndex = 0; iModuleIndex < MODULE_COUNT; iModuleIndex++)
		{
			float fCurrentPosition = m_pRacingLines[iModuleIndex]->GetShape().getPosition().x;
			float fDeltaX = iDirection * m_pRacingLines[iModuleIndex]->GetVelocity() * fRateOfChangeOfDistance;
			float fNewPosition = fCurrentPosition + fDeltaX;
			if (fNewPosition < m_fMinX)
			{
				fNewPosition = m_fMinX;
				fDeltaX = fNewPosition - fCurrentPosition;
			}
			else if (fNewPosition > m_fMaxX)
			{
				fNewPosition = m_fMaxX;
				fDeltaX = fNewPosition - fCurrentPosition;
			}

			if (fDeltaX == 0.0f)
			{
				fRateOfChangeOfDistance = 0.0f;
			}

			m_pRacingLines[iModuleIndex]->SetRateOfChangeOfDistance(iDirection * fRateOfChangeOfDistance);
			m_pRacingLines[iModuleIndex]->GetShape().move(fDeltaX, 0.0f);
		}
	}
}

bool UIManager::InputsAreValid()
{
	std::string strDistance = m_spDistanceTextField->getText();
	std::string strRateOfChange = m_spRateOfChangeTextField->getText();
	std::string strError = "";

	if (!strDistance.empty())
	{
		if (!Utils::StringIsNumber(strDistance))
		{
			strError += "Distance is invalid.";
		}
	}

	if (!strRateOfChange.empty())
	{
		if (!Utils::StringIsNumber(strRateOfChange))
		{
			if (!strError.empty()) strError += " ";
			strError += "Rate of Change of Distance is invalid.";
		}
	}

	if (!strError.empty())
	{
		Utils::ShowMessage(strError, nullptr);
		return false;
	}

	return true;
}

#pragma endregion
