#include <iostream>

#include "GameConfig.h"
#include "GameRenderConfig.h"
#include "GameInputConfig.h"
#include "KeyCode.h"
#include "GameButton.h"
#include "GameEventAggregator.h"
#include "GameClock.h"
#include "KeyboardInputReader.h"
#include "Game.h"
#include "DiagnosticsConsoleRenderer.h"
#include "StartupStateInputHandler.h"
#include "PlayingStateInputHandler.h"
#include "GameInputHandler.h"
#include "ConsoleDrawer.h"
#include "StartupStateConsoleRenderer.h"
#include "PlayingStateConsoleRenderer.h"
#include "GameConsoleRenderer.h"
#include "GameRunner.h"
#include "GameState.h"
#include "ConsoleColor.h"

using namespace std;
using namespace ConsoleGame;

// TODO: I suppose these configs should be loaded from files at some point,
// but at the very least they should all have default values, and those could
// probably be set in some initializer instead of in here.
shared_ptr<GameRenderConfig> BuildRenderConfig();
shared_ptr<GameInputConfig> BuildInputConfig();
shared_ptr<GameConfig> BuildGameConfig();

int main()
{
   cout << "Loading all the things...";

   auto config = BuildGameConfig();

   // auxiliary objects
   auto eventAggregator = shared_ptr<GameEventAggregator>( new GameEventAggregator() );
   auto clock = shared_ptr<GameClock>( new GameClock( config->FramesPerSecond ) );
   auto keyboardInputReader = shared_ptr<KeyboardInputReader>( new KeyboardInputReader( config->InputConfig ) );

   // game data objects
   auto game = shared_ptr<Game>( new Game( eventAggregator ) );

   // input objects
   auto startupStateInputHandler = shared_ptr<StartupStateInputHandler>( new StartupStateInputHandler( keyboardInputReader, game ) );
   auto playingStateInputHandler = shared_ptr<PlayingStateInputHandler>( new PlayingStateInputHandler( keyboardInputReader, game ) );
   auto inputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( keyboardInputReader, game, eventAggregator ) );
   inputHandler->AddInputHandlerForGameState( GameState::Startup, startupStateInputHandler );
   inputHandler->AddInputHandlerForGameState( GameState::Playing, playingStateInputHandler );

   // rendering objects
   auto consoleDrawer = shared_ptr<ConsoleDrawer>( new ConsoleDrawer( config->RenderConfig ) );
   auto diagnosticsRenderer = shared_ptr<DiagnosticsConsoleRenderer>( new DiagnosticsConsoleRenderer( consoleDrawer, clock, config->RenderConfig ) );
   auto startupStateConsoleRenderer = shared_ptr<StartupStateConsoleRenderer>( new StartupStateConsoleRenderer( consoleDrawer, config->RenderConfig, config->InputConfig ) );
   auto playingStateConsoleRenderer = shared_ptr<PlayingStateConsoleRenderer>( new PlayingStateConsoleRenderer( consoleDrawer ) );
   auto consoleRenderer = shared_ptr<GameConsoleRenderer>( new GameConsoleRenderer( config->RenderConfig, consoleDrawer, game, diagnosticsRenderer, eventAggregator ) );
   consoleRenderer->AddRendererForGameState( GameState::Startup, startupStateConsoleRenderer );
   consoleRenderer->AddRendererForGameState( GameState::Playing, playingStateConsoleRenderer );

   // game loop
   auto runner = shared_ptr<GameRunner>( new GameRunner( eventAggregator, clock, inputHandler, consoleRenderer ) );

   cout << " done!\nLet's goooo!\n";

   runner->Run();

   cout << "Thanks for playing, enjoy your burrito!\n";
}

shared_ptr<GameRenderConfig> BuildRenderConfig()
{
   auto renderConfig = make_shared<GameRenderConfig>();

   // TODO: don't change these dimensions until we figure out the issue with console resizing.
   // (see ConsoleDrawer.cpp)
   renderConfig->ConsoleWidth = 120;
   renderConfig->ConsoleHeight = 30;

   renderConfig->DefaultForegroundColor = ConsoleColor::Grey;
   renderConfig->DefaultBackgroundColor = ConsoleColor::Black;

   return renderConfig;
}

shared_ptr<GameInputConfig> BuildInputConfig()
{
   auto inputConfig = make_shared<GameInputConfig>();

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

shared_ptr<GameConfig> BuildGameConfig()
{
   auto config = make_shared<GameConfig>();

   config->FramesPerSecond = 60;
   config->RenderConfig = BuildRenderConfig();
   config->InputConfig = BuildInputConfig();

   return config;
}
