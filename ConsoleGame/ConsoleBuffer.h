#pragma once

#include <memory>
#include <string>

#include "IScreenBuffer.h"
#include "ConsoleSprite.h"

namespace ConsoleGame
{
   struct ConsoleBufferInfo;

   class ConsoleBuffer : public IScreenBuffer
   {
   public:
      ConsoleBuffer();
      ~ConsoleBuffer();

      void Initialize( ConsoleColor defaultForegroundColor,
                       ConsoleColor defaultBackgroundColor,
                       short defaultWidth,
                       short defaultHeight );
      virtual void LoadRenderDefs( const std::shared_ptr<IGameRenderDefs> renderDefs ) override;
      virtual void CleanUp() override;

      virtual void SetDefaultForegroundColor( ConsoleColor color );
      virtual void SetDefaultBackgroundColor( ConsoleColor color );
      virtual void Clear() override;

      virtual void Draw( int left, int top, char buffer );
      virtual void Draw( int left, int top, char buffer, ConsoleColor foregroundColor );
      virtual void Draw( int left, int top, char buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor );
      virtual void Draw( int left, int top, const std::string& buffer );
      virtual void Draw( int left, int top, const std::string& buffer, ConsoleColor foregroundColor );
      virtual void Draw( int left, int top, const std::string& buffer, ConsoleColor foregroundColor, ConsoleColor backgroundColor );
      virtual void Draw( int left, int top, const ConsoleSprite& sprite );

      void Flip() override;

   private:
      void ResetDrawBuffer();
      void SetCursorVisibility( bool isVisible );
      unsigned short ConsoleColorsToAttribute( ConsoleColor foregroundColor, ConsoleColor backgroundColor );

   private:
      std::shared_ptr<ConsoleBufferInfo> _bufferInfo;

      ConsoleColor _defaultForegroundColor;
      ConsoleColor _defaultBackgroundColor;

      unsigned short _originalColorAttribute;
      short _originalWidth;
      short _originalHeight;
      bool _drawBufferAllocated;
   };
}
