#include <format>

#include "GameConsoleRenderer.h"
#include "ConsoleRenderConfig.h"
#include "IConsoleDrawer.h"
#include "IGameStateProvider.h"
#include "IGameEventAggregator.h"
#include "GameState.h"
#include "GameEvent.h"
#include "ConsoleColor.h"

using namespace std;
using namespace ConsoleGame;

GameConsoleRenderer::GameConsoleRenderer( const shared_ptr<ConsoleRenderConfig> renderConfig,
                                          const shared_ptr<IConsoleDrawer> consoleDrawer,
                                          const shared_ptr<IGameStateProvider> stateProvider,
                                          const shared_ptr<IGameRenderer> diagnosticsRenderer,
                                          const shared_ptr<IGameEventAggregator> eventAggregator )
   : _consoleDrawer( consoleDrawer ),
     _stateProvider( stateProvider ),
     _diagnosticsRenderer( diagnosticsRenderer ),
     _showDiagnostics( false ),
     _isCleaningUp( false )
{
   eventAggregator->RegisterEventHandler( GameEvent::Shutdown, std::bind( &GameConsoleRenderer::HandleQuitEvent, this ) );
   eventAggregator->RegisterEventHandler( GameEvent::ToggleDiagnostics, std::bind( &GameConsoleRenderer::HandleToggleDiagnosticsEvent, this ) );

   consoleDrawer->Initialize();
   consoleDrawer->SetDefaultForegroundColor( renderConfig->DefaultForegroundColor );
   consoleDrawer->SetDefaultBackgroundColor( renderConfig->DefaultBackgroundColor );
}

void GameConsoleRenderer::AddRendererForGameState( GameState state, shared_ptr<IGameRenderer> renderer )
{
   _stateRenderers[state] = renderer;
}

void GameConsoleRenderer::Render()
{
   if ( _isCleaningUp )
   {
      return;
   }

   _consoleDrawer->ClearDrawBuffer();

   _stateRenderers.at( _stateProvider->GetGameState() )->Render();

   if ( _showDiagnostics )
   {
      _diagnosticsRenderer->Render();
   }

   _consoleDrawer->FlipDrawBuffer();
}

void GameConsoleRenderer::HandleQuitEvent()
{
   _isCleaningUp = true;
   _consoleDrawer->CleanUp();
}

void GameConsoleRenderer::HandleToggleDiagnosticsEvent()
{
   _showDiagnostics = !_showDiagnostics;
}
