#ifndef TRAY_H
#define TRAY_H

#include <windows.h>

class Tray {
 public:
  Tray();
  ~Tray();

 private:
  NOTIFYICONDATA nid_;
};

#endif