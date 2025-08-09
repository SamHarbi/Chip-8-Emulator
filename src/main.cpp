#include <iostream>
#include <string>

#include "renderer.h"

int main(void) {
    Renderer* rend = new Renderer();
    int error = rend->init();
    if(error == 0) {
        do {
            error = rend->render();
        } while ( error == 0);
    }

    return 0;
}