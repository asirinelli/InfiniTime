#pragma once

#include <lvgl/lvgl.h>
#include <cstdint>
#include "Screen.h"

namespace Pinetime {
  namespace Components {
    class LittleVgl;
  }
  namespace Applications {
    namespace Screens {

      class calendar : public Screen {
      public:
        calendar(DisplayApp* app, Pinetime::Components::LittleVgl& lvgl);

        ~calendar() override;

        bool Refresh() override;

        bool OnButtonPushed() override;

        bool OnTouchEvent(TouchEvents event) override;

        bool OnTouchEvent(uint16_t x, uint16_t y) override;

      private:
        Pinetime::Components::LittleVgl& lvgl;
        bool running = true;
      };
    }
  }
}
