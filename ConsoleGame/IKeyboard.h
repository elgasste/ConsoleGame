#pragma once

#include "KeyCode.h"

namespace ConsoleGame
{
   class __declspec( novtable ) IKeyboard
   {
   public:
      virtual bool IsKeyDown( KeyCode keyCode ) const = 0;
   };
}
