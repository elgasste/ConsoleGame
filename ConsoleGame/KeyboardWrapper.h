#pragma once

#include "IKeyboard.h"

namespace ConsoleGame
{
   class KeyboardWrapper : public IKeyboard
   {
   public:
      bool IsKeyDown( KeyCode keyCode ) const override;
   };
}
