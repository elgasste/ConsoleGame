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

ConsoleBuffer::ConsoleBuffer( const shared_ptr<ConsoleRenderConfig> renderConfig ) :
   _renderConfig( renderConfig ),
   _defaultForegroundColor( ConsoleColor::Grey ),
   _defaultBackgroundColor( ConsoleColor::Black )
{
   _bufferInfo = shared_ptr<ConsoleBufferInfo>( new ConsoleBufferInfo );
   _bufferInfo->OutputHandle = GetStdHandle( STD_OUTPUT_HANDLE );
   _bufferInfo->ConsoleSize = { _renderConfig->ConsoleWidth, _renderConfig->ConsoleHeight };
   _bufferInfo->DrawBufferSize = _renderConfig->ConsoleWidth * _renderConfig->ConsoleHeight;
   _bufferInfo->DrawBuffer = new CHAR_INFO[_bufferInfo->DrawBufferSize];
   _bufferInfo->OutputRect = { 0, 0, _renderConfig->ConsoleWidth, _renderConfig->ConsoleHeight };

   CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
   GetConsoleScreenBufferInfo( _bufferInfo->OutputHandle, &screenBufferInfo );
   _originalColorAttribute = screenBufferInfo.wAttributes;

   for ( int i = 0; i < _bufferInfo->DrawBufferSize; i++ )
   {
      _bufferInfo->DrawBuffer[i] = CHAR_INFO();
   }
}

ConsoleBuffer::~ConsoleBuffer()
{
   delete[] _bufferInfo->DrawBuffer;
}

void ConsoleBuffer::Initialize()
{
   SetConsoleScreenBufferSize( _bufferInfo->OutputHandle, { _bufferInfo->ConsoleSize.X, _bufferInfo->ConsoleSize.Y } );

   SMALL_RECT windowCoords{ 0, 0, _bufferInfo->ConsoleSize.X - 1, _bufferInfo->ConsoleSize.Y - 1 };
   SetConsoleWindowInfo( _bufferInfo->OutputHandle, TRUE, &windowCoords );

   SetCursorVisibility( false );

   SetDefaultForegroundColor( _renderConfig->DefaultForegroundColor );
   SetDefaultBackgroundColor( _renderConfig->DefaultBackgroundColor );

   Clear();
   Flip();
}

void ConsoleBuffer::CleanUp()
{
   // TODO: restore the original console dimensions
   SetConsoleTextAttribute( _bufferInfo->OutputHandle, _originalColorAttribute );
   Clear();
   Flip();

   SetCursorVisibility( true );
   SetConsoleCursorPosition( _bufferInfo->OutputHandle, { 0, 0 } );
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
