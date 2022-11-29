#pragma once

namespace ConsoleGame
{
   enum class ConsoleColor;

   struct ConsolePixel
   {
      char Value = '\0';
      ConsoleColor Color = (ConsoleColor)0;
   };
}
