#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class ConsoleBuffer;
   class ConsoleRenderDefs;
   class IGameInfoProvider;

   class PlayingStateConsoleRenderer : public IGameRenderer
   {
   public:
      PlayingStateConsoleRenderer( const std::shared_ptr<ConsoleBuffer> consoleBuffer,
                                   const std::shared_ptr<ConsoleRenderDefs> renderDefs,
                                   const std::shared_ptr<IGameInfoProvider> gameInfoProvider );

      void Render() override;

   private:
      void DrawArenaFence();
      void DrawPlayer();

   private:
      const std::shared_ptr<ConsoleBuffer> _consoleBuffer;
      const std::shared_ptr<ConsoleRenderDefs> _renderDefs;
      const std::shared_ptr<IGameInfoProvider> _gameInfoProvider;

      float _arenaCoordConverterX;
      float _arenaCoordConverterY;
   };
}
