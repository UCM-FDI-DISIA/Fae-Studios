#include "checkML.h"
#include <iostream>
#include "SDLApplication.h"

using namespace std;

int main(int argc, char* argv[]){
#ifdef __WINDOWS__
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // Check Memory Leaks
#endif

    SDLApplication* game;
    try {
        game = new SDLApplication();
        delete game;
    }
    catch (exception e) {
        cout << e.what();
    }
    return 0;
}