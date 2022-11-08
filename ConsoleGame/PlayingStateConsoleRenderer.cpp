#include "PlayingStateConsoleRenderer.h"
#include "IConsoleDrawer.h"
#include "ConsoleColor.h"

using namespace std;
using namespace ConsoleGame;

PlayingStateConsoleRenderer::PlayingStateConsoleRenderer( const shared_ptr<IConsoleDrawer>& consoleDrawer )
   : _consoleDrawer( consoleDrawer )
{
}

void PlayingStateConsoleRenderer::Render()
{
   _consoleDrawer->SetDefaultBackgroundColor( ConsoleColor::DarkGrey );
   _consoleDrawer->SetDefaultForegroundColor( ConsoleColor::White );

   _consoleDrawer->Draw( 2, 1, "The game has started, let's gooooooo!" );

   _consoleDrawer->Draw( 2, 3, "(when you're done \"playing\", press the A button to get out of here)" );
}
