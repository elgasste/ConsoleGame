#pragma once

#include <vector>

#include "ConsolePixel.h"

namespace ConsoleGame
{
   struct ConsoleSprite
   {
      ConsoleSprite() :
         Width( 0 ),
         Height( 0 ) { }

      int Width;
      int Height;

      std::vector<ConsolePixel> Pixels;
   };
}
