#include <SDL2/SDL.h>
#include <thread>
#include <iostream>
#include <SDLGame.h>

namespace ReBackyardMonsters
{
	void SDLGame::Initialize() {
	    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	        std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
	
	    window = SDL_CreateWindow("Re: Backyard Monsters", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1152, 864, SDL_WINDOW_SHOWN);
	    SDL_SetWindowResizable(window, SDL_TRUE);
	    if (window == nullptr) {
	        std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
	    }
	    int imgFlags = IMG_INIT_PNG;
	    if (!(IMG_Init(imgFlags) & imgFlags))
	        std::cerr << "SDL_Error: " << "Couldn't init SDL_Image." << std::endl;
	    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	    SDL_RenderSetLogicalSize(renderer, 1152, 864);
	    SDL_GL_SetSwapInterval(0);
	    SDL_UpdateWindowSurface(window);
	}

	void SDLGame::Cleanup()  {
	    SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    SDL_Quit();
	    exit(1);
	}

	void SDLGame::RunFrame()
	{
		this->handleEvents(); // Include this in timing?
	        
	    auto start = std::chrono::high_resolution_clock::now();
	
	    this->Update(frameDelta);
	    this->Render();
	
	    // TODO: Refactor time tracking to seconds, so we can actually use it in Gametick() sanely
	    if (!Focused)
	        std::this_thread::sleep_for(std::chrono::microseconds((62500 - Globals::minimumFrameDelta)));
	    auto stop = std::chrono::high_resolution_clock::now();
	
	    frameDelta = std::chrono::duration_cast<std::chrono::microseconds>(start-stop).count();
	    if (frameDelta < Globals::minimumFrameDelta && Focused)
	        std::this_thread::sleep_for(std::chrono::microseconds(Globals::minimumFrameDelta - (int) frameDelta));
	    frameCount++;
	}

	void SDLGame::Gameloop() {
	    while (!requestQuit) {
	        RunFrame();
	    }
	}

	void SDLGame::Run()
	{
	    Gameloop();
	}

	void SDLGame::handleEvents() {
		while (SDL_PollEvent(&event)) {
		    if (event.type == SDL_QUIT)
		        requestQuit = true;
		
		    if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		    	Focused = false;

			if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
				Focused = true;
		}
	}    
	void SDLGame::Render() { } // To be overriden in derived class
	void SDLGame::Update(float delta) { } // To be overriden in derived class

	SDLGame::SDLGame()
	{
	        
	}
	
	SDLGame::~SDLGame()
	{
	        
	}
	
	Vector2 SDLGame::GetWindowSize() {
	    return {width, height};
	}
	void SDLGame::SetWindowSize(int x, int y) {
	    SetWindowSize(x, y, true);
	        
	        //SDL_SetWindowSize(window, x, y);
	}
	void SDLGame::SetWindowSize(Vector2 const&v) {
	    SetWindowSize(v.GetX(), v.GetY(), true);
	}
	void SDLGame::setWindowSize(int width, int height, bool updateWindow)
	{
	    this->width = width;
	    this->height = height;
	    if (updateWindow)
	        SDL_SetWindowSize(window, width, height);
	}
}
