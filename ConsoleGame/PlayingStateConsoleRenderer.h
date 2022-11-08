#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleDrawer;

   class PlayingStateConsoleRenderer : public IGameRenderer
   {
   public:
      PlayingStateConsoleRenderer( const std::shared_ptr<IConsoleDrawer>& consoleDrawer );

      void Render() override;

   private:
      const std::shared_ptr<IConsoleDrawer>& _consoleDrawer;
   };
}
