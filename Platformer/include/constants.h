//
// Created by zoade on 04.11.2026.
//

#ifndef BOX2D_TESTS_CONSTANTS_H
#define BOX2D_TESTS_CONSTANTS_H


class Conversion {
    static constexpr float MetersPerPixels = 0.05f;
public:
    static constexpr float Pixels(float meters) {
        return meters / MetersPerPixels;
    }

    static constexpr float Meters( float pixels) {
        return pixels * MetersPerPixels;
    }
};
#endif // BOX2D_TESTS_CONSTANTS_H
