#include "PlayingStateConsoleRenderer.h"
#include "IConsoleDrawer.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleDrawer>& consoleDrawer )
   : _consoleDrawer( consoleDrawer )
{
}

void PlayingStateConsoleRenderer::Render()
{
   _consoleDrawer->Draw( 2, 1, "The game has started, let's gooooooo!" );

   _consoleDrawer->Draw( 2, 3, "(when you're done \"playing\", press A to get out of here)" );
}
