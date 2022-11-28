#pragma once

#include <map>

#include "IGameRenderConfig.h"
#include "ConsoleSprite.h"

namespace ConsoleGame
{
   enum class ConsoleColor;
   enum class Direction;

   class ConsoleRenderConfig : public IGameRenderConfig
   {
   public:
      ConsoleRenderConfig() :
         ConsoleWidth( 0 ),
         ConsoleHeight( 0 ),
         ArenaCharWidth( 0 ),
         ArenaCharHeight( 0 ),
         ArenaFenceX( 0 ),
         ArenaFenceY( 0 ),
         DefaultForegroundColor( (ConsoleColor)0 ),
         DefaultBackgroundColor( (ConsoleColor)0 ) { }

      short ConsoleWidth;
      short ConsoleHeight;

      short ArenaCharWidth;
      short ArenaCharHeight;

      short ArenaFenceX;
      short ArenaFenceY;

      ConsoleColor DefaultForegroundColor;
      ConsoleColor DefaultBackgroundColor;

      ConsoleSprite PlayerStaticSprite;
      std::map<Direction, ConsoleSprite> PlayerMovingSpriteMap;
   };
}
