#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleBuffer;
   class ConsoleRenderDefs;
   class KeyboardInputConfig;

   class StartupStateConsoleRenderer : public IGameRenderer
   {
   public:
      StartupStateConsoleRenderer( const std::shared_ptr<IConsoleBuffer> consoleBuffer,
                                   const std::shared_ptr<ConsoleRenderDefs> renderDefs,
                                   const std::shared_ptr<KeyboardInputConfig> inputConfig );

      void Render() override;

   private:
      void DrawKeyBindings( int middleX, int top ) const;

   private:
      const std::shared_ptr<IConsoleBuffer> _consoleBuffer;
      const std::shared_ptr<ConsoleRenderDefs> _renderDefs;
      const std::shared_ptr<KeyboardInputConfig> _inputConfig;
   };
}
