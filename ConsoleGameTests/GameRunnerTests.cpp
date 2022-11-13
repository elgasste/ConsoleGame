#include "gtest/gtest.h"

#include <memory>
#include <thread>

#include <ConsoleGame/GameRunner.h>
#include <ConsoleGame/GameEventAggregator.h>
#include <ConsoleGame/GameEvent.h>

#include "mock_GameClock.h"
#include "mock_GameInputHandler.h"
#include "mock_GameRenderer.h"

using namespace std;
using namespace testing;
using namespace ConsoleGame;

int TickCount = 0;
int HandleInputCount = 0;
int RenderCount = 0;

void IncrementTickCount() { TickCount++; }
void IncrementHandleInputCount () { HandleInputCount++; }
void IncrementRenderCount () { RenderCount++; }

void RunWorker( const shared_ptr<GameRunner> runner )
{
   runner->Run();
}

class GameRunnerTests : public Test
{
public:
   void SetUp() override
   {
      _eventAggregator.reset( new GameEventAggregator );
      _clockMock.reset( new NiceMock<mock_GameClock> );
      _inputHandlerMock.reset( new NiceMock<mock_GameInputHandler> );
      _rendererMock.reset( new NiceMock<mock_GameRenderer> );

      _runner.reset( new GameRunner( _eventAggregator,
                                     _clockMock,
                                     _inputHandlerMock,
                                     _rendererMock ) );

      TickCount = 0;
      HandleInputCount = 0;
      RenderCount = 0;

      ON_CALL( *_clockMock, Tick() ).WillByDefault( Invoke( IncrementTickCount ) );
      ON_CALL( *_inputHandlerMock, HandleInput() ).WillByDefault( Invoke( IncrementHandleInputCount ) );
      ON_CALL( *_rendererMock, Render() ).WillByDefault( Invoke( IncrementRenderCount ) );
   }

protected:
   shared_ptr<GameEventAggregator> _eventAggregator;
   shared_ptr<mock_GameClock> _clockMock;
   shared_ptr<mock_GameInputHandler> _inputHandlerMock;
   shared_ptr<mock_GameRenderer> _rendererMock;

   shared_ptr<GameRunner> _runner;
};

TEST_F( GameRunnerTests, Run_Always_StartsClock )
{
   EXPECT_CALL( *_clockMock, Start() );

   thread runWorker( RunWorker, _runner );
   while( TickCount == 0 ) { }
   _eventAggregator->RaiseEvent( GameEvent::Shutdown );

   runWorker.join();
}

TEST_F( GameRunnerTests, Run_Always_StopsClock )
{
   thread runWorker( RunWorker, _runner );

   while( TickCount == 0 ) { }
   EXPECT_CALL( *_clockMock, Stop() );
   _eventAggregator->RaiseEvent( GameEvent::Shutdown );

   runWorker.join();
}

TEST_F( GameRunnerTests, Run_EveryLoop_RendersGame )
{
   thread runWorker( RunWorker, _runner );
   while( TickCount < 10 ) { }
   _eventAggregator->RaiseEvent( GameEvent::Shutdown );

   runWorker.join();

   EXPECT_EQ( RenderCount, TickCount );
}

TEST_F( GameRunnerTests, Run_EveryLoop_HandlesInput )
{
   thread runWorker( RunWorker, _runner );
   while( TickCount < 10 ) { }
   _eventAggregator->RaiseEvent( GameEvent::Shutdown );

   runWorker.join();

   EXPECT_EQ( HandleInputCount, TickCount );
}
