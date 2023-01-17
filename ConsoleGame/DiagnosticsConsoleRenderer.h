#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class ConsoleBuffer;
   class IFrameRateProvider;
   class ConsoleRenderDefs;

   class DiagnosticsConsoleRenderer : public IGameRenderer
   {
   public:
      DiagnosticsConsoleRenderer( const std::shared_ptr<ConsoleBuffer> consoleBuffer,
                                  const std::shared_ptr<IFrameRateProvider> frameRateProvider,
                                  const std::shared_ptr<ConsoleRenderDefs> renderDefs );

      void Render() override;

   private:
      const std::shared_ptr<ConsoleBuffer> _consoleBuffer;
      const std::shared_ptr<IFrameRateProvider> _frameRateProvider;
      const std::shared_ptr<ConsoleRenderDefs> _renderDefs;
   };
}
