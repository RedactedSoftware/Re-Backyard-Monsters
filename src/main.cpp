#include "gameTick.hpp"
#include "frameRender.hpp"
int main() {
    //init code here
    std::thread frameRenderThread (frameRender);
    std::thread gameTickThread (gameTick);
    //Do stuff on main thread here
    frameRenderThread.join();
    gameTickThread.join();
    return 0;
}
