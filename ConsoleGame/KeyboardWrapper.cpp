#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "KeyboardWrapper.h"

using namespace ConsoleGame;

bool KeyboardWrapper::IsKeyDown( KeyCode keyCode ) const
{
   return GetKeyState( (int)keyCode ) & 0x800; // if the high-order bit is 1, the key is down
}
