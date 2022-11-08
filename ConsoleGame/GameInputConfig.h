#pragma once

#include <map>

namespace ConsoleGame
{
   enum class KeyCode;
   enum class GameButton;

   class GameInputConfig
   {
   public:
      std::map<KeyCode, GameButton> KeyMap;
   };
}
