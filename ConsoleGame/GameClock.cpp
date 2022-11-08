#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "GameClock.h"

using namespace std;
using namespace ConsoleGame;

GameClock::GameClock( int framesPerSecond )
   : _framesPerSecond( framesPerSecond ),
     _totalFrameCount( 0 ),
     _lagFrameCount( 0 ),
     _frameStartTimeNano(),
     _nanoSecondsPerFrame( 1'000'000'000ll / framesPerSecond ),
     _isRunning( false )
{ }

void GameClock::Start()
{
   if ( _isRunning )
   {
      return;
   }

   _totalFrameCount = 0;
   _lagFrameCount = 0;
   _isRunning = true;

   _frameStartTimeNano = chrono::high_resolution_clock::now();
}

void GameClock::Tick()
{
   if ( !_isRunning )
   {
      return;
   }

   auto elapsedFrameTimeNano = chrono::high_resolution_clock::now() - _frameStartTimeNano;
   auto remainingFrameTimeNano = _nanoSecondsPerFrame - elapsedFrameTimeNano.count();

   if ( remainingFrameTimeNano > 0ll )
   {
      Sleep( (DWORD)( remainingFrameTimeNano / 1'000'000 ) ); // Sleep() uses milliseconds
   }
   else if ( remainingFrameTimeNano < 0ll )
   {
      _lagFrameCount++;
   }

   _totalFrameCount++;
   _frameStartTimeNano = chrono::high_resolution_clock::now();
}

void GameClock::Stop()
{
   _isRunning = false;
}
