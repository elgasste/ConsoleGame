#pragma once

namespace ConsoleGame
{
   enum class KeyCode;

   class __declspec( novtable ) IKeyboard
   {
   public:
      virtual bool IsKeyDown( KeyCode keyCode ) const = 0;
   };
}
