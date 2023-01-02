#include <string>
#include <format>

#include "StartupStateConsoleRenderer.h"
#include "IConsoleBuffer.h"
#include "ConsoleRenderDefs.h"
#include "KeyboardInputDefs.h"
#include "ConsoleColor.h"

using namespace std;
using namespace ConsoleGame;

StartupStateConsoleRenderer::StartupStateConsoleRenderer( const shared_ptr<IConsoleBuffer> consoleBuffer,
                                                          const shared_ptr<ConsoleRenderDefs> renderDefs,
                                                          const shared_ptr<KeyboardInputDefs> inputDefs ) :
   _consoleBuffer( consoleBuffer ),
   _renderDefs( renderDefs ),
   _inputDefs( inputDefs )
{
}

void StartupStateConsoleRenderer::Render()
{
   _consoleBuffer->SetDefaultBackgroundColor( ConsoleColor::DarkBlue );
   _consoleBuffer->SetDefaultForegroundColor( ConsoleColor::White );

   auto middleX = _renderDefs->ConsoleWidth / 2;

   _consoleBuffer->Draw( middleX - 26, 1, ".==================================================." );
   _consoleBuffer->Draw( middleX - 27, 2, "|          WELCOME TO (INSERT YOUR TITLE)!!          |" );
   _consoleBuffer->Draw( middleX - 26, 3, "`=================================================='" );

   _consoleBuffer->Draw( middleX - 30, 6, "They sky's the limit! Er, the console is the limit, I guess." );
   _consoleBuffer->Draw( middleX - 40, 7, "Just to get you started, here's a list of which keys are bound to which buttons:" );

   int top = 9;

   DrawKeyBindings( middleX, top );

   top += (int)_inputDefs->KeyMap.size() + 1;
   _consoleBuffer->Draw( middleX - 17, top, "Press any button to play the game!" );
   _consoleBuffer->Draw( middleX - 25, top + 1, "(remember, not every key is bound to a button....)" );
}

void StartupStateConsoleRenderer::DrawKeyBindings( int middleX, int top ) const
{
   auto leftOfMiddleX = middleX - 2;

   for ( auto const& [keyCode, mappedButton] : _inputDefs->KeyMap )
   {
      string keyString( format( "{0} Key", _inputDefs->KeyNames.at(keyCode) ) );
      string buttonString( format( "{0} Button", _inputDefs->ButtonNames.at(mappedButton) ) );

      _consoleBuffer->Draw( leftOfMiddleX - (int)keyString.length() - 2, top, format( "{0} -> {1}", keyString, buttonString ) );

      top++;
   }
}
