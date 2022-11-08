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
#include "GameInputHandler.h"
#include "ConsoleDrawer.h"
#include "StartupStateConsoleRenderer.h"
#include "GameConsoleRenderer.h"
#include "GameRunner.h"
#include "GameState.h"
#include "ConsoleColor.h"

using namespace std;
using namespace ConsoleGame;

// MUFFINS: I suppose these configs should be loaded from files at some point,
// but at the very least they should all have default values, and those could
// probably be set in a class somewhere instead of in here.
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
   auto game = shared_ptr<Game>( new Game() );

   // input objects
   auto startupStateInputHandler = shared_ptr<StartupStateInputHandler>( new StartupStateInputHandler( keyboardInputReader, eventAggregator ) );
   auto inputHandler = shared_ptr<GameInputHandler>( new GameInputHandler( keyboardInputReader, game, eventAggregator ) );
   inputHandler->AddInputHandlerForGameState( GameState::Startup, startupStateInputHandler );

   // rendering objects
   auto consoleDrawer = shared_ptr<ConsoleDrawer>( new ConsoleDrawer( config->RenderConfig ) );
   auto diagnosticsRenderer = shared_ptr<DiagnosticsConsoleRenderer>( new DiagnosticsConsoleRenderer( consoleDrawer, clock, config->RenderConfig ) );
   auto startupStateConsoleRenderer = shared_ptr<StartupStateConsoleRenderer>( new StartupStateConsoleRenderer( consoleDrawer ) );
   auto consoleRenderer = shared_ptr<GameConsoleRenderer>( new GameConsoleRenderer( config->RenderConfig, consoleDrawer, game, diagnosticsRenderer, eventAggregator ) );
   consoleRenderer->AddRendererForGameState( GameState::Startup, startupStateConsoleRenderer );

   // game loop
   auto runner = shared_ptr<GameRunner>( new GameRunner( eventAggregator, clock, inputHandler, consoleRenderer ) );

   cout << " done!\nLet's goooo!\n";

   runner->Run();

   cout << "Thanks for playing, enjoy your burrito!\n";
}

shared_ptr<GameRenderConfig> BuildRenderConfig()
{
   auto renderConfig = make_shared<GameRenderConfig>();

   renderConfig->ConsoleWidth = 120;
   renderConfig->ConsoleHeight = 35;

   renderConfig->DefaultForegroundColor = ConsoleColor::White;
   renderConfig->DefaultBackgroundColor = ConsoleColor::DarkBlue;

   return renderConfig;
}

shared_ptr<GameInputConfig> BuildInputConfig()
{
   auto inputConfig = make_shared<GameInputConfig>();

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
