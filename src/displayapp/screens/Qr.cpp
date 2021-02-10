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
  if(qrText != qrService.getQrText()) {
    qrText = qrService.getQrText();
    resetScreen();
    drawQr();
  }
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
  return true;
}

void Qr::drawQr() {
  
  bool ok = qrcodegen_encodeText(qrText.c_str(), tempBuffer, qrcode, qrcodegen_Ecc_LOW,
    qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
  if (ok) {

    qrSize = qrcodegen_getSize(qrcode);
    qrModuleSize = LV_HOR_RES_MAX / (qrSize + 2*border);
    bufferSize = qrModuleSize * qrModuleSize;
    
    offset = (LV_HOR_RES_MAX - (qrSize + 2*border)*qrModuleSize)/2;

    lv_color_t* b = new lv_color_t[bufferSize];
    std::fill(b, b + bufferSize, LV_COLOR_WHITE);

    for (int y = -border; y < qrSize + border; y++) {
    	for (int x = -border; x < qrSize + border; x++) {
        if (!qrcodegen_getModule(qrcode, x, y)) {
          area.x1 = qrModuleSize*(x+border) + offset;
          area.y1 = qrModuleSize*(y+border) + offset;
          area.x2 = qrModuleSize*(x+border+1) + offset - 1;
          area.y2 = qrModuleSize*(y+border+1) + offset - 1;
          lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::None);  
          lvgl.FlushDisplay(&area, b);
        }
    	}
    }
    delete[] b;
  }
}

void Qr::resetScreen() {
  
  lv_color_t* b = new lv_color_t[100];
  std::fill(b, b + 100, LV_COLOR_BLACK);
  for (int y = 0; y < (LV_VER_RES_MAX/10); y++) {
    for (int x = 0; x < (LV_HOR_RES_MAX/10); x++) {
      area.x1 = 10*x;
      area.y1 = 10*y;
      area.x2 = 10*(x+1) - 1;
      area.y2 = 10*(y+1) - 1;
      lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::None);  
      lvgl.FlushDisplay(&area, b);
    }
  }
  delete[] b;
}

