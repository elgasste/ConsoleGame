#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include "GameConfig.h"
#include "ConsoleRenderConfig.h"
#include "KeyboardInputConfig.h"
#include "PlayerConfig.h"
#include "ArenaConfig.h"
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
shared_ptr<ConsoleRenderConfig> BuildConsoleRenderConfig();
shared_ptr<KeyboardInputConfig> BuildKeyboardInputConfig();
shared_ptr<PlayerConfig> BuildPlayerConfig();
shared_ptr<ArenaConfig> BuildArenaConfig();
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

   auto consoleBuffer = shared_ptr<ConsoleBuffer>( new ConsoleBuffer( 120, 30 ) );
   LoadAndRun( consoleBuffer );
}

void LoadAndRun( const shared_ptr<IConsoleBuffer> consoleBuffer )
{
   // configs
   auto config = BuildGameConfig();
   auto consoleRenderConfig = static_pointer_cast<ConsoleRenderConfig>( config->RenderConfig );
   auto keyboardInputConfig = static_pointer_cast<KeyboardInputConfig>( config->InputConfig );

   // wrappers
   auto highResolutionClock = shared_ptr<HighResolutionClockWrapper>( new HighResolutionClockWrapper() );
   auto sleeper = shared_ptr<SleeperWrapper>( new SleeperWrapper() );
   auto keyboard = shared_ptr<IKeyboard>( new KeyboardWrapper() );
   auto thread = shared_ptr<IThread>( new ThreadWrapper() );

   // auxiliary objects
   auto eventAggregator = shared_ptr<GameEventAggregator>( new GameEventAggregator() );
   auto clock = shared_ptr<GameClock>( new GameClock( highResolutionClock, sleeper, config->FramesPerSecond ) );
   auto keyboardInputReader = shared_ptr<KeyboardInputReader>( new KeyboardInputReader( keyboardInputConfig, keyboard ) );

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
   auto diagnosticsRenderer = shared_ptr<DiagnosticsConsoleRenderer>( new DiagnosticsConsoleRenderer( consoleBuffer, clock, consoleRenderConfig ) );
   auto startupStateConsoleRenderer = shared_ptr<StartupStateConsoleRenderer>( new StartupStateConsoleRenderer( consoleBuffer, consoleRenderConfig, keyboardInputConfig ) );
   auto playingStateConsoleRenderer = shared_ptr<PlayingStateConsoleRenderer>( new PlayingStateConsoleRenderer( consoleBuffer, consoleRenderConfig, game ) );
   auto renderer = shared_ptr<GameRenderer>( new GameRenderer( consoleRenderConfig, consoleBuffer, game, diagnosticsRenderer, eventAggregator ) );
   renderer->AddRendererForGameState( GameState::Startup, startupStateConsoleRenderer );
   renderer->AddRendererForGameState( GameState::Playing, playingStateConsoleRenderer );

   // game loop
   auto runner = shared_ptr<GameRunner>( new GameRunner( eventAggregator, clock, inputHandler, renderer, game, thread ) );

   runner->Run();
}

