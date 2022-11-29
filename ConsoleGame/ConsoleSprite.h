#pragma once

#include <vector>

#include "ConsolePixel.h"

namespace ConsoleGame
{
   struct ConsoleSprite
   {
      int Width = 0;
      int Height = 0;

      std::vector<ConsolePixel> Pixels;
   };
}
