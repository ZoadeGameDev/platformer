//
// Created by zoade on 20.11.2026.
//

#ifndef PLATFORMER_DEATH_ZONE_H
#define PLATFORMER_DEATH_ZONE_H
#include "interactable.h"
#include "sensor.h"

class DeathZone : public Interactable {
public:
    void SetupSensors() override;

    bool CheckBool();

private:
    // Sensor
    Sensor death_zone_;
};


#endif // PLATFORMER_DEATH_ZONE_H
