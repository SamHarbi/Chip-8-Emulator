#pragma once
#include <map>

// Abstract Class. Decouple input (based on api used for window/renderer) from the cpu
class IInput {
    public:
        ~IInput() {};
        virtual void poll() = 0; // Populate class members

    protected:
        // String because labels such as "ESC" Are likely to be implemented
        std::map<std::string, bool> keys {
            {"0", false},
            {"1", false},
            {"2", false},
            {"3", false},
            {"4", false},
            {"5", false},
            {"6", false},
            {"7", false},
            {"8", false},
            {"9", false},
            {"A", false},
            {"B", false},
            {"C", false},
            {"D", false},
            {"E", false},
            {"F", false},
        };
};