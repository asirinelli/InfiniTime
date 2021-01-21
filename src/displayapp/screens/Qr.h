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

        uint16_t qrSize;
        uint16_t qrPixelSize;
        uint16_t bufferSize;
        lv_area_t area;
        // static constexpr uint16_t maxBufferSize = 12*12;
        // static constexpr lv_color_t b[maxBufferSize];
        static constexpr uint16_t border = 1;

        bool running = true;
        std::string qrString = "https://github.com/JF002/Pinetime";
        // qrcodegen::QrCode qrCode;
      };
    }
  }
}
