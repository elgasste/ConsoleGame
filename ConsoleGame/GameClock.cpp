#include "GameClock.h"
#include "IHighResolutionClock.h"
#include "ISleeper.h"

using namespace std;
using namespace ConsoleGame;

GameClock::GameClock( const shared_ptr<IHighResolutionClock> highResolutionClock,
                      const shared_ptr<ISleeper> sleeper,
                      int framesPerSecond )
   : _highResolutionClock( highResolutionClock ),
     _sleeper( sleeper ),
     _framesPerSecond( framesPerSecond ),
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

   _frameStartTimeNano = _highResolutionClock->Now();
}

void GameClock::Tick()
{
   if ( !_isRunning )
   {
      return;
   }

   auto elapsedFrameTimeNano = _highResolutionClock->Now() - _frameStartTimeNano;
   auto remainingFrameTimeNano = _nanoSecondsPerFrame - elapsedFrameTimeNano;

   if ( remainingFrameTimeNano > 0ll )
   {
      _sleeper->Sleep( (unsigned long)( remainingFrameTimeNano / 1'000'000 ) ); // Sleep() uses milliseconds
   }
   else if ( remainingFrameTimeNano < 0ll )
   {
      _lagFrameCount++;
   }

   _totalFrameCount++;
   _frameStartTimeNano = _highResolutionClock->Now();
}

void GameClock::Stop()
{
   _isRunning = false;
}
