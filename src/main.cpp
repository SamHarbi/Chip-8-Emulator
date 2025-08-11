#include <iostream>
#include <string>

#include "renderer.h"
#include "cpu.h"

int main(void) {
    CPU* cpu = new CPU();
    Renderer* rend = new Renderer();
    int error = rend->init();
    if(error == 0) {
        do {
            error = rend->render();
        } while ( error == 0);
    }

    return 0;
}