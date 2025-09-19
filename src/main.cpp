#include <iostream>
#include <string>

#include "renderer.h"
#include "cpu.h"

int main(int argc, char* argv[]) {
    Renderer* rend = new Renderer();
    int error = rend->init();

    // This can all be done a lot better and safer, TODO make a shared ptr
    CPU* cpu = new CPU(rend->input);

    if( argc > 1 ) {
        // A bit more validation for the future would be nice, TODO
        cpu->loadROM(argv[1]);
    } else {
        error = 1;
        std::cerr << "Please pass in a .ch8 rom filepath as the first argument!" << std::endl;
    }

    // Clock values to control speed of emulation
    std::chrono::time_point<std::chrono::steady_clock> last_clock = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> currentTime = last_clock;
    std::chrono::duration<float, std::chrono::milliseconds::period> dt = currentTime - last_clock;
    const std::chrono::duration<double> clock_delay{0.001};

    if(error == 0) {
        do {
            currentTime = std::chrono::steady_clock::now();
		    dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - last_clock);
            rend->input->poll();
            if( cpu->updateRenderer ) {
                error = rend->render();
                cpu->updateRenderer = false;
            }
		    if( dt > clock_delay ) {
                //std::cout << dt << std::endl;
                rend->inputDisplayData(cpu->getDisplayData());
                last_clock = cpu->cycle();
		    }
            
        } while ( error == 0);
    }

    delete cpu;
    delete rend;
    return 0;
}