#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>

#include "KeyboardInputReader.h"
#include "GameInputConfig.h"
#include "KeyCode.h"
#include "GameButton.h"

using namespace std;
using namespace ConsoleGame;

KeyboardInputReader::KeyboardInputReader( const shared_ptr<GameInputConfig>& inputConfig )
   : _inputConfig( inputConfig )
{
   for ( int i = 0; i < (int)GameButton::GameButtonCount; i++ )
   {
      _buttonStates[(GameButton)i] = { false, false };
   }
}

void KeyboardInputReader::ReadInput()
{
   std::vector<GameButton> checkedButtons;

   for ( map<KeyCode, GameButton>::iterator it = _inputConfig->KeyMap.begin(); it != _inputConfig->KeyMap.end(); it++ )
   {
      if ( std::find( checkedButtons.begin(), checkedButtons.end(), it->second ) != checkedButtons.end() )
      {
         continue; // already updated this button
      }

      if ( IsKeyDown( it->first ) )
      {
         _buttonStates.at( it->second ).ButtonWasPressed = !_buttonStates.at( it->second ).ButtonIsDown;
         _buttonStates.at( it->second ).ButtonIsDown = true;

         checkedButtons.push_back( it->second );
      }
      else
      {
         _buttonStates.at( it->second ).ButtonWasPressed = false;
         _buttonStates.at( it->second ).ButtonIsDown = false;
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
