#include <format>

#include "DiagnosticsConsoleRenderer.h"
#include "ConsoleBuffer.h"
#include "IFrameRateProvider.h"
#include "ConsoleRenderDefs.h"

#define DIAGNOSTICS_WIDTH 35

using namespace std;
using namespace ConsoleGame;

DiagnosticsConsoleRenderer::DiagnosticsConsoleRenderer( const shared_ptr<ConsoleBuffer> consoleBuffer,
                                                        const shared_ptr<IFrameRateProvider> frameRateProvider,
                                                        const shared_ptr<ConsoleRenderDefs> renderDefs ) :
   _consoleBuffer( consoleBuffer ),
   _frameRateProvider( frameRateProvider ),
   _renderDefs( renderDefs )
{
}

void DiagnosticsConsoleRenderer::Render()
{
   auto left = _renderDefs->ConsoleWidth - DIAGNOSTICS_WIDTH;

   auto elapsedSecondsString = format( " Elapsed seconds:    {0} ", _frameRateProvider->GetElapsedNanoseconds() / 1'000'000'000 );
   auto totalFramesString = format( " Total frames:       {0} ", _frameRateProvider->GetCurrentFrame() );
   auto framesPerSecondString = format( " Average frame rate: {0} ", _frameRateProvider->GetAverageFrameRate() );

   while ( elapsedSecondsString.length() < DIAGNOSTICS_WIDTH ) { elapsedSecondsString += ' '; }
   while ( totalFramesString.length() < DIAGNOSTICS_WIDTH ) { totalFramesString += ' '; }
   while ( framesPerSecondString.length() < DIAGNOSTICS_WIDTH ) { framesPerSecondString += ' '; }

   _consoleBuffer->Draw( left, 0, elapsedSecondsString, ConsoleColor::DarkGrey, ConsoleColor::Black );
   _consoleBuffer->Draw( left, 1, totalFramesString, ConsoleColor::DarkGrey, ConsoleColor::Black );
   _consoleBuffer->Draw( left, 2, framesPerSecondString, ConsoleColor::DarkGrey, ConsoleColor::Black );
}
