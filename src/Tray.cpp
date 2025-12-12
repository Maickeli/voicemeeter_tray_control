#include "Tray.h"

#include <windows.h>

#define WM_TRAYICON (WM_USER + 1)

#ifndef IDI_MYICON
#define IDI_MYICON 101
#endif

HMENU hmenu_;

// Window procedure to handle tray messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_TRAYICON:
      if (lParam == WM_RBUTTONUP) {
        POINT pt;
        GetCursorPos(&pt);
        SetForegroundWindow(hwnd);  // required to show menu properly
        TrackPopupMenu(hmenu_, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, nullptr);
      }
      break;

    case WM_COMMAND:
      if (LOWORD(wParam) == 1) {  // Exit menu item
        PostQuitMessage(0);
      }
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
  return 0;
}

Tray::Tray() {
  HINSTANCE exe = GetModuleHandle(NULL);

  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = exe;
  wc.lpszClassName = "VoiceMeeterTrayControl";
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(exe, MAKEINTRESOURCE(IDI_MYICON));
  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(0, wc.lpszClassName, "VoiceMeeterTrayControl", WS_OVERLAPPEDWINDOW, 0,
                             0, 0, 0, nullptr, nullptr, exe, nullptr);

  nid_ = {};
  nid_.cbSize = sizeof(NOTIFYICONDATA);
  nid_.hWnd = hwnd;
  nid_.uID = 1;
  nid_.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
  nid_.uCallbackMessage = WM_TRAYICON;
  nid_.hIcon = (HICON)LoadImage(exe, MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON,
                                GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);

  strcpy_s(nid_.szTip, "VoiceMeeter Tray Control");
  Shell_NotifyIcon(NIM_ADD, &nid_);

  hmenu_ = CreatePopupMenu();
  AppendMenu(hmenu_, MF_STRING, 1, "Exit");
}

Tray::~Tray() {
  Shell_NotifyIcon(NIM_DELETE, &nid_);
  DestroyMenu(hmenu_);
}
