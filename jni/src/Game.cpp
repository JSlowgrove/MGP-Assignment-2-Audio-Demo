#include "Game.h"
#include "SDL.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(JAM_StateManager * stateManager, SDL_Renderer* renderer, int screenWidth, int screenHeight)
	: JAM_State(stateManager, renderer, screenWidth, screenHeight)
{
	/*initialise the textures*/
	JAM_Texture* playTexture = new JAM_Texture("img/play.png", renderer);
	JAM_Texture* stopTexture = new JAM_Texture("img/stop.png", renderer);

	/*initialise buttons*/
	buttons.push_back(new JAM_Button(stopTexture, JAM_Utilities::scaleNumber(200.0f, screenHeight), 
		JAM_Utilities::scaleNumber(180.0f, screenHeight), JAM_Utilities::scaleNumber(100.0f, screenHeight),
		JAM_Utilities::scaleNumber(100.0f, screenHeight)));
	buttons.push_back(new JAM_Button(playTexture, JAM_Utilities::scaleNumber(350.0f, screenHeight),
		JAM_Utilities::scaleNumber(180.0f, screenHeight), JAM_Utilities::scaleNumber(100.0f, screenHeight),
		JAM_Utilities::scaleNumber(100.0f, screenHeight)));
	buttons.push_back(new JAM_Button(playTexture, JAM_Utilities::scaleNumber(200.0f, screenHeight),
		JAM_Utilities::scaleNumber(300.0f, screenHeight), JAM_Utilities::scaleNumber(100.0f, screenHeight),
		JAM_Utilities::scaleNumber(100.0f, screenHeight)));

	/*initialise the music*/
	music = new JAM_Audio("aud/Cipher.ogg", true);
	soundEffect = new JAM_Audio("aud/zapThreeToneDown.ogg", false);

	/*initialise the playing boolean*/
	playing = false;
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	/*stop music*/
	music->stopAudio();
	/*delete audio pointers*/
	delete music;
	delete soundEffect;
	/*delete pointers*/
	for (auto button : buttons)
	{
		delete button;
	}
}

/**************************************************************************************************************/

/*handles inputs*/
bool Game::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT: /*If player closes the window, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;
		}

		/*if the stop button is pressed*/
		if (buttons[0]->input(incomingEvent))
		{
			/*stop music*/
			music->stopAudio();
			playing = false;
		}

		/*if the play button is pressed*/
		if (buttons[1]->input(incomingEvent))
		{
			/*start music*/
			music->startAudio();
			playing = true;
		}

		/*if the sound effect button is pressed*/
		if (buttons[2]->input(incomingEvent))
		{
			/*play sound effect*/
			soundEffect->playEffect();
	}
				
#ifdef __ANDROID__

		/*handle the android inputs*/
		return androidInput(incomingEvent);

#elif _WIN32	

		/*handle the windows inputs*/
		return windowsInput(incomingEvent);

#endif

	}
	return true;
}

/**************************************************************************************************************/

/*handles windows inputs*/
bool Game::windowsInput(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE: /*If Escape is pressed, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;

		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*handles android inputs*/
bool Game::androidInput(SDL_Event& incomingEvent)
{
	switch (incomingEvent.type)
	{
	case SDL_KEYDOWN:

		switch (incomingEvent.key.keysym.sym)
		{
		case SDLK_AC_BACK: /*If Back is pressed on the phone, end the game loop*/

			SDL_Log("Exiting Main Loop");
			return false;
			break;
		}
		break;
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
	/*if the music boolean is true*/
	if (playing)
	{
		/*keep the music playing*/
		music->startAudio();
	}
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	/*draw the buttons*/
	buttons[0]->draw(renderer);
	buttons[1]->draw(renderer);
	buttons[2]->draw(renderer);
}