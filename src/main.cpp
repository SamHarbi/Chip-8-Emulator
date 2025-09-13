#include <iostream>
#include <string>

#include "renderer.h"
#include "cpu.h"

int main(void) {
    Renderer* rend = new Renderer();
    int error = rend->init();

    // This can all be done a lot better and safer, TODO
    CPU* cpu = new CPU(rend->input);

    // Clock values to control speed of emulation
    std::chrono::time_point<std::chrono::steady_clock> last_clock = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> currentTime = last_clock;
    std::chrono::duration<float, std::chrono::milliseconds::period> dt = currentTime - last_clock;
    const std::chrono::duration<double> clock_delay{0.0};

    // Renderer -> Creates Input (Since input is tied to a window which is renderer domain), CPU -> purely emulation,
    // Main -> Orchestrate everything
    // Input Obj passed into CPU, CPU polls keys independently from renderer thanks to this middle man obj.
    if(error == 0) {
        do {
            currentTime = std::chrono::steady_clock::now();
		    dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - last_clock);
		    if( dt > clock_delay ) {
			    last_clock = cpu->cycle();
                rend->inputDisplayData(cpu->getDisplayData());
                error = rend->render();
		    }
            
        } while ( error == 0);
    }

    delete cpu;
    delete rend;
    return 0;
}