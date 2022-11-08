#pragma once

#include <memory>

#include "IGameRenderer.h"

namespace ConsoleGame
{
   class IConsoleDrawer;

   class StartupStateConsoleRenderer : public IGameRenderer
   {
   public:
      StartupStateConsoleRenderer( const std::shared_ptr<IConsoleDrawer>& consoleDrawer );

      void Render() override;

   private:
   private:
      const std::shared_ptr<IConsoleDrawer>& _consoleDrawer;
   };
}
