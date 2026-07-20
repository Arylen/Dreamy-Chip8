#pragma once

#include "core/AppState.h"
#include "core/Entity.h"

namespace dc8::core::ui {
    class FilePickerHost: public Entity {
    public:
    public:
        FilePickerHost(AppState& state);
        ~FilePickerHost();
        void update(float deltaTime);
        void drawUi();
        void draw();
    private:
        AppState& state_;
    };
}
