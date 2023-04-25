#pragma once
namespace ReBackyardMonsters
{
	// Base Game Implementation
	class SDLGame {
	public:
	    SDLGame();
	    ~SDLGame();
	    
	    virtual void Initialize();
	    virtual void Cleanup();
	    virtual void Update(float delta);
	    virtual void Render();
	
	    // Starts Render & Gametic Threads
	    void Run();
	    void Gameloop();
	    void RunFrame();
	
	    bool Focused;
	    bool Paused;
	
	    Vector2 GetWindowSize();
	    void SetWindowSize(int x, int y);
	    void SetWindowSize(Vector2 const&v);
	
	protected:
	    int width;
	    int height;
	    bool requestQuit;
	    float frameDelta;
	    float tickDelta;
	    int frameCount;
	
	    SDL_Event event;
	    SDL_Renderer *renderer;
	    SDL_Window *window;
	
	};
}
