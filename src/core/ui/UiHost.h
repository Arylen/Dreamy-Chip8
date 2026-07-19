#pragma once

#include "core/Entity.h"
namespace dc8::core {
    class UiHost : public Entity {
    public:
        UiHost();
        ~UiHost();
        void update(float deltaTime);
        void drawUi();
    };
}
