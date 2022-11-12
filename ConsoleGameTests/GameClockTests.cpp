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

      ON_CALL( *_highResolutionClockMock, Now() ).WillByDefault( Return( 0ll ) );
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

TEST_F( GameClockTests, Start_AlreadyRunning_DoesNotChangeValues )
{
   EXPECT_CALL( *_highResolutionClockMock, Now() ).Times( 1 );

   _gameClock->Start();
   _gameClock->Start();
}

TEST_F( GameClockTests, Start_AfterPreviousRun_ResetsAllValues )
{
   EXPECT_CALL( *_highResolutionClockMock, Now() );

   _gameClock->Start();

   EXPECT_CALL( *_highResolutionClockMock, Now() ).WillOnce( Return( 1'000'000ll ) );
   EXPECT_CALL( *_sleeperMock, Sleep( _ ) );

   _gameClock->Tick();
   _gameClock->Stop();

   EXPECT_CALL( *_highResolutionClockMock, Now() );

   _gameClock->Start();

   EXPECT_EQ( _gameClock->GetFramesPerSecond(), 100 );
   EXPECT_EQ( _gameClock->GetTotalFrameCount(), 0 );
   EXPECT_EQ( _gameClock->GetLagFrameCount(), 0 );
}

TEST_F( GameClockTests, Tick_NotRunning_DoesNothing )
{
   EXPECT_CALL( *_highResolutionClockMock, Now() ).Times( 0 );

   _gameClock->Tick();
}

TEST_F( GameClockTests, Tick_FrameIsCounted_IncrementsTotalFrames )
{
   EXPECT_CALL( *_highResolutionClockMock, Now() );

   _gameClock->Start();

   EXPECT_CALL( *_highResolutionClockMock, Now() ).WillOnce( Return( 1ll ) );
   EXPECT_CALL( *_sleeperMock, Sleep( _ ) );

   _gameClock->Tick();

   EXPECT_EQ( _gameClock->GetTotalFrameCount(), 1 );
}

TEST_F( GameClockTests, Tick_TimeIsLeftInFrame_SleepsForRemainingTime )
{
   EXPECT_CALL( *_highResolutionClockMock, Now() );

   _gameClock->Start();

   EXPECT_CALL( *_highResolutionClockMock, Now() ).WillOnce( Return( 1'000'000ll ) );
   EXPECT_CALL( *_sleeperMock, Sleep( 9 ) );

   _gameClock->Tick();
}

TEST_F( GameClockTests, Tick_FrameIsOverTime_IncrementsLagFrames )
{
   EXPECT_CALL( *_highResolutionClockMock, Now() );

   _gameClock->Start();

   auto nanoSecondsPerFrame = 1'000'000'000ll / _framesPerSecond;

   EXPECT_CALL( *_highResolutionClockMock, Now() ).WillOnce( Return( nanoSecondsPerFrame + 1ll ) );
   EXPECT_CALL( *_sleeperMock, Sleep( _ ) ).Times( 0 );

   _gameClock->Tick();

   EXPECT_EQ( _gameClock->GetLagFrameCount(), 1 );
}
