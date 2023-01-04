#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class ConsoleBuffer;
   class ConsoleRenderDefs;
   class KeyboardInputDefs;

   class StartupStateConsoleRenderer : public IGameRenderer
   {
   public:
      StartupStateConsoleRenderer( const std::shared_ptr<ConsoleBuffer> consoleBuffer,
                                   const std::shared_ptr<ConsoleRenderDefs> renderDefs,
                                   const std::shared_ptr<KeyboardInputDefs> inputDefs );

      void Render() override;

   private:
      void DrawKeyBindings( int middleX, int top ) const;

   private:
      const std::shared_ptr<ConsoleBuffer> _consoleBuffer;
      const std::shared_ptr<ConsoleRenderDefs> _renderDefs;
      const std::shared_ptr<KeyboardInputDefs> _inputDefs;
   };
}
