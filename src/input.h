#pragma once
// Abstract Class. Decouple input (based on api used for window/renderer) from the cpu
class IInput {
    public:
        ~IInput() {};

        bool key_1;
        bool key_2;
        bool key_3;
        bool key_C;
        bool key_4;
        bool key_5;
        bool key_6;
        bool key_D;
        bool key_7;
        bool key_8;
        bool key_9;
        bool key_E;
        bool key_A;
        bool key_0;
        bool key_B;
        bool key_F;

        virtual void poll() = 0; // Populate class members
};