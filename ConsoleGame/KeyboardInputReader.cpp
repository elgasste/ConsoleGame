#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "KeyboardInputReader.h"
#include "GameInputConfig.h"
#include "KeyCode.h"
#include "GameButton.h"

using namespace std;
using namespace ConsoleGame;

KeyboardInputReader::KeyboardInputReader( const shared_ptr<GameInputConfig>& inputConfig )
{
   for ( int i = 0; i < (int)GameButton::GameButtonCount; i++ )
   {
      _buttonStates[(GameButton)i] = { false, false };
   }

   // since we allow multiple keys to bind to a single button, creating this inverted
   // map of button-to-keys makes the input reading logic much easier
   for ( int i = 0; i < (int)GameButton::GameButtonCount; i++ )
   {
      auto button = (GameButton)i;

      for ( auto const& [keyCode, mappedButton] : inputConfig->KeyMap )
      {
         if ( mappedButton == button )
         {
            _buttonKeyBindings[button].push_back( keyCode );
         }
      }
   }
}

void KeyboardInputReader::ReadInput()
{
   for ( auto const& [button, keyCodes] : _buttonKeyBindings )
   {
      bool buttonIsDown = false;

      for ( auto keyCode : keyCodes )
      {
         if ( IsKeyDown( keyCode ) )
         {
            buttonIsDown = true;
            break;
         }
      }

      if ( buttonIsDown )
      {
         _buttonStates.at( button ).ButtonWasPressed = !_buttonStates.at( button ).ButtonIsDown;
         _buttonStates.at( button ).ButtonIsDown = true;
      }
      else
      {
         _buttonStates.at( button ).ButtonWasPressed = false;
         _buttonStates.at( button ).ButtonIsDown = false;
      }
   }
}

bool KeyboardInputReader::WasButtonPressed( GameButton button ) const
{
   return _buttonStates.at( button ).ButtonWasPressed;
}

bool KeyboardInputReader::IsButtonDown( GameButton button ) const
{
   return _buttonStates.at( button ).ButtonIsDown;
}

bool KeyboardInputReader::WasAnyButtonPressed() const
{
   for ( int i = 0; i < (int)GameButton::GameButtonCount; i++ )
   {
      auto button = (GameButton)i;

      if ( button != GameButton::Diagnostics && WasButtonPressed( button ) )
      {
         return true;
      }
   }

   return false;
}

bool KeyboardInputReader::IsKeyDown( KeyCode keyCode ) const
{
   return GetKeyState( (int)keyCode ) & 0x800; // if the high-order bit is 1, the key is down
}
