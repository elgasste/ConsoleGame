#include "PlayingStateConsoleRenderer.h"
#include "IConsoleDrawer.h"
#include "GameRenderConfig.h"
#include "GameConfig.h"
#include "IPlayerInfoProvider.h"
#include "ConsoleColor.h"
#include "Direction.h"
#include "ConsoleSprite.h"
#include "ConsolePixel.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleDrawer> consoleDrawer,
                                                          const shared_ptr<GameRenderConfig> renderConfig,
                                                          const shared_ptr<GameConfig> gameConfig,
                                                          const shared_ptr<IPlayerInfoProvider> playerInfoProvider )
   : _consoleDrawer( consoleDrawer ),
     _renderConfig( renderConfig ),
     _gameConfig( gameConfig ),
     _playerInfoProvider( playerInfoProvider )
{
   auto leftSprite = shared_ptr<ConsoleSprite>( new ConsoleSprite );
   leftSprite->Width = 2;
   leftSprite->Height = 1;
   leftSprite->Pixels.push_back( { 'L', ConsoleColor::White } );
   leftSprite->Pixels.push_back( { '-', ConsoleColor::White } );

   auto rightSprite = shared_ptr<ConsoleSprite>( new ConsoleSprite );
   rightSprite->Width = 2;
   rightSprite->Height = 1;
   rightSprite->Pixels.push_back( { '-', ConsoleColor::White } );
   rightSprite->Pixels.push_back( { 'R', ConsoleColor::White } );

   auto upSprite = shared_ptr<ConsoleSprite>( new ConsoleSprite );
   upSprite->Width = 1;
   upSprite->Height = 2;
   upSprite->Pixels.push_back( { 'U', ConsoleColor::White } );
   upSprite->Pixels.push_back( { '|', ConsoleColor::White } );

   auto downSprite = shared_ptr<ConsoleSprite>( new ConsoleSprite );
   downSprite->Width = 1;
   downSprite->Height = 2;
   downSprite->Pixels.push_back( { '|', ConsoleColor::White } );
   downSprite->Pixels.push_back( { 'D', ConsoleColor::White } );

   _playerSpriteMap[Direction::Left] = leftSprite;
   _playerSpriteMap[Direction::Up] = upSprite;
   _playerSpriteMap[Direction::Right] = rightSprite;
   _playerSpriteMap[Direction::Down] = downSprite;
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
         _consoleDrawer->Draw( playerX, playerY, _playerSpriteMap[Direction::Left] );
         break;
      case Direction::Up:
         _consoleDrawer->Draw( playerX, playerY, _playerSpriteMap[Direction::Up] );
         break;
      case Direction::Right:
         _consoleDrawer->Draw( playerX - 1, playerY, _playerSpriteMap[Direction::Right] );
         break;
      case Direction::Down:
         _consoleDrawer->Draw( playerX, playerY - 1, _playerSpriteMap[Direction::Down] );
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
