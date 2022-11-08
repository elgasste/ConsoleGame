#include <format>

#include "StartupStateConsoleRenderer.h"
#include "IConsoleDrawer.h"
#include "GameRenderConfig.h"

using namespace std;
using namespace ConsoleGame;

StartupStateConsoleRenderer::StartupStateConsoleRenderer( const shared_ptr<IConsoleDrawer>& consoleDrawer,
                                                          const shared_ptr<GameRenderConfig>& renderConfig )
   : _consoleDrawer( consoleDrawer ),
     _renderConfig( renderConfig )
{
}

void StartupStateConsoleRenderer::Render()
{
   _consoleDrawer->Draw( 2, 1, "Hi!" );

   _consoleDrawer->Draw( 2, 3, "Press any button to start the game!" );
}
