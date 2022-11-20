#include "PlayingStateConsoleRenderer.h"
#include "IConsoleBuffer.h"
#include "ConsoleRenderConfig.h"
#include "IGameInfoProvider.h"
#include "ConsoleColor.h"
#include "Direction.h"
#include "ConsoleSprite.h"
#include "ConsolePixel.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleBuffer> consoleBuffer,
                                                          const shared_ptr<ConsoleRenderConfig> renderConfig,
                                                          const shared_ptr<IGameInfoProvider> gameInfoProvider ) :
   _consoleBuffer( consoleBuffer ),
   _renderConfig( renderConfig ),
   _gameInfoProvider( gameInfoProvider ),
   _arenaCoordConverterX( renderConfig->ArenaCharWidth / (double)gameInfoProvider->GetArenaWidth() ),
   _arenaCoordConverterY( renderConfig->ArenaCharHeight / (double)gameInfoProvider->GetArenaHeight() )
{
}

void PlayingStateConsoleRenderer::Render()
{
   _consoleBuffer->SetDefaultBackgroundColor( ConsoleColor::DarkGrey );
   _consoleBuffer->SetDefaultForegroundColor( ConsoleColor::White );

   _consoleBuffer->Draw( 2, 1, "Use the direction buttons to move around, or press the A button to quit." );

   DrawArenaFence();
   DrawPlayer();
}

void PlayingStateConsoleRenderer::DrawArenaFence()
{
   // corners
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX, _renderConfig->ArenaFenceY, ',');
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _renderConfig->ArenaCharWidth + 1, _renderConfig->ArenaFenceY, '.' );
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX, _renderConfig->ArenaFenceY + _renderConfig->ArenaCharHeight + 1, '\'' );
   _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _renderConfig->ArenaCharWidth + 1, _renderConfig->ArenaFenceY + _renderConfig->ArenaCharHeight + 1, '\'' );

   // top and bottom fences
   for ( int left = _renderConfig->ArenaFenceX; left < _renderConfig->ArenaCharWidth + 1; left++ )
   {
      _consoleBuffer->Draw( left + 1, _renderConfig->ArenaFenceY, '-' );
      _consoleBuffer->Draw( left + 1, _renderConfig->ArenaFenceY + _renderConfig->ArenaCharHeight + 1, '-' );
   }

   // side fences
   for ( int top = _renderConfig->ArenaFenceY + 1; top < _renderConfig->ArenaFenceY + _renderConfig->ArenaCharHeight + 1; top++ )
   {
      _consoleBuffer->Draw( _renderConfig->ArenaFenceX, top, '|' );
      _consoleBuffer->Draw( _renderConfig->ArenaFenceX + _renderConfig->ArenaCharWidth + 1, top, '|' );
   }
}

void PlayingStateConsoleRenderer::DrawPlayer()
{
   auto convertedPlayerX = (short)( _gameInfoProvider->GetArenaPlayerXPosition() * _arenaCoordConverterX );
   auto convertedPlayerY = (short)( _gameInfoProvider->GetArenaPlayerYPosition() * _arenaCoordConverterY );

   auto playerX = convertedPlayerX + _renderConfig->ArenaFenceX + 1;
   auto playerY = convertedPlayerY + _renderConfig->ArenaFenceY + 1;

   int spriteOffsetX = 0;
   int spriteOffsetY = 0;

   auto direction = _gameInfoProvider->GetPlayerDirection();

   switch ( direction )
   {
   case Direction::UpRight:
   case Direction::Right:
      spriteOffsetX = -1;
      break;
   case Direction::Down:
   case Direction::DownLeft:
      spriteOffsetY = -1;
      break;
   case Direction::DownRight:
      spriteOffsetX = -1;
      spriteOffsetY = -1;
      break;
   }

   _consoleBuffer->Draw( playerX + spriteOffsetX, playerY + spriteOffsetY, _renderConfig->PlayerMovingSpriteMap[direction] );
}
