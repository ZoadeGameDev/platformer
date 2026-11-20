//
// Created by zoade on 20.11.2026.
//

#ifndef PLATFORMER_WIN_FLAG_H
#define PLATFORMER_WIN_FLAG_H
#include "interactable.h"

class WinZone : public Interactable {
public:
    void SetupSensors() override;

    bool CheckBool();
private:
    // Sensor
    Sensor win_zone_;
};

#endif // PLATFORMER_WIN_FLAG_H
