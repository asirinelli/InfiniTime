#include "calendar.h"
#include "../DisplayApp.h"
#include "../LittleVgl.h"

using namespace Pinetime::Applications::Screens;

calendar::calendar(Pinetime::Applications::DisplayApp* app, Pinetime::Components::LittleVgl& lvgl) : Screen(app), lvgl{lvgl} {
  app->SetTouchMode(DisplayApp::TouchModes::Polling);
}

calendar::calendar() {
  // Reset the touchmode
  app->SetTouchMode(DisplayApp::TouchModes::Gestures);
  lv_obj_clean(lv_scr_act());
}

bool calendar::Refresh() {
  return running;
}

bool calendar::OnButtonPushed() {
  running = false;
  return true;
}

bool calendar::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return true;
}

bool calendar::OnTouchEvent(uint16_t x, uint16_t y) {
  return true;
}

