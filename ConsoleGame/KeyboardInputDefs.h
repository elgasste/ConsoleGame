#pragma once

#include <map>
#include <string>

#include "IGameInputDefs.h"
#include "KeyCode.h"
#include "GameButton.h"

namespace ConsoleGame
{
   class KeyboardInputDefs : public IGameInputDefs
   {
   public:
      std::map<KeyCode, GameButton> KeyMap;

      std::map<KeyCode, std::string> KeyNames;
      std::map<GameButton, std::string> ButtonNames;
   };
}
