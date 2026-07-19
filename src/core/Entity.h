#pragma once

namespace dc8::core {
    class Entity {
    public:
        virtual ~Entity() = default;
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;
        virtual void drawUi() = 0;
    };
}
