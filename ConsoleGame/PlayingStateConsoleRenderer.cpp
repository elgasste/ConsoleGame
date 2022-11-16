#include "PlayingStateConsoleRenderer.h"
#include "IConsoleDrawer.h"
#include "ConsoleRenderConfig.h"
#include "GameConfig.h"
#include "IPlayerInfoProvider.h"
#include "ConsoleColor.h"
#include "Direction.h"
#include "ConsoleSprite.h"
#include "ConsolePixel.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleDrawer> consoleDrawer,
                                                          const shared_ptr<ConsoleRenderConfig> renderConfig,
                                                          const shared_ptr<GameConfig> gameConfig,
                                                          const shared_ptr<IPlayerInfoProvider> playerInfoProvider )
   : _consoleDrawer( consoleDrawer ),
     _renderConfig( renderConfig ),
     _gameConfig( gameConfig ),
     _playerInfoProvider( playerInfoProvider )
{
}

void PlayingStateConsoleRenderer::Render()
{
   _consoleDrawer->SetDefaultBackgroundColor( ConsoleColor::DarkGrey );
   _consoleDrawer->SetDefaultForegroundColor( ConsoleColor::White );

   _consoleDrawer->Draw( 2, 1, "Use the direction buttons to move around, or press the A button to quit." );

   DrawArenaFence();

   auto playerX = _playerInfoProvider->GetPlayerXPosition() + _renderConfig->ArenaFenceX + 1;
   auto playerY = _playerInfoProvider->GetPlayerYPosition() + _renderConfig->ArenaFenceY + 1;

   switch ( _playerInfoProvider->GetPlayerDirection() )
   {
      case Direction::Left:
         _consoleDrawer->Draw( playerX, playerY, _renderConfig->PlayerSpriteMap[Direction::Left] );
         break;
      case Direction::Up:
         _consoleDrawer->Draw( playerX, playerY, _renderConfig->PlayerSpriteMap[Direction::Up] );
         break;
      case Direction::Right:
         _consoleDrawer->Draw( playerX - 1, playerY, _renderConfig->PlayerSpriteMap[Direction::Right] );
         break;
      case Direction::Down:
         _consoleDrawer->Draw( playerX, playerY - 1, _renderConfig->PlayerSpriteMap[Direction::Down] );
         break;
   }
}

void PlayingStateConsoleRenderer::DrawArenaFence()
{
   // corners
   _consoleDrawer->Draw( _renderConfig->ArenaFenceX, _renderConfig->ArenaFenceY, ',');
   _consoleDrawer->Draw( _renderConfig->ArenaFenceX + _gameConfig->ArenaWidth + 1, _renderConfig->ArenaFenceY, '.' );
   _consoleDrawer->Draw( _renderConfig->ArenaFenceX, _renderConfig->ArenaFenceY + _gameConfig->ArenaHeight + 1, '\'' );
   _consoleDrawer->Draw( _renderConfig->ArenaFenceX + _gameConfig->ArenaWidth + 1, _renderConfig->ArenaFenceY + _gameConfig->ArenaHeight + 1, '\'' );

   // top and bottom fences
   for ( int left = _renderConfig->ArenaFenceX; left < _gameConfig->ArenaWidth + 2; left++ )
   {
      _consoleDrawer->Draw( left + 1, _renderConfig->ArenaFenceY, '-' );
      _consoleDrawer->Draw( left + 1, _renderConfig->ArenaFenceY + _gameConfig->ArenaHeight + 1, '-' );
   }

   // side fences
   for ( int top = _renderConfig->ArenaFenceY + 1; top < _renderConfig->ArenaFenceY + _gameConfig->ArenaHeight + 1; top++ )
   {
      _consoleDrawer->Draw( _renderConfig->ArenaFenceX, top, '|' );
      _consoleDrawer->Draw( _renderConfig->ArenaFenceX + _gameConfig->ArenaWidth + 2, top, '|' );
   }
}
