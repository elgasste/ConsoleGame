#include <iostream>

#include "GameConfig.h"
#include "ConsoleRenderConfig.h"
#include "KeyboardInputConfig.h"
#include "PlayerConfig.h"
#include "KeyCode.h"
#include "GameButton.h"
#include "HighResolutionClockWrapper.h"
#include "SleeperWrapper.h"
#include "KeyboardWrapper.h"
#include "GameEventAggregator.h"
#include "GameClock.h"
#include "KeyboardInputReader.h"
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
#include "ConsoleSprite.h"

using namespace std;
using namespace ConsoleGame;

// TODO: I suppose these configs should be loaded from files at some point,
// but at the very least they should all have default values, and those could
// probably be set in some initializer instead of in here.
shared_ptr<ConsoleRenderConfig> BuildConsoleRenderConfig();
shared_ptr<KeyboardInputConfig> BuildKeyboardInputConfig();
shared_ptr<PlayerConfig> BuildPlayerConfig();
shared_ptr<GameConfig> BuildGameConfig();

int main()
{
   cout << "Loading all the things...";

   // configs
   auto config = BuildGameConfig();
   auto consoleRenderConfig = static_pointer_cast<ConsoleRenderConfig>( config->RenderConfig );
   auto keyboardInputConfig = static_pointer_cast<KeyboardInputConfig>( config->InputConfig );

   // wrappers
   auto highResolutionClock = shared_ptr<HighResolutionClockWrapper>( new HighResolutionClockWrapper() );
   auto sleeper = shared_ptr<SleeperWrapper>( new SleeperWrapper() );
   auto keyboard = shared_ptr<IKeyboard>( new KeyboardWrapper() );

   // auxiliary objects
   auto eventAggregator = shared_ptr<GameEventAggregator>( new GameEventAggregator() );
   auto clock = shared_ptr<GameClock>( new GameClock( highResolutionClock, sleeper, config->FramesPerSecond ) );
   auto keyboardInputReader = shared_ptr<KeyboardInputReader>( new KeyboardInputReader( keyboardInputConfig, keyboard ) );

   // game data objects
   auto game = shared_ptr<Game>( new Game( config, eventAggregator ) );

   // input objects
   auto startupStateInputHandler = shared_ptr<StartupStateInputHandler>( new StartupStateInputHandler( keyboardInputReader, game ) );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( keyboardInputReader, game ) );
   auto inputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( keyboardInputReader, game, eventAggregator ) );
   inputHandler->AddInputHandlerForGameState( GameState::Startup, startupStateInputHandler );
   inputHandler->AddInputHandlerForGameState( GameState::Playing, playingStateInputHandler );

   // rendering objects
   auto consoleBuffer = shared_ptr<ConsoleBuffer>( new ConsoleBuffer( consoleRenderConfig ) );
   auto diagnosticsRenderer = shared_ptr<DiagnosticsConsoleRenderer>( new DiagnosticsConsoleRenderer( consoleBuffer, clock, consoleRenderConfig ) );
   auto startupStateConsoleRenderer = shared_ptr<StartupStateConsoleRenderer>( new StartupStateConsoleRenderer( consoleBuffer, consoleRenderConfig, keyboardInputConfig ) );
   auto playingStateConsoleRenderer = shared_ptr<PlayingStateConsoleRenderer>( new PlayingStateConsoleRenderer( consoleBuffer, consoleRenderConfig, game ) );
   auto renderer = shared_ptr<GameRenderer>( new GameRenderer( consoleRenderConfig, consoleBuffer, game, diagnosticsRenderer, eventAggregator ) );
   renderer->AddRendererForGameState( GameState::Startup, startupStateConsoleRenderer );
   renderer->AddRendererForGameState( GameState::Playing, playingStateConsoleRenderer );

   // game loop
   auto runner = shared_ptr<GameRunner>( new GameRunner( eventAggregator, clock, inputHandler, renderer ) );

   cout << " done!\nLet's goooo!\n";

   runner->Run();

   cout << "Thanks for playing, enjoy your burrito!\n";
}

shared_ptr<ConsoleRenderConfig> BuildConsoleRenderConfig()
{
   auto renderConfig = make_shared<ConsoleRenderConfig>();

   // TODO: don't change these dimensions until we figure out the issue with console resizing.
   // (see ConsoleDrawer.cpp)
   renderConfig->ConsoleWidth = 120;
   renderConfig->ConsoleHeight = 30;

   renderConfig->ArenaCharWidth = 114;
   renderConfig->ArenaCharHeight = 24;

   renderConfig->ArenaFenceX = 2;
   renderConfig->ArenaFenceY = 3;

   renderConfig->DefaultForegroundColor = ConsoleColor::Grey;
   renderConfig->DefaultBackgroundColor = ConsoleColor::Black;

   renderConfig->PlayerSpriteMap[Direction::Left].Width = 2;
   renderConfig->PlayerSpriteMap[Direction::Left].Height = 1;
   renderConfig->PlayerSpriteMap[Direction::Left].Pixels.push_back( { 'L', ConsoleColor::White } );
   renderConfig->PlayerSpriteMap[Direction::Left].Pixels.push_back( { '-', ConsoleColor::White } );

   renderConfig->PlayerSpriteMap[Direction::Right].Width = 2;
   renderConfig->PlayerSpriteMap[Direction::Right].Height = 1;
   renderConfig->PlayerSpriteMap[Direction::Right].Pixels.push_back( { '-', ConsoleColor::White } );
   renderConfig->PlayerSpriteMap[Direction::Right].Pixels.push_back( { 'R', ConsoleColor::White } );

   renderConfig->PlayerSpriteMap[Direction::Up].Width = 1;
   renderConfig->PlayerSpriteMap[Direction::Up].Height = 2;
   renderConfig->PlayerSpriteMap[Direction::Up].Pixels.push_back( { 'U', ConsoleColor::White } );
   renderConfig->PlayerSpriteMap[Direction::Up].Pixels.push_back( { '|', ConsoleColor::White } );

   renderConfig->PlayerSpriteMap[Direction::Down].Width = 1;
   renderConfig->PlayerSpriteMap[Direction::Down].Height = 2;
   renderConfig->PlayerSpriteMap[Direction::Down].Pixels.push_back( { '|', ConsoleColor::White } );
   renderConfig->PlayerSpriteMap[Direction::Down].Pixels.push_back( { 'D', ConsoleColor::White } );

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

   playerConfig->StartVelocityX = 0;
   playerConfig->StartVelocityY = 0;

   playerConfig->MaxVelocityX = 1;
   playerConfig->MaxVelocityY = 1;

   playerConfig->VelocityDeltaX = 1;
   playerConfig->VelocityDeltaY = 1;

   playerConfig->StartDirection = Direction::Right;

   return playerConfig;
}

shared_ptr<GameConfig> BuildGameConfig()
{
   auto config = make_shared<GameConfig>();
   auto consoleRenderConfig = BuildConsoleRenderConfig();
   auto keyboardInputConfig = BuildKeyboardInputConfig();
   auto playerConfig = BuildPlayerConfig();

   config->FramesPerSecond = 60;

   config->ArenaWidth = consoleRenderConfig->ArenaCharWidth;
   config->ArenaHeight = consoleRenderConfig->ArenaCharHeight;

   config->PlayerStartX = config->ArenaWidth / 2;
   config->PlayerStartY = config->ArenaHeight / 2;

   config->RenderConfig = consoleRenderConfig;
   config->InputConfig = keyboardInputConfig;
   config->PlayerConfig = playerConfig;

   return config;
}
