#include <SDL2/SDL.h>
#include <chrono>
using namespace std::chrono;
/** A struct that manages time-related data */
struct Time {
    private:
        high_resolution_clock::time_point lastCpuTime;
        Uint64 lastGpuTime;
        int frameCount = 0;
        float timeAccumulator = 0.0f;

    public:
        float delta_time = 0.0f; /** The time delta between the current and the last frame in seconds. */
        float delta_cpu = 0.0f;  /** The time the CPU took to render the last frame in seconds. */
        float delta_gpu = 0.0f;  /** The time the GPU took to render the last frame in seconds. */
        int   framerate = 0;     /** The framerate in frames per second. */
};