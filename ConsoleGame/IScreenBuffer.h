#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IScreenBuffer
   {
   public:
      virtual void Initialize() = 0;
      virtual void CleanUp() = 0;

      virtual void Clear() = 0;
      virtual void Flip() = 0;
   };
}
