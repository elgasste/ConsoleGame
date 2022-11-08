#include <format>

#include "ConsoleDrawer.h"
#include "GameRenderConfig.h"
#include "ConsoleColor.h"

using namespace std;
using namespace ConsoleGame;

ConsoleDrawer::ConsoleDrawer( const shared_ptr<GameRenderConfig>& renderConfig )
   : _renderConfig( renderConfig ),
     _outputHandle( GetStdHandle( STD_OUTPUT_HANDLE ) ),
     _consoleSize( { _renderConfig->ConsoleWidth, _renderConfig->ConsoleHeight } ),
     _drawBufferSize( _consoleSize.X * _consoleSize.Y ),
     _drawBuffer( new CHAR_INFO[_drawBufferSize] ),
     _outputRect( { 0, 0, _renderConfig->ConsoleWidth, _renderConfig->ConsoleHeight } ),
     _defaultForegroundColor( ConsoleColor::Grey ),
     _defaultBackgroundColor( ConsoleColor::Black )
{
   for ( int i = 0; i < _drawBufferSize; i++ )
   {
      _drawBuffer[i] = CHAR_INFO();
   }
}

ConsoleDrawer::~ConsoleDrawer()
{
   delete[] _drawBuffer;
}

void ConsoleDrawer::Initialize()
{
   // MUFFINS: maybe this is possible if we can get character size?
   //auto consoleHandle = GetConsoleWindow();
   //RECT consoleRect;
   //GetWindowRect( consoleHandle, &consoleRect );
   //MoveWindow( consoleHandle, consoleRect.left, consoleRect.top, 800, 600, TRUE );

   // MUFFINS: there HAS to be a better way to do this...
   system( format("MODE CON COLS={0} LINES={1}", _consoleSize.X, _consoleSize.Y ).c_str() );

   SetCursorVisibility( false );
   ClearDrawBuffer();
   FlipDrawBuffer();
}

void ConsoleDrawer::CleanUp()
{
   // MUFFINS: resize the window back to its original dimensions.
   // also, use the config to set default fg/bg colors, and restore them here as well.
   SetDefaultForegroundColor( ConsoleColor::Grey );
   SetDefaultBackgroundColor( ConsoleColor::Black );
   ClearDrawBuffer();
   FlipDrawBuffer();

   SetCursorVisibility( true );
   SetConsoleCursorPosition( _outputHandle, { 0, 0 } );
}

void ConsoleDrawer::SetDefaultForegroundColor( ConsoleColor color )
{
   _defaultForegroundColor = color;
}

void ConsoleDrawer::SetDefaultBackgroundColor( ConsoleColor color )
{
   _defaultBackgroundColor = color;
}

void ConsoleDrawer::ClearDrawBuffer()
{
   for ( int i = 0; i < _drawBufferSize; i++ )
   {
      _drawBuffer[i].Char.AsciiChar = 0x20;
      _drawBuffer[i].Attributes = ConsoleColorsToAttribute( _defaultForegroundColor, _defaultBackgroundColor );
   }
}

void ConsoleDrawer::Draw( int left, int top, char buffer )
{
   Draw( left, top, buffer, _defaultForegroundColor );
}

void ConsoleDrawer::Draw( int left, int top, char buffer, ConsoleColor foregroundColor )
{
   Draw( left, top, buffer, foregroundColor, _defaultBackgroundColor );
}

void ConsoleDrawer::Draw( int left, int top, char buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor )
{
   if ( left < 0 || left >= _consoleSize.X || top < 0 || top >= _consoleSize.Y )
   {
      return;
   }

   auto bufferLocation = left + ( top * _consoleSize.X );
   _drawBuffer[bufferLocation].Attributes = ConsoleColorsToAttribute( foregroundColor, backgroundColor );
   _drawBuffer[bufferLocation].Char.AsciiChar = buffer;
}

void ConsoleDrawer::Draw( int left, int top, const string& buffer )
{
   Draw( left, top, buffer, _defaultForegroundColor );
}

void ConsoleDrawer::Draw( int left, int top, const string& buffer, ConsoleColor foregroundColor )
{
   Draw( left, top, buffer, foregroundColor, _defaultBackgroundColor );
}

void ConsoleDrawer::Draw( int left, int top, const string& buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor )
{
   for ( int i = 0; i < (int)buffer.length(); i++ )
   {
      Draw( left + i, top, buffer[i], foregroundColor, backgroundColor );
   }
}

void ConsoleDrawer::FlipDrawBuffer()
{
   WriteConsoleOutput( _outputHandle, _drawBuffer, _consoleSize, _zeroCoordinate, &_outputRect );
}

void ConsoleDrawer::SetCursorVisibility( bool isVisible )
{
   CONSOLE_CURSOR_INFO cursorInfo;
   GetConsoleCursorInfo( _outputHandle, &cursorInfo );
   cursorInfo.bVisible = isVisible;
   SetConsoleCursorInfo( _outputHandle, &cursorInfo );
}

unsigned short ConsoleDrawer::ConsoleColorsToAttribute( ConsoleColor foregroundColor, ConsoleColor backgroundColor )
{
   return (unsigned short)( (int)foregroundColor | ( (int)backgroundColor << 0x4 ) );
}
