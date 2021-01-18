#include "Qr.h"
#include "../DisplayApp.h"
#include "../LittleVgl.h"
#include "QrCode.hpp"
#include <string>

using namespace Pinetime::Applications::Screens;
using namespace qrcodegen;


Qr::Qr(Pinetime::Applications::DisplayApp* app, Pinetime::Components::LittleVgl& lvgl) : Screen(app), lvgl{lvgl} {
  app->SetTouchMode(DisplayApp::TouchModes::Polling);
  std::fill(b, b + bufferSize, LV_COLOR_WHITE);
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

// void Qr::receiveQrString(std::string newQrString) {
//   qrString = newQrString;
// }

void Qr::drawQr() {
  qrcodegen::QrCode qrCode = QrCode::encodeText("https://github.com/JF002/Pinetime", QrCode::Ecc::MEDIUM);
  qrSize = qrCode.getSize();
  // qrPixelSize = 240 / qrSize;
  // qrPixelSize = 8;
  // uint16_t bufferSize1 = qrPixelSize*qrPixelSize;
  // lv_color_t bb[bufferSize1];
  // std::fill(bb, bb + bufferSize1, LV_COLOR_WHITE);

  lv_area_t area;
  int border = 4;
	for (int y = -border; y < qrSize + border; y++) {
		for (int x = -border; x < qrSize + border; x++) {
      if (!qrCode.getModule(x, y)) {
        area.x1 = qrPixelSize*(x+border);
        area.y1 = qrPixelSize*(y+border);
        area.x2 = qrPixelSize*(x+border+1) - 1;
        area.y2 = qrPixelSize*(y+border+1) - 1;
        lvgl.SetFullRefresh(Components::LittleVgl::FullRefreshDirections::None);
        lvgl.FlushDisplay(&area, b);
      }
		}
	}
}
