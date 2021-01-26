#include <string>
#include "../DisplayApp.h"
#include "../LittleVgl.h"
#include "qrcodegen.h"
#include "components/ble/QrService.h"
#include "Qr.h"

using namespace Pinetime::Applications::Screens;

Qr::Qr(Pinetime::Applications::DisplayApp* app,
        Pinetime::Components::LittleVgl& lvgl,
        Pinetime::Controllers::QrService& qrService) :
          Screen(app), lvgl{lvgl}, qrService(qrService) {
  app->SetTouchMode(DisplayApp::TouchModes::Polling);
}

Qr::~Qr() {
  // Reset the touchmode
  app->SetTouchMode(DisplayApp::TouchModes::Gestures);
  lv_obj_clean(lv_scr_act());
}

bool Qr::Refresh() {
  return running;
}

bool Qr::OnButtonPushed() {
  running = false;
  return true;
}

bool Qr::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return true;
}

bool Qr::OnTouchEvent(uint16_t x, uint16_t y) {
  drawQr();
  return true;
}

void Qr::drawQr() {

  qrText = qrService.getQrText();

  bool ok = qrcodegen_encodeText(qrText.c_str(), tempBuffer, qrcode, qrcodegen_Ecc_LOW,
      qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);

  if (ok) {

    qrSize = qrcodegen_getSize(qrcode);
    qrModuleSize = 240 / (qrSize + 2*border);
    bufferSize = qrModuleSize * qrModuleSize;

    lv_color_t* b = new lv_color_t[bufferSize];
    std::fill(b, b + bufferSize, LV_COLOR_WHITE);

    for (int y = -border; y < qrSize + border; y++) {
    	for (int x = -border; x < qrSize + border; x++) {
        if (!qrcodegen_getModule(qrcode, x, y)) {
          area.x1 = qrModuleSize*(x+border);
          area.y1 = qrModuleSize*(y+border);
          area.x2 = qrModuleSize*(x+border+1) - 1;
          area.y2 = qrModuleSize*(y+border+1) - 1;
          lvgl.FlushDisplay(&area, b);
        }
    	}
    }
    delete[] b;
  }
}
