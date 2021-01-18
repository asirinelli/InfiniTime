#pragma once

#include <lvgl/lvgl.h>
#include <cstdint>
#include "Screen.h"
#include "QrCode.hpp"

using namespace qrcodegen;


namespace Pinetime {
  namespace Components {
    class LittleVgl;
  }
  namespace Applications {
    namespace Screens {

      class Qr : public Screen {
      public:
        Qr(DisplayApp* app, Pinetime::Components::LittleVgl& lvgl);

        ~Qr() override;

        bool Refresh() override;

        bool OnButtonPushed() override;

        bool OnTouchEvent(TouchEvents event) override;

        bool OnTouchEvent(uint16_t x, uint16_t y) override;

        // void receiveQrString(std::string qrString);

        void drawQr();

      private:
        Pinetime::Components::LittleVgl& lvgl;
        static constexpr uint16_t width = 6;
        static constexpr uint16_t height = 6;
        static constexpr uint16_t bufferSize = width * height;
        lv_color_t b[bufferSize];

        uint16_t qrSize;
        uint16_t qrPixelSize = 6;
        bool running = true;
        std::string qrString = "https://github.com/JF002/Pinetime";
        // qrcodegen::QrCode qrCode;
      };
    }
  }
}
