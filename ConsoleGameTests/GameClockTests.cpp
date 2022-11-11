#include "gtest/gtest.h"

#include <memory>

#include <ConsoleGame/GameClock.h>

#include "mock_HighResolutionClock.h"
#include "mock_Sleeper.h"

using namespace std;
using namespace testing;
using namespace ConsoleGame;

class GameClockTests : public Test
{
public:
   void SetUp() override
   {
      _highResolutionClockMock.reset( new mock_HighResolutionClock() );
      _sleeperMock.reset( new mock_Sleeper() );
      _framesPerSecond = 100;

      _gameClock.reset( new GameClock( _highResolutionClockMock,
                                       _sleeperMock,
                                       _framesPerSecond ) );

      ON_CALL( *_highResolutionClockMock, Now() ).WillByDefault( Return( chrono::steady_clock::time_point() ) );
   }

protected:
   shared_ptr<mock_HighResolutionClock> _highResolutionClockMock;
   shared_ptr<mock_Sleeper> _sleeperMock;
   int _framesPerSecond;

   shared_ptr<GameClock> _gameClock;
};

TEST_F( GameClockTests, Constructor_Always_InitializesAllValues )
{
   EXPECT_EQ( _gameClock->GetFramesPerSecond(), 100 );
   EXPECT_EQ( _gameClock->GetTotalFrameCount(), 0 );
   EXPECT_EQ( _gameClock->GetLagFrameCount(), 0 );
}
