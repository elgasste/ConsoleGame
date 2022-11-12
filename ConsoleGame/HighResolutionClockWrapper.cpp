#include <chrono>

#include "HighResolutionClockWrapper.h"

using namespace std;
using namespace ConsoleGame;

long long HighResolutionClockWrapper::Now()
{
   return chrono::high_resolution_clock::now().time_since_epoch().count();
}
