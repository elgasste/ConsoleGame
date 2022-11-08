#include <format>

#include "StartupStateConsoleRenderer.h"
#include "IConsoleDrawer.h"

using namespace std;
using namespace ConsoleGame;

StartupStateConsoleRenderer::StartupStateConsoleRenderer( const shared_ptr<IConsoleDrawer>& consoleDrawer )
   : _consoleDrawer( consoleDrawer )
{
}

void StartupStateConsoleRenderer::Render()
{
   _consoleDrawer->Draw( 2, 1, "Hi!" );

   _consoleDrawer->Draw( 2, 3, "Press any button to start the game!" );
}
