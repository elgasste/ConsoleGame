#include <chrono>

#include "HighResolutionClockWrapper.h"

using namespace std;
using namespace ConsoleGame;

long long HighResolutionClockWrapper::Now()
{
   return chrono::steady_clock::now().time_since_epoch().count();
}
