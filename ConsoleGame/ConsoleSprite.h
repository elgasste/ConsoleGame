#pragma once

#include <vector>

#include "ConsolePixel.h"

namespace ConsoleGame
{
   struct ConsoleSprite
   {
      int Width;
      int Height;

      std::vector<ConsolePixel> Pixels;
   };
}
