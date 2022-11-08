#include <string>
#include <format>

#include "StartupStateConsoleRenderer.h"
#include "IConsoleDrawer.h"
#include "GameRenderConfig.h"
#include "GameInputConfig.h"
#include "ConsoleColor.h"

using namespace std;
using namespace ConsoleGame;

StartupStateConsoleRenderer::StartupStateConsoleRenderer( const shared_ptr<IConsoleDrawer>& consoleDrawer,
                                                          const shared_ptr<GameRenderConfig>& renderConfig,
                                                          const shared_ptr<GameInputConfig>& inputConfig )
   : _consoleDrawer( consoleDrawer ),
     _renderConfig( renderConfig ),
     _inputConfig( inputConfig )
{
}

void StartupStateConsoleRenderer::Render()
{
   _consoleDrawer->SetDefaultBackgroundColor( ConsoleColor::DarkBlue );
   _consoleDrawer->SetDefaultForegroundColor( ConsoleColor::White );

   auto middleX = _renderConfig->ConsoleWidth / 2;

   _consoleDrawer->Draw( middleX - 26, 1, ".==================================================." );
   _consoleDrawer->Draw( middleX - 27, 2, "|          WELCOME TO (INSERT YOUR TITLE)!!          |" );
   _consoleDrawer->Draw( middleX - 26, 3, "`=================================================='" );

   _consoleDrawer->Draw( middleX - 30, 6, "They sky's the limit! Er, the console is the limit, I guess." );
   _consoleDrawer->Draw( middleX - 40, 7, "Just to get you started, here's a list of which keys are bound to which buttons:" );

   DrawKeyBindings( middleX, 9 );
}

void StartupStateConsoleRenderer::DrawKeyBindings( int middleX, int top ) const
{
   auto leftOfMiddleX = middleX - 2;

   for ( auto const& [keyCode, mappedButton] : _inputConfig->KeyMap )
   {
      string keyString( _inputConfig->KeyNames.at( keyCode ) );
      string buttonString( _inputConfig->ButtonNames.at( mappedButton ) );

      _consoleDrawer->Draw( leftOfMiddleX - (int)keyString.length() - 2, top, format( "{0} -> {1}", keyString, buttonString ) );

      top++;
   }
}
