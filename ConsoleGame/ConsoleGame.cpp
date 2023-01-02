#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include "GameConfig.h"
#include "ConsoleRenderDefs.h"
#include "KeyboardInputDefs.h"
#include "PlayerDefs.h"
#include "ArenaDefs.h"
#include "KeyCode.h"
#include "GameButton.h"
#include "HighResolutionClockWrapper.h"
#include "SleeperWrapper.h"
#include "KeyboardWrapper.h"
#include "ThreadWrapper.h"
#include "GameEventAggregator.h"
#include "GameClock.h"
#include "KeyboardInputReader.h"
#include "PlayerFactory.h"
#include "Game.h"
#include "DiagnosticsConsoleRenderer.h"
#include "StartupStateInputHandler.h"
#include "PlayingStateInputHandler.h"
#include "GameInputHandler.h"
#include "ConsoleBuffer.h"
#include "StartupStateConsoleRenderer.h"
#include "PlayingStateConsoleRenderer.h"
#include "GameRenderer.h"
#include "GameRunner.h"
#include "GameState.h"
#include "ConsoleColor.h"
#include "Direction.h"

using namespace std;
using namespace ConsoleGame;

// TODO: I suppose these configs should be loaded from files at some point,
// but at the very least they should all have default values, and those could
// probably be set in some initializer instead of in here.
shared_ptr<ConsoleRenderDefs> BuildConsoleRenderDefs();
shared_ptr<KeyboardInputDefs> BuildKeyboardInputDefs();
shared_ptr<PlayerDefs> BuildPlayerDefs();
shared_ptr<ArenaDefs> BuildArenaDefs();
shared_ptr<GameConfig> BuildGameConfig();
void LoadAndRun( const shared_ptr<IConsoleBuffer> consoleBuffer );

INT WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow )
{
   AllocConsole();
   wstring consoleTitle = L"Console Game";
   SetConsoleTitle( consoleTitle.c_str() );

   // you can't close this window unless I WANT you to
   EnableMenuItem( GetSystemMenu( GetConsoleWindow(), FALSE ), SC_CLOSE , MF_GRAYED );
   DrawMenuBar( GetConsoleWindow() );

   auto consoleHandleR = _open_osfhandle( (intptr_t)GetStdHandle( STD_INPUT_HANDLE ), _O_TEXT );
   auto fptr = _fdopen( consoleHandleR, "r" );
   *stdin = *fptr;
   setvbuf( stdin, NULL, _IONBF, 0 );

   auto consoleHandleW = _open_osfhandle( (intptr_t)GetStdHandle( STD_OUTPUT_HANDLE ), _O_TEXT );
   fptr = _fdopen( consoleHandleW, "w" );
   *stdout = *fptr;
   setvbuf( stdout, NULL, _IONBF, 0 );

   *stderr = *fptr;
   setvbuf( stderr, NULL, _IONBF, 0 );

   auto consoleBuffer = shared_ptr<ConsoleBuffer>( new ConsoleBuffer() );
   LoadAndRun( consoleBuffer );
}

void LoadAndRun( const shared_ptr<IConsoleBuffer> consoleBuffer )
{
   consoleBuffer->Draw( 2, 1, "Loading all the things..." );
   consoleBuffer->Flip();

   // configs
   auto config = BuildGameConfig();
   auto consoleRenderDefs = static_pointer_cast<ConsoleRenderDefs>( config->RenderDefs );
   auto keyboardInputDefs = static_pointer_cast<KeyboardInputDefs>( config->InputDefs );

   // wrappers
   auto highResolutionClock = shared_ptr<HighResolutionClockWrapper>( new HighResolutionClockWrapper() );
   auto sleeper = shared_ptr<SleeperWrapper>( new SleeperWrapper() );
   auto keyboard = shared_ptr<IKeyboard>( new KeyboardWrapper() );
   auto thread = shared_ptr<IThread>( new ThreadWrapper() );

   // auxiliary objects
   auto eventAggregator = shared_ptr<GameEventAggregator>( new GameEventAggregator() );
   auto clock = shared_ptr<GameClock>( new GameClock( highResolutionClock, sleeper, config->FramesPerSecond ) );
   auto keyboardInputReader = shared_ptr<KeyboardInputReader>( new KeyboardInputReader( keyboardInputDefs, keyboard ) );

   // game data objects
   auto playerFactory = shared_ptr<IPlayerFactory>( new PlayerFactory( config ) );
   auto game = shared_ptr<Game>( new Game( config, eventAggregator, playerFactory ) );

   // input objects
   auto startupStateInputHandler = shared_ptr<StartupStateInputHandler>( new StartupStateInputHandler( keyboardInputReader, game ) );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( keyboardInputReader, game ) );
   auto inputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( keyboardInputReader, game, eventAggregator ) );
   inputHandler->AddInputHandlerForGameState( GameState::Startup, startupStateInputHandler );
   inputHandler->AddInputHandlerForGameState( GameState::Playing, playingStateInputHandler );

   // rendering objects
   auto diagnosticsRenderer = shared_ptr<DiagnosticsConsoleRenderer>( new DiagnosticsConsoleRenderer( consoleBuffer, clock, consoleRenderDefs ) );
   auto startupStateConsoleRenderer = shared_ptr<StartupStateConsoleRenderer>( new StartupStateConsoleRenderer( consoleBuffer, consoleRenderDefs, keyboardInputDefs ) );
   auto playingStateConsoleRenderer = shared_ptr<PlayingStateConsoleRenderer>( new PlayingStateConsoleRenderer( consoleBuffer, consoleRenderDefs, game ) );
   auto renderer = shared_ptr<GameRenderer>( new GameRenderer( consoleRenderDefs, consoleBuffer, game, diagnosticsRenderer, eventAggregator ) );
   renderer->AddRendererForGameState( GameState::Startup, startupStateConsoleRenderer );
   renderer->AddRendererForGameState( GameState::Playing, playingStateConsoleRenderer );

   // game loop
   auto runner = shared_ptr<GameRunner>( new GameRunner( eventAggregator, clock, inputHandler, renderer, game, thread ) );

   runner->Run();
}

