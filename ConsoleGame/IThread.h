#pragma once

namespace ConsoleGame
{
   class __declspec( novtable ) IThread
   {
   public:
      virtual bool SetThisThreadToHighestPriority() = 0;
   };
}
