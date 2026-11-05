//
// Created by zoade on 04.11.2026.
//

#ifndef BOX2D_TESTS_CONSTANTS_H
#define BOX2D_TESTS_CONSTANTS_H


class Conversion {
    static constexpr float MetersperPixels = 0.05f;
public:
    static constexpr float Pixels(float meters) {
        return meters / MetersperPixels;
    }

    static constexpr float Meter( float pixels) {
        return pixels * MetersperPixels;
    }
};
#endif // BOX2D_TESTS_CONSTANTS_H
