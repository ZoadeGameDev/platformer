//
// Created by zoade on 19.11.2026.
//

#ifndef PLATFORMER_FLAG_H
#define PLATFORMER_FLAG_H
#include "interactable.h"

class Flag : public Interactable {
public:
    void SetupSensors() override;

    void UpdateVisuals() override;

    float GetPositionX();
    float GetPositionY();

    bool CheckBool();

    void SetBool(bool boolean);

private:
    // Sensor
    Sensor flag_;
    float position_x_;
    float position_y_;
};


#endif // PLATFORMER_FLAG_H