shared_ptr<ConsoleRenderConfig> BuildConsoleRenderConfig()
{
   auto renderConfig = make_shared<ConsoleRenderConfig>();

   renderConfig->ConsoleWidth = 120;
   renderConfig->ConsoleHeight = 30;

   renderConfig->ArenaCharWidth = 114;
   renderConfig->ArenaCharHeight = 24;

   renderConfig->ArenaFenceX = 2;
   renderConfig->ArenaFenceY = 3;

   renderConfig->DefaultForegroundColor = ConsoleColor::Grey;
   renderConfig->DefaultBackgroundColor = ConsoleColor::Black;

   renderConfig->PlayerStaticSprite.Width = 1;
   renderConfig->PlayerStaticSprite.Height = 1;
   renderConfig->PlayerStaticSprite.Pixels.push_back( { '*', ConsoleColor::White } );

   renderConfig->PlayerMovingSpriteMap[Direction::Left].Width = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::Left].Height = 1;
   renderConfig->PlayerMovingSpriteMap[Direction::Left].Pixels.push_back( { '+', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::Left].Pixels.push_back( { '-', ConsoleColor::White } );

   renderConfig->PlayerMovingSpriteMap[Direction::UpLeft].Width = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::UpLeft].Height = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::UpLeft].Pixels.push_back( { '+', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::UpLeft].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::UpLeft].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::UpLeft].Pixels.push_back( { '\\', ConsoleColor::White } );

   renderConfig->PlayerMovingSpriteMap[Direction::Up].Width = 1;
   renderConfig->PlayerMovingSpriteMap[Direction::Up].Height = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::Up].Pixels.push_back( { '+', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::Up].Pixels.push_back( { '|', ConsoleColor::White } );

   renderConfig->PlayerMovingSpriteMap[Direction::UpRight].Width = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::UpRight].Height = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::UpRight].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::UpRight].Pixels.push_back( { '+', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::UpRight].Pixels.push_back( { '/', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::UpRight].Pixels.push_back( { ' ', ConsoleColor::White } );

   renderConfig->PlayerMovingSpriteMap[Direction::Right].Width = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::Right].Height = 1;
   renderConfig->PlayerMovingSpriteMap[Direction::Right].Pixels.push_back( { '-', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::Right].Pixels.push_back( { '+', ConsoleColor::White } );

   renderConfig->PlayerMovingSpriteMap[Direction::DownRight].Width = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::DownRight].Height = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::DownRight].Pixels.push_back( { '\\', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::DownRight].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::DownRight].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::DownRight].Pixels.push_back( { '+', ConsoleColor::White } );

   renderConfig->PlayerMovingSpriteMap[Direction::Down].Width = 1;
   renderConfig->PlayerMovingSpriteMap[Direction::Down].Height = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::Down].Pixels.push_back( { '|', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::Down].Pixels.push_back( { '+', ConsoleColor::White } );

   renderConfig->PlayerMovingSpriteMap[Direction::DownLeft].Width = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::DownLeft].Height = 2;
   renderConfig->PlayerMovingSpriteMap[Direction::DownLeft].Pixels.push_back( { ' ', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::DownLeft].Pixels.push_back( { '/', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::DownLeft].Pixels.push_back( { '+', ConsoleColor::White } );
   renderConfig->PlayerMovingSpriteMap[Direction::DownLeft].Pixels.push_back( { ' ', ConsoleColor::White } );

   return renderConfig;
}

shared_ptr<KeyboardInputConfig> BuildKeyboardInputConfig()
{
   auto inputConfig = make_shared<KeyboardInputConfig>();

   // key code bindings
   inputConfig->KeyMap[KeyCode::Left] = GameButton::Left;
   inputConfig->KeyMap[KeyCode::Up] = GameButton::Up;
   inputConfig->KeyMap[KeyCode::Right] = GameButton::Right;
   inputConfig->KeyMap[KeyCode::Down] = GameButton::Down;

   inputConfig->KeyMap[KeyCode::Return] = GameButton::Start;
   inputConfig->KeyMap[KeyCode::Tab] = GameButton::Select;

   inputConfig->KeyMap[KeyCode::A] = GameButton::A;
   inputConfig->KeyMap[KeyCode::Return] = GameButton::A;
   inputConfig->KeyMap[KeyCode::Space] = GameButton::A;
   inputConfig->KeyMap[KeyCode::B] = GameButton::B;
   inputConfig->KeyMap[KeyCode::X] = GameButton::X;
   inputConfig->KeyMap[KeyCode::Y] = GameButton::Y;

   inputConfig->KeyMap[KeyCode::NumPad1] = GameButton::L1;
   inputConfig->KeyMap[KeyCode::NumPad2] = GameButton::L2;
   inputConfig->KeyMap[KeyCode::NumPad3] = GameButton::R1;
   inputConfig->KeyMap[KeyCode::NumPad4] = GameButton::R2;

   inputConfig->KeyMap[KeyCode::F12] = GameButton::Diagnostics;

   // key names
   inputConfig->KeyNames[KeyCode::Left] = "Left Arrow";
   inputConfig->KeyNames[KeyCode::Up] = "Up Arrow";
   inputConfig->KeyNames[KeyCode::Right] = "Right Arrow";
   inputConfig->KeyNames[KeyCode::Down] = "Down Arrow";
   inputConfig->KeyNames[KeyCode::Return] = "Enter";
   inputConfig->KeyNames[KeyCode::Space] = "Space Bar";
   inputConfig->KeyNames[KeyCode::Tab] = "Tab";
   inputConfig->KeyNames[KeyCode::A] = "A";
   inputConfig->KeyNames[KeyCode::B] = "B";
   inputConfig->KeyNames[KeyCode::X] = "X";
   inputConfig->KeyNames[KeyCode::Y] = "Y";
   inputConfig->KeyNames[KeyCode::NumPad1] = "1";
   inputConfig->KeyNames[KeyCode::NumPad2] = "2";
   inputConfig->KeyNames[KeyCode::NumPad3] = "3";
   inputConfig->KeyNames[KeyCode::NumPad4] = "4";
   inputConfig->KeyNames[KeyCode::F12] = "F12";

   // button names
   inputConfig->ButtonNames[GameButton::Left] = "Left";
   inputConfig->ButtonNames[GameButton::Up] = "Up";
   inputConfig->ButtonNames[GameButton::Right] = "Right";
   inputConfig->ButtonNames[GameButton::Down] = "Down";
   inputConfig->ButtonNames[GameButton::Start] = "Start";
   inputConfig->ButtonNames[GameButton::Select] = "Select";
   inputConfig->ButtonNames[GameButton::A] = "A";
   inputConfig->ButtonNames[GameButton::B] = "B";
   inputConfig->ButtonNames[GameButton::X] = "X";
   inputConfig->ButtonNames[GameButton::Y] = "Y";
   inputConfig->ButtonNames[GameButton::L1] = "L1";
   inputConfig->ButtonNames[GameButton::L2] = "L2";
   inputConfig->ButtonNames[GameButton::R1] = "R1";
   inputConfig->ButtonNames[GameButton::R2] = "R2";
   inputConfig->ButtonNames[GameButton::Diagnostics] = "Toggle Diagnostics";

   return inputConfig;
}

shared_ptr<PlayerConfig> BuildPlayerConfig()
{
   auto playerConfig = make_shared<PlayerConfig>();

   playerConfig->StartVelocityX = 0.;
   playerConfig->StartVelocityY = 0.;

   // this means at max velocity, it should take
   // 3 seconds to cross the arena horizontally
   playerConfig->MaxVelocity = 1444.;

   // this means it should take a third of a second
   // to go from 0 to max velocity
   playerConfig->AccelerationPerSecond = 4332.;

   playerConfig->StartDirection = Direction::Right;

   return playerConfig;
}

shared_ptr<ArenaConfig> BuildArenaConfig()
{
   auto arenaConfig = make_shared<ArenaConfig>();

   arenaConfig->Width = 4332.;
   arenaConfig->Height = 1872.;

   arenaConfig->PlayerStartX = arenaConfig->Width / 2.;
   arenaConfig->PlayerStartY = arenaConfig->Height / 2.;

   return arenaConfig;
}

shared_ptr<GameConfig> BuildGameConfig()
{
   auto config = make_shared<GameConfig>();

   config->FramesPerSecond = 60;

   config->RenderConfig = BuildConsoleRenderConfig();
   config->InputConfig = BuildKeyboardInputConfig();
   config->PlayerConfig = BuildPlayerConfig();
   config->ArenaConfig = BuildArenaConfig();

   return config;
}
