#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <format>

#include "ConsoleBuffer.h"
#include "ConsoleRenderConfig.h"
#include "ConsoleColor.h"
#include "ConsoleSprite.h"
#include "ConsolePixel.h"

namespace ConsoleGame
{
   struct ConsoleBufferInfo
   {
      HANDLE OutputHandle;
      COORD ConsoleSize;
      int DrawBufferSize;
      CHAR_INFO* DrawBuffer;
      SMALL_RECT OutputRect;
      COORD ZeroCoordinate = { 0, 0 };
   };
}

using namespace std;
using namespace ConsoleGame;

ConsoleBuffer::ConsoleBuffer( short defaultWidth, short defaultHeight ) :
   _defaultForegroundColor( ConsoleColor::Grey ),
   _defaultBackgroundColor( ConsoleColor::Black ),
   _originalConsoleWidth( defaultWidth ),
   _originalConsoleHeight( defaultHeight )
{
   _bufferInfo = shared_ptr<ConsoleBufferInfo>( new ConsoleBufferInfo );
   _bufferInfo->OutputHandle = GetStdHandle( STD_OUTPUT_HANDLE );
   _bufferInfo->ConsoleSize = { defaultWidth, defaultHeight };
   _bufferInfo->DrawBufferSize = defaultWidth * defaultHeight;
   _bufferInfo->DrawBuffer = new CHAR_INFO[_bufferInfo->DrawBufferSize];
   _bufferInfo->OutputRect = { 0, 0, defaultWidth, defaultHeight };

   CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
   GetConsoleScreenBufferInfo( _bufferInfo->OutputHandle, &screenBufferInfo );
   _originalColorAttribute = screenBufferInfo.wAttributes;

   ResetDrawBuffer();
}

ConsoleBuffer::~ConsoleBuffer()
{
   delete[] _bufferInfo->DrawBuffer;
}

void ConsoleBuffer::ResetDrawBuffer()
{
   for ( int i = 0; i < _bufferInfo->DrawBufferSize; i++ )
   {
      _bufferInfo->DrawBuffer[i] = CHAR_INFO();
   }
}

void ConsoleBuffer::LoadRenderConfig( const shared_ptr<IGameRenderConfig> config )
{
   auto consoleConfig = static_pointer_cast<ConsoleRenderConfig>( config );

   _bufferInfo->ConsoleSize = { consoleConfig->ConsoleWidth, consoleConfig->ConsoleHeight };
   _bufferInfo->DrawBufferSize = consoleConfig->ConsoleWidth * consoleConfig->ConsoleHeight;
   _bufferInfo->DrawBuffer = new CHAR_INFO[_bufferInfo->DrawBufferSize];
   _bufferInfo->OutputRect = { 0, 0, consoleConfig->ConsoleWidth, consoleConfig->ConsoleHeight };

   ResetDrawBuffer();

   SetConsoleScreenBufferSize( _bufferInfo->OutputHandle, { _bufferInfo->ConsoleSize.X, _bufferInfo->ConsoleSize.Y } );

   SMALL_RECT windowCoords{ 0, 0, _bufferInfo->ConsoleSize.X - 1, _bufferInfo->ConsoleSize.Y - 1 };
   SetConsoleWindowInfo( _bufferInfo->OutputHandle, TRUE, &windowCoords );

   SetCursorVisibility( false );

   SetDefaultForegroundColor( consoleConfig->DefaultForegroundColor );
   SetDefaultBackgroundColor( consoleConfig->DefaultBackgroundColor );

   Clear();
   Flip();
}

void ConsoleBuffer::CleanUp()
{
   SetConsoleTextAttribute( _bufferInfo->OutputHandle, _originalColorAttribute );

   SMALL_RECT windowCoords{ 0, 0, _originalConsoleWidth - 1, _originalConsoleHeight - 1 };
   SetConsoleWindowInfo( _bufferInfo->OutputHandle, TRUE, &windowCoords );

   SetCursorVisibility( true );
   SetConsoleCursorPosition( _bufferInfo->OutputHandle, { 0, 0 } );

   Clear();
   Flip();
}

void ConsoleBuffer::SetDefaultForegroundColor( ConsoleColor color )
{
   _defaultForegroundColor = color;
}

void ConsoleBuffer::SetDefaultBackgroundColor( ConsoleColor color )
{
   _defaultBackgroundColor = color;
}

void ConsoleBuffer::Clear()
{
   for ( int i = 0; i < _bufferInfo->DrawBufferSize; i++ )
   {
      _bufferInfo->DrawBuffer[i].Char.AsciiChar = 0x20;
      _bufferInfo->DrawBuffer[i].Attributes = ConsoleColorsToAttribute( _defaultForegroundColor, _defaultBackgroundColor );
   }
}

void ConsoleBuffer::Draw( int left, int top, char buffer )
{
   Draw( left, top, buffer, _defaultForegroundColor );
}

void ConsoleBuffer::Draw( int left, int top, char buffer, ConsoleColor foregroundColor )
{
   Draw( left, top, buffer, foregroundColor, _defaultBackgroundColor );
}

void ConsoleBuffer::Draw( int left, int top, char buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor )
{
   if ( left < 0 || left >= _bufferInfo->ConsoleSize.X || top < 0 || top >= _bufferInfo->ConsoleSize.Y )
   {
      return;
   }

   auto bufferLocation = left + ( top * _bufferInfo->ConsoleSize.X );
   _bufferInfo->DrawBuffer[bufferLocation].Attributes = ConsoleColorsToAttribute( foregroundColor, backgroundColor );
   _bufferInfo->DrawBuffer[bufferLocation].Char.AsciiChar = buffer;
}

void ConsoleBuffer::Draw( int left, int top, const string& buffer )
{
   Draw( left, top, buffer, _defaultForegroundColor );
}

void ConsoleBuffer::Draw( int left, int top, const string& buffer, ConsoleColor foregroundColor )
{
   Draw( left, top, buffer, foregroundColor, _defaultBackgroundColor );
}

void ConsoleBuffer::Draw( int left, int top, const string& buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor )
{
   for ( int i = 0; i < (int)buffer.length(); i++ )
   {
      Draw( left + i, top, buffer[i], foregroundColor, backgroundColor );
   }
}

void ConsoleBuffer::Draw( int left, int top, const ConsoleSprite& sprite )
{
   int i = 0, j = 0;

   for ( auto pixel : sprite.Pixels )
   {
      Draw( left + i, top + j, pixel.Value, pixel.Color );

      i++;

      if ( i == sprite.Width )
      {
         i = 0;
         j++;
      }
   }
}

void ConsoleBuffer::Flip()
{
   WriteConsoleOutput( _bufferInfo->OutputHandle,
                       _bufferInfo->DrawBuffer,
                       _bufferInfo->ConsoleSize,
                       _bufferInfo->ZeroCoordinate,
                       &( _bufferInfo->OutputRect ) );
}

void ConsoleBuffer::SetCursorVisibility( bool isVisible )
{
   CONSOLE_CURSOR_INFO cursorInfo;
   GetConsoleCursorInfo( _bufferInfo->OutputHandle, &cursorInfo );
   cursorInfo.bVisible = isVisible;
   SetConsoleCursorInfo( _bufferInfo->OutputHandle, &cursorInfo );
}

unsigned short ConsoleBuffer::ConsoleColorsToAttribute( ConsoleColor foregroundColor, ConsoleColor backgroundColor )
{
   return (unsigned short)( (int)foregroundColor | ( (int)backgroundColor << 0x4 ) );
}
