#pragma once

#include <memory>

namespace ConsoleGame
{
   class IGameRenderDefs;
   class IGameInputDefs;
   class PlayerDefs;
   class ArenaDefs;

   class GameDefs
   {
   public:
      std::shared_ptr<IGameRenderDefs> RenderDefs;
      std::shared_ptr<IGameInputDefs> InputDefs;
      std::shared_ptr<PlayerDefs> PlayerDefs;
      std::shared_ptr<ArenaDefs> ArenaDefs;
   };
}
