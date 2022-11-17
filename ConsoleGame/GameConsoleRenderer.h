#pragma once

#include <memory>
#include <map>

#include "IGameRenderer.h"
#include "GameEvent.h"

namespace ConsoleGame
{
   class ConsoleRenderConfig;
   class IConsoleDrawer;
   class IGameStateProvider;
   class IGameEventAggregator;
   enum class GameState;
   enum class GameEvent;

   class GameConsoleRenderer : public IGameRenderer
   {
   public:
      GameConsoleRenderer( const std::shared_ptr<ConsoleRenderConfig> renderConfig,
                           const std::shared_ptr<IConsoleDrawer> consoleDrawer,
                           const std::shared_ptr<IGameStateProvider> stateProvider,
                           const std::shared_ptr<IGameRenderer> diagnosticsRenderer,
                           const std::shared_ptr<IGameEventAggregator> eventAggregator );

      void AddRendererForGameState( GameState state, std::shared_ptr<IGameRenderer> renderer );

      void Render() override;

   private:
      void HandleQuitEvent();
      void HandleToggleDiagnosticsEvent();

   private:
      const std::shared_ptr<IConsoleDrawer> _consoleDrawer;
      const std::shared_ptr<IGameStateProvider> _stateProvider;
      const std::shared_ptr<IGameRenderer> _diagnosticsRenderer;

      std::map<GameState, std::shared_ptr<IGameRenderer>> _stateRenderers;

      bool _showDiagnostics;
      bool _isCleaningUp;
   };
}
