#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleBuffer;
   class ConsoleRenderConfig;
   class IGameInfoProvider;

   class PlayingStateConsoleRenderer : public IGameRenderer
   {
   public:
      PlayingStateConsoleRenderer( const std::shared_ptr<IConsoleBuffer> consoleBuffer,
                                   const std::shared_ptr<ConsoleRenderConfig> renderConfig,
                                   const std::shared_ptr<IGameInfoProvider> gameInfoProvider );

      void Render() override;

   private:
      void DrawArenaFence();

   private:
      const std::shared_ptr<IConsoleBuffer> _consoleBuffer;
      const std::shared_ptr<ConsoleRenderConfig> _renderConfig;
      const std::shared_ptr<IGameInfoProvider> _gameInfoProvider;

      double _arenaCoordConverterX;
      double _arenaCoordConverterY;
   };
}
