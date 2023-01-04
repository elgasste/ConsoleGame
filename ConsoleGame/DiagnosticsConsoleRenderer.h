#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class ConsoleBuffer;
   class IGameClock;
   class ConsoleRenderDefs;

   class DiagnosticsConsoleRenderer : public IGameRenderer
   {
   public:
      DiagnosticsConsoleRenderer( const std::shared_ptr<ConsoleBuffer> consoleBuffer,
                                  const std::shared_ptr<IGameClock> clock,
                                  const std::shared_ptr<ConsoleRenderDefs> renderDefs );

      void Render() override;

   private:
      const std::shared_ptr<ConsoleBuffer> _consoleBuffer;
      const std::shared_ptr<IGameClock> _clock;
      const std::shared_ptr<ConsoleRenderDefs> _renderDefs;
   };
}
