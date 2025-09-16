#pragma once
#include <map>

// Abstract Class. Decouple input (based on api used for window/renderer) from the cpu
class IInput {
    public:
        ~IInput() {};
        virtual void poll() {}; // Populate class members
        virtual bool queryKey(uint8_t name) {return false;};
        virtual bool isAnyKeyPressed(uint8_t &keyThatIsPressed) {return false;};

    protected:
        std::map<uint8_t, bool> keys {
            {0x0, false},
            {0x1, false},
            {0x2, false},
            {0x3, false},
            {0x4, false},
            {0x5, false},
            {0x6, false},
            {0x7, false},
            {0x8, false},
            {0x9, false},
            {0xA, false},
            {0xB, false},
            {0xC, false},
            {0xD, false},
            {0xE, false},
            {0xF, false},
        };
};