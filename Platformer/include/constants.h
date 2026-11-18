//
// Created by zoade on 04.11.2026.
//

#ifndef PLATFORMER_CONSTANTS_H
#define PLATFORMER_CONSTANTS_H


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
#endif // PLATFORMER_CONSTANTS_H
