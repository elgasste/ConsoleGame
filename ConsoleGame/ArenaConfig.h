#pragma once

namespace ConsoleGame
{
   class ArenaConfig
   {
   public:
      ArenaConfig() :
         Width( 0 ),
         Height( 0 ),
         PlayerStartX( 0 ),
         PlayerStartY( 0 ) { }

      double Width;
      double Height;

      double PlayerStartX;
      double PlayerStartY;
   };
}
