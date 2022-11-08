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

   _consoleDrawer->Draw( 2, 3, "Press F12 to toggle diagnostics, or press A to get out of here!" );
}