shared_ptr<ConsoleRenderDefs> BuildConsoleRenderDefs()
{
   auto renderDefs = make_shared<ConsoleRenderDefs>();

   renderDefs->ConsoleWidth = 120;
   renderDefs->ConsoleHeight = 30;

   renderDefs->ArenaCharWidth = 114;
   renderDefs->ArenaCharHeight = 24;

   renderDefs->ArenaFenceX = 2;
   renderDefs->ArenaFenceY = 3;

   renderDefs->DefaultForegroundColor = ConsoleColor::Grey;
   renderDefs->DefaultBackgroundColor = ConsoleColor::Black;

   renderDefs->PlayerStaticSprite.Width = 1;
   renderDefs->PlayerStaticSprite.Height = 1;
   renderDefs->PlayerStaticSprite.Pixels.push_back( { '*', ConsoleColor::White } );

   renderDefs->PlayerMovingSpriteMap[Direction::Left].Width = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::Left].Height = 1;
   renderDefs->PlayerMovingSpriteMap[Direction::Left].Pixels.push_back( { '+', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::Left].Pixels.push_back( { '-', ConsoleColor::White } );

   renderDefs->PlayerMovingSpriteMap[Direction::UpLeft].Width = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::UpLeft].Height = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::UpLeft].Pixels.push_back( { '+', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::UpLeft].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::UpLeft].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::UpLeft].Pixels.push_back( { '\\', ConsoleColor::White } );

   renderDefs->PlayerMovingSpriteMap[Direction::Up].Width = 1;
   renderDefs->PlayerMovingSpriteMap[Direction::Up].Height = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::Up].Pixels.push_back( { '+', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::Up].Pixels.push_back( { '|', ConsoleColor::White } );

   renderDefs->PlayerMovingSpriteMap[Direction::UpRight].Width = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::UpRight].Height = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::UpRight].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::UpRight].Pixels.push_back( { '+', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::UpRight].Pixels.push_back( { '/', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::UpRight].Pixels.push_back( { ' ', ConsoleColor::White } );

   renderDefs->PlayerMovingSpriteMap[Direction::Right].Width = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::Right].Height = 1;
   renderDefs->PlayerMovingSpriteMap[Direction::Right].Pixels.push_back( { '-', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::Right].Pixels.push_back( { '+', ConsoleColor::White } );

   renderDefs->PlayerMovingSpriteMap[Direction::DownRight].Width = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::DownRight].Height = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::DownRight].Pixels.push_back( { '\\', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::DownRight].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::DownRight].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::DownRight].Pixels.push_back( { '+', ConsoleColor::White } );

   renderDefs->PlayerMovingSpriteMap[Direction::Down].Width = 1;
   renderDefs->PlayerMovingSpriteMap[Direction::Down].Height = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::Down].Pixels.push_back( { '|', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::Down].Pixels.push_back( { '+', ConsoleColor::White } );

   renderDefs->PlayerMovingSpriteMap[Direction::DownLeft].Width = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::DownLeft].Height = 2;
   renderDefs->PlayerMovingSpriteMap[Direction::DownLeft].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::DownLeft].Pixels.push_back( { '/', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::DownLeft].Pixels.push_back( { '+', ConsoleColor::White } );
   renderDefs->PlayerMovingSpriteMap[Direction::DownLeft].Pixels.push_back( { ' ', ConsoleColor::White } );

   return renderDefs;
}

