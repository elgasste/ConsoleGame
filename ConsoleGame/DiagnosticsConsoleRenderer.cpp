#include <format>

#include "DiagnosticsConsoleRenderer.h"
#include "IConsoleDrawer.h"
#include "IGameClock.h"
#include "ConsoleRenderConfig.h"
#include "ConsoleColor.h"

#define DIAGNOSTICS_WIDTH 30

using namespace std;
using namespace ConsoleGame;

DiagnosticsConsoleRenderer::DiagnosticsConsoleRenderer( const shared_ptr<IConsoleDrawer> consoleDrawer,
                                                        const shared_ptr<IGameClock> clock,
                                                        const shared_ptr<ConsoleRenderConfig> renderConfig )
   : _consoleDrawer( consoleDrawer ),
     _clock( clock ),
     _renderConfig( renderConfig )
{
}

void DiagnosticsConsoleRenderer::Render()
{
   auto left = _renderConfig->ConsoleWidth - DIAGNOSTICS_WIDTH;

   auto framesPerSecondString = format( " Frames per second: {0} ", _clock->GetFramesPerSecond() );
   auto totalFramesString = format( " Total frames:      {0} ", _clock->GetTotalFrameCount() );
   auto lagFramesString = format( " Lag frames:        {0} ", _clock->GetLagFrameCount() );

   while ( framesPerSecondString.length() < DIAGNOSTICS_WIDTH ) { framesPerSecondString += ' '; }
   while ( totalFramesString.length() < DIAGNOSTICS_WIDTH ) { totalFramesString += ' '; }
   while ( lagFramesString.length() < DIAGNOSTICS_WIDTH ) { lagFramesString += ' '; }

   _consoleDrawer->Draw( left, 0, framesPerSecondString, ConsoleColor::DarkGrey, ConsoleColor::Black );
   _consoleDrawer->Draw( left, 1, totalFramesString, ConsoleColor::DarkGrey, ConsoleColor::Black );
   _consoleDrawer->Draw( left, 2, lagFramesString, ConsoleColor::DarkGrey, ConsoleColor::Black );
}
