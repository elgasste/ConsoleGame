#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "SleeperWrapper.h"

using namespace ConsoleGame;

void SleeperWrapper::Sleep( unsigned long milliseconds )
{
   ::Sleep( milliseconds );
}
