#include "GameClock.h"
#include "IHighResolutionClock.h"

using namespace std;
using namespace ConsoleGame;

GameClock::GameClock( const shared_ptr<IHighResolutionClock> highResolutionClock ) :
   _highResolutionClock( highResolutionClock ),
   _totalFrameCount( 0 ),
   _lagFrameCount( 0 ),
   _absoluteStartTimeNano( 0 ),
   _frameStartTimeNano( 0 ),
   _lastFrameDurationNano( 0 ),
   _totalDurationNano( 0 )
{
}

void GameClock::StartFrame()
{
   _frameStartTimeNano = _highResolutionClock->Now();
}

void GameClock::EndFrame()
{
   _totalFrameCount++;
   auto now = _highResolutionClock->Now();
   _lastFrameDurationNano = now - _frameStartTimeNano;
   _totalDurationNano = now - _absoluteStartTimeNano;
}

long long GameClock::GetAverageFrameRate() const
{
   return _totalFrameCount == 0 ? 0 : ( 1'000'000'000 / ( _totalDurationNano / _totalFrameCount ) );
}

float GameClock::GetFrameSeconds() const
{
   return _lastFrameDurationNano / 1'000'000'000.0f;
}
