#include "Time.h"
#include <SDL2/SDL.h>
constexpr float expected_delta = 10.75;

uint64_t last_frametime;
uint64_t curr_frametime;
uint64_t _delta;
float _normaldelta;

uint64_t Time::delta() {return _delta;}
float Time::normaldelta() {return _normaldelta;}

void Time::step() {
    last_frametime = curr_frametime;
    curr_frametime = SDL_GetTicks64();
    _delta = curr_frametime-last_frametime;
    _normaldelta = _delta/expected_delta;
}