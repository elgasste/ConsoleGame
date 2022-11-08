#pragma once

namespace ConsoleGame
{
   enum class GameCommand;

   class _declspec( novtable ) IGameCommandExecutor
   {
   public:
      virtual void Execute( GameCommand command ) = 0;
   };
}
