#include "PlayingStateConsoleRenderer.h"
#include "IConsoleDrawer.h"
#include "GameRenderConfig.h"
#include "IPlayerInfoProvider.h"
#include "ConsoleColor.h"
#include "Direction.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleDrawer>& consoleDrawer,
                                                          const shared_ptr<GameRenderConfig>& renderConfig,
                                                          const shared_ptr<IPlayerInfoProvider>& playerInfoProvider )
   : _consoleDrawer( consoleDrawer ),
     _renderConfig( renderConfig ),
     _playerInfoProvider( playerInfoProvider )
{
}

void PlayingStateConsoleRenderer::Render()
{
   _consoleDrawer->SetDefaultBackgroundColor( ConsoleColor::DarkGrey );
   _consoleDrawer->SetDefaultForegroundColor( ConsoleColor::White );

   auto playerChar = GetPlayerCharFromDirection( _playerInfoProvider->GetPlayerDirection() );
   _consoleDrawer->Draw( _playerInfoProvider->GetPlayerXPosition(), _playerInfoProvider->GetPlayerYPosition(), playerChar );
}

char PlayingStateConsoleRenderer::GetPlayerCharFromDirection( Direction direction )
{
   switch ( direction )
   {
      case Direction::Left:
         return '<';
      case Direction::Up:
         return '^';
      case Direction::Right:
         return '>';
      case Direction::Down:
         return 'V';

      default:
         return 'X';
   }
}
