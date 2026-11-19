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

private:
    // Sensor
    Sensor flag_;
};


#endif // PLATFORMER_FLAG_H
