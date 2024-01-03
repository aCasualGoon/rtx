#ifndef _TIME_H_CUSTOM_
#define _TIME_H_CUSTOM_

#include <SDL2/SDL.h>

namespace Time
{
    /**The time in ms since last iteration*/
    uint64_t delta();
    /**The time since the last iteration normalized to be aproximately 1*/
    float normaldelta();
    /**Steps the time forward to the current iteration*/
    void step();
}


#endif//_TIME_H_CUSTOM_