//
// Created by zoade on 20.11.2026.
//

#ifndef PLATFORMER_SETTINGS_H
#define PLATFORMER_SETTINGS_H
class Settings {
public:
    inline static bool debug_mode_ = false;
    inline static int fps_ = 60;

    // Messy code
    inline static bool want_go_down_ = false; // I put it there to be easily accessible but usually it shouldn't be here
                                              // I really wanted the characcter to go through platforms
    inline static bool i_am_on_passable_platforms_ = false; // same for this one

};

#endif // PLATFORMER_SETTINGS_H