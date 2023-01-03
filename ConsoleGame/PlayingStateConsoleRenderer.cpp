#include "PlayingStateConsoleRenderer.h"
#include "IConsoleBuffer.h"
#include "ConsoleRenderDefs.h"
#include "IGameInfoProvider.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleBuffer> consoleBuffer,
                                                          const shared_ptr<ConsoleRenderDefs> renderDefs,
                                                          const shared_ptr<IGameInfoProvider> gameInfoProvider ) :
   _consoleBuffer( consoleBuffer ),
   _renderDefs( renderDefs ),
   _gameInfoProvider( gameInfoProvider ),
   _arenaCoordConverterX( renderDefs->ArenaCharWidth / gameInfoProvider->GetArenaWidth() ),
   _arenaCoordConverterY( renderDefs->ArenaCharHeight / gameInfoProvider->GetArenaHeight() )
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
   _consoleBuffer->Draw( _renderDefs->ArenaFenceX, _renderDefs->ArenaFenceY, ',');
   _consoleBuffer->Draw( _renderDefs->ArenaFenceX + _renderDefs->ArenaCharWidth + 1, _renderDefs->ArenaFenceY, '.' );
   _consoleBuffer->Draw( _renderDefs->ArenaFenceX, _renderDefs->ArenaFenceY + _renderDefs->ArenaCharHeight + 1, '\'' );
   _consoleBuffer->Draw( _renderDefs->ArenaFenceX + _renderDefs->ArenaCharWidth + 1, _renderDefs->ArenaFenceY + _renderDefs->ArenaCharHeight + 1, '\'' );

   // top and bottom fences
   for ( int left = _renderDefs->ArenaFenceX; left < _renderDefs->ArenaCharWidth + 1; left++ )
   {
      _consoleBuffer->Draw( left + 1, _renderDefs->ArenaFenceY, '-' );
      _consoleBuffer->Draw( left + 1, _renderDefs->ArenaFenceY + _renderDefs->ArenaCharHeight + 1, '-' );
   }

   // side fences
   for ( int top = _renderDefs->ArenaFenceY + 1; top < _renderDefs->ArenaFenceY + _renderDefs->ArenaCharHeight + 1; top++ )
   {
      _consoleBuffer->Draw( _renderDefs->ArenaFenceX, top, '|' );
      _consoleBuffer->Draw( _renderDefs->ArenaFenceX + _renderDefs->ArenaCharWidth + 1, top, '|' );
   }
}

void PlayingStateConsoleRenderer::DrawPlayer()
{
   auto convertedPlayerX = (short)( _gameInfoProvider->GetArenaPlayerXPosition() * _arenaCoordConverterX );
   auto convertedPlayerY = (short)( _gameInfoProvider->GetArenaPlayerYPosition() * _arenaCoordConverterY );

   auto playerX = convertedPlayerX + _renderDefs->ArenaFenceX + 1;
   auto playerY = convertedPlayerY + _renderDefs->ArenaFenceY + 1;

   if ( !_gameInfoProvider->IsPlayerMoving() )
   {
      _consoleBuffer->Draw( playerX, playerY, _renderDefs->PlayerStaticSprite );
      return;
   }

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

   _consoleBuffer->Draw( playerX + spriteOffsetX, playerY + spriteOffsetY, _renderDefs->PlayerMovingSpriteMap[direction] );
}
