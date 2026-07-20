#include "UiHost.h"
#include "core/Log.h"
#include "core/ui/MainMenuBar.h"

namespace dc8::core::ui {
    UiHost::UiHost(AppState& state) {
        elements_.push_back(std::make_unique<MainMenuBar>(state));
        log::info("UI Elements Loaded: {}", elements_.size());
    }

    UiHost::~UiHost() { }

    void UiHost::update(float deltaTime) {
        for (auto& e : elements_) {
            e->update(deltaTime);
        }
    }

    void UiHost::drawUi() {
        for (auto& e : elements_) {
            e->drawUi();
        }
    }

    void UiHost::draw() { }
}
