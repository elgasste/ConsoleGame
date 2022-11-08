#pragma once

#include <map>
#include <string>

namespace ConsoleGame
{
   enum class KeyCode;
   enum class GameButton;

   class GameInputConfig
   {
   public:
      std::map<KeyCode, GameButton> KeyMap;

      std::map<KeyCode, std::string> KeyNames;
      std::map<GameButton, std::string> ButtonNames;
   };
}