shared_ptr<KeyboardInputDefs> BuildKeyboardInputDefs()
{
   auto inputDefs = make_shared<KeyboardInputDefs>();

   // key code bindings
   inputDefs->KeyMap[KeyCode::Left] = GameButton::Left;
   inputDefs->KeyMap[KeyCode::Up] = GameButton::Up;
   inputDefs->KeyMap[KeyCode::Right] = GameButton::Right;
   inputDefs->KeyMap[KeyCode::Down] = GameButton::Down;

   inputDefs->KeyMap[KeyCode::Return] = GameButton::Start;
   inputDefs->KeyMap[KeyCode::Tab] = GameButton::Select;

   inputDefs->KeyMap[KeyCode::A] = GameButton::A;
   inputDefs->KeyMap[KeyCode::Return] = GameButton::A;
   inputDefs->KeyMap[KeyCode::Space] = GameButton::A;
   inputDefs->KeyMap[KeyCode::B] = GameButton::B;
   inputDefs->KeyMap[KeyCode::X] = GameButton::X;
   inputDefs->KeyMap[KeyCode::Y] = GameButton::Y;

   inputDefs->KeyMap[KeyCode::NumPad1] = GameButton::L1;
   inputDefs->KeyMap[KeyCode::NumPad2] = GameButton::L2;
   inputDefs->KeyMap[KeyCode::NumPad3] = GameButton::R1;
   inputDefs->KeyMap[KeyCode::NumPad4] = GameButton::R2;

   inputDefs->KeyMap[KeyCode::F12] = GameButton::Diagnostics;

   // key names
   inputDefs->KeyNames[KeyCode::Left] = "Left Arrow";
   inputDefs->KeyNames[KeyCode::Up] = "Up Arrow";
   inputDefs->KeyNames[KeyCode::Right] = "Right Arrow";
   inputDefs->KeyNames[KeyCode::Down] = "Down Arrow";
   inputDefs->KeyNames[KeyCode::Return] = "Enter";
   inputDefs->KeyNames[KeyCode::Space] = "Space Bar";
   inputDefs->KeyNames[KeyCode::Tab] = "Tab";
   inputDefs->KeyNames[KeyCode::A] = "A";
   inputDefs->KeyNames[KeyCode::B] = "B";
   inputDefs->KeyNames[KeyCode::X] = "X";
   inputDefs->KeyNames[KeyCode::Y] = "Y";
   inputDefs->KeyNames[KeyCode::NumPad1] = "1";
   inputDefs->KeyNames[KeyCode::NumPad2] = "2";
   inputDefs->KeyNames[KeyCode::NumPad3] = "3";
   inputDefs->KeyNames[KeyCode::NumPad4] = "4";
   inputDefs->KeyNames[KeyCode::F12] = "F12";

   // button names
   inputDefs->ButtonNames[GameButton::Left] = "Left";
   inputDefs->ButtonNames[GameButton::Up] = "Up";
   inputDefs->ButtonNames[GameButton::Right] = "Right";
   inputDefs->ButtonNames[GameButton::Down] = "Down";
   inputDefs->ButtonNames[GameButton::Start] = "Start";
   inputDefs->ButtonNames[GameButton::Select] = "Select";
   inputDefs->ButtonNames[GameButton::A] = "A";
   inputDefs->ButtonNames[GameButton::B] = "B";
   inputDefs->ButtonNames[GameButton::X] = "X";
   inputDefs->ButtonNames[GameButton::Y] = "Y";
   inputDefs->ButtonNames[GameButton::L1] = "L1";
   inputDefs->ButtonNames[GameButton::L2] = "L2";
   inputDefs->ButtonNames[GameButton::R1] = "R1";
   inputDefs->ButtonNames[GameButton::R2] = "R2";
   inputDefs->ButtonNames[GameButton::Diagnostics] = "Toggle Diagnostics";

   return inputDefs;
}

shared_ptr<PlayerDefs> BuildPlayerDefs()
{
   auto playerDefs = make_shared<PlayerDefs>();

   playerDefs->StartVelocityX = 0.;
   playerDefs->StartVelocityY = 0.;

   // this means at max velocity, it should take
   // 3 seconds to cross the arena horizontally
   playerDefs->MaxVelocity = 1444.;

   // this means it should take a third of a second
   // to go from 0 to max velocity
   playerDefs->AccelerationPerSecond = 4332.;

   playerDefs->StartDirection = Direction::Right;

   return playerDefs;
}

shared_ptr<ArenaDefs> BuildArenaDefs()
{
   auto arenaDefs = make_shared<ArenaDefs>();

   arenaDefs->Width = 4332.;
   arenaDefs->Height = 1872.;

   arenaDefs->PlayerStartX = arenaDefs->Width / 2.;
   arenaDefs->PlayerStartY = arenaDefs->Height / 2.;

   return arenaDefs;
}

shared_ptr<GameConfig> BuildGameConfig()
{
   auto config = make_shared<GameConfig>();

   config->FramesPerSecond = 60;

   config->RenderDefs = BuildConsoleRenderDefs();
   config->InputDefs = BuildKeyboardInputDefs();
   config->PlayerDefs = BuildPlayerDefs();
   config->ArenaDefs = BuildArenaDefs();

   return config;
}
