#pragma once

#include <linux/input-event-codes.h> // 提供 KEY_* 常量 :contentReference[oaicite:0]{index=0}
#include <sys/types.h>
#include <array>

namespace xwrap {
enum class Key : int {
  Unknown = 0, // UNKNOWN

  A = 4,
  B = 5,
  C = 6,
  D = 7,
  E = 8,
  F = 9,
  G = 10,
  H = 11,
  I = 12,
  J = 13,
  K = 14,
  L = 15,
  M = 16,
  N = 17,
  O = 18,
  P = 19,
  Q = 20,
  R = 21,
  S = 22,
  T = 23,
  U = 24,
  V = 25,
  W = 26,
  X = 27,
  Y = 28,
  Z = 29,

  Num1 = 30,
  Num2 = 31,
  Num3 = 32,
  Num4 = 33,
  Num5 = 34,
  Num6 = 35,
  Num7 = 36,
  Num8 = 37,
  Num9 = 38,
  Num0 = 39,

  Enter = 40, // Enter
  Escape = 41, // Esc
  Backspace = 42,
  Tab = 43,
  Space = 44,

  Minus = 45, // -
  Equals = 46, // =
  LeftBracket = 47, // [
  RightBracket = 48, // ]
  Backslash = 49, // \

  Semicolon = 51, // ;
  Apostrophe = 52, // '
  Grave = 53, // `
  Comma = 54, // ,
  Period = 55, // .
  Slash = 56, // /

  CapsLock = 57,

  // F1–F12
  F1 = 58,
  F2 = 59,
  F3 = 60,
  F4 = 61,
  F5 = 62,
  F6 = 63,
  F7 = 64,
  F8 = 65,
  F9 = 66,
  F10 = 67,
  F11 = 68,
  F12 = 69,

  PrintScreen = 70,
  ScrollLock = 71,
  Pause = 72,

  Insert = 73,
  Home = 74,
  PageUp = 75,
  Delete = 76,
  End = 77,
  PageDown = 78,

  ArrowRight = 79,
  ArrowLeft = 80,
  ArrowDown = 81,
  ArrowUp = 82,

  // Pad
  NumLockClear = 83, // NumLock
  KP_Divide = 84,
  KP_Multiply = 85,
  KP_Minus = 86,
  KP_Plus = 87,
  KP_Enter = 88,
  KP_1 = 89,
  KP_2 = 90,
  KP_3 = 91,
  KP_4 = 92,
  KP_5 = 93,
  KP_6 = 94,
  KP_7 = 95,
  KP_8 = 96,
  KP_9 = 97,
  KP_0 = 98,
  KP_Period = 99,

  // Mod
  LCtrl = 224,
  LShift = 225,
  LAlt = 226,
  LGUI = 227,
  RCtrl = 228,
  RShift = 229,
  RAlt = 230,
  RGUI = 231,

  Count = 512
};

enum class MouseButton {
  Unknown = -1, // 未知按键
  Left = 1, // BUTTON1
  Right = 2, // BUTTON2
  Middle = 3, // BUTTON3
  X1 = 4, // BUTTON4
  X2 = 5, // BUTTON5
  Button6 = 6,
  Button7 = 7,
  Button8 = 8
};

consteval std::array<u_int16_t, 256> usb_hid_to_evdev() {
  std::array<u_int16_t, 256> table {};
  table.fill(
    KEY_UNKNOWN
  ); // 默认所有 Usage ID 映射到 KEY_UNKNOWN :contentReference[oaicite:6]{index=6} :contentReference[oaicite:7]{index=7}

  // 0x00–0x03: 保留为 KEY_RESERVED
  for (int i = 0x00; i <= 0x03; ++i) {
    table[i] = KEY_RESERVED;
  }

  // 字母键 0x04–0x1D
  table[0x04] = KEY_A;
  table[0x05] = KEY_B;
  table[0x06] = KEY_C;
  table[0x07] = KEY_D;
  table[0x08] = KEY_E;
  table[0x09] = KEY_F;
  table[0x0A] = KEY_G;
  table[0x0B] = KEY_H;
  table[0x0C] = KEY_I;
  table[0x0D] = KEY_J;
  table[0x0E] = KEY_K;
  table[0x0F] = KEY_L;
  table[0x10] = KEY_M;
  table[0x11] = KEY_N;
  table[0x12] = KEY_O;
  table[0x13] = KEY_P;
  table[0x14] = KEY_Q;
  table[0x15] = KEY_R;
  table[0x16] = KEY_S;
  table[0x17] = KEY_T;
  table[0x18] = KEY_U;
  table[0x19] = KEY_V;
  table[0x1A] = KEY_W;
  table[0x1B] = KEY_X;
  table[0x1C] = KEY_Y;
  table[0x1D] = KEY_Z;

  // 数字键 0x1E–0x27
  table[0x1E] = KEY_1;
  table[0x1F] = KEY_2;
  table[0x20] = KEY_3;
  table[0x21] = KEY_4;
  table[0x22] = KEY_5;
  table[0x23] = KEY_6;
  table[0x24] = KEY_7;
  table[0x25] = KEY_8;
  table[0x26] = KEY_9;
  table[0x27] = KEY_0;

  // 控制键 0x28–0x38
  table[0x28] = KEY_ENTER;
  table[0x29] = KEY_ESC;
  table[0x2A] = KEY_BACKSPACE;
  table[0x2B] = KEY_TAB;
  table[0x2C] = KEY_SPACE;
  table[0x2D] = KEY_MINUS;
  table[0x2E] = KEY_EQUAL;
  table[0x2F] = KEY_LEFTBRACE;
  table[0x30] = KEY_RIGHTBRACE;
  table[0x31] = KEY_BACKSLASH;
  table[0x32] = KEY_BACKSLASH;
  table[0x33] = KEY_SEMICOLON;
  table[0x34] = KEY_APOSTROPHE;
  table[0x35] = KEY_GRAVE;
  table[0x36] = KEY_COMMA;
  table[0x37] = KEY_DOT;
  table[0x38] = KEY_SLASH;

  // 功能键 0x39–0x45
  table[0x39] = KEY_CAPSLOCK;
  table[0x3A] = KEY_F1;
  table[0x3B] = KEY_F2;
  table[0x3C] = KEY_F3;
  table[0x3D] = KEY_F4;
  table[0x3E] = KEY_F5;
  table[0x3F] = KEY_F6;
  table[0x40] = KEY_F7;
  table[0x41] = KEY_F8;
  table[0x42] = KEY_F9;
  table[0x43] = KEY_F10;
  table[0x44] = KEY_F11;
  table[0x45] = KEY_F12;

  // 系统控制键 0x46–0x48
  table[0x46] = KEY_SYSRQ;
  table[0x47] = KEY_SCROLLLOCK;
  table[0x48] = KEY_PAUSE;

  // 导航键 0x49–0x52
  table[0x49] = KEY_INSERT;
  table[0x4A] = KEY_HOME;
  table[0x4B] = KEY_PAGEUP;
  table[0x4C] = KEY_DELETE;
  table[0x4D] = KEY_END;
  table[0x4E] = KEY_PAGEDOWN;
  table[0x4F] = KEY_RIGHT;
  table[0x50] = KEY_LEFT;
  table[0x51] = KEY_DOWN;
  table[0x52] = KEY_UP;

  // 小键盘 0x53–0x63
  table[0x53] = KEY_NUMLOCK;
  table[0x54] = KEY_KPSLASH;
  table[0x55] = KEY_KPASTERISK;
  table[0x56] = KEY_KPMINUS;
  table[0x57] = KEY_KPPLUS;
  table[0x58] = KEY_KPENTER;
  table[0x59] = KEY_KP1;
  table[0x5A] = KEY_KP2;
  table[0x5B] = KEY_KP3;
  table[0x5C] = KEY_KP4;
  table[0x5D] = KEY_KP5;
  table[0x5E] = KEY_KP6;
  table[0x5F] = KEY_KP7;
  table[0x60] = KEY_KP8;
  table[0x61] = KEY_KP9;
  table[0x62] = KEY_KP0;
  table[0x63] = KEY_KPDOT;

  // AC Editing Keys 0x64–0x73
  table[0x64] = KEY_102ND;
  table[0x65] = KEY_COMPOSE;
  table[0x66] = KEY_POWER;
  table[0x67] = KEY_KPEQUAL;
  table[0x68] = KEY_F13;
  table[0x69] = KEY_F14;
  table[0x6A] = KEY_F15;
  table[0x6B] = KEY_F16;
  table[0x6C] = KEY_F17;
  table[0x6D] = KEY_F18;
  table[0x6E] = KEY_F19;
  table[0x6F] = KEY_F20;
  table[0x70] = KEY_F21;
  table[0x71] = KEY_F22;
  table[0x72] = KEY_F23;
  table[0x73] = KEY_F24;

  // 多媒体/系统控制 0x74–0x7A
  table[0x74] = KEY_OPEN;
  table[0x75] = KEY_HELP;
  table[0x76] = KEY_PROPS;
  table[0x77] = KEY_FRONT;
  table[0x78] = KEY_STOP;
  table[0x79] = KEY_AGAIN;
  table[0x7A] = KEY_UNDO;

  // 音量与查找 0x7B–0x81
  table[0x7B] = KEY_CUT;
  table[0x7C] = KEY_COPY;
  table[0x7D] = KEY_PASTE;
  table[0x7E] = KEY_FIND;
  table[0x7F] = KEY_MUTE;
  table[0x80] = KEY_VOLUMEDOWN;
  table[0x81] = KEY_VOLUMEUP;

  // 扩展修饰键 0xE0–0xE7
  table[0xE0] = KEY_LEFTCTRL;
  table[0xE1] = KEY_LEFTSHIFT;
  table[0xE2] = KEY_LEFTALT;
  table[0xE3] = KEY_LEFTMETA;
  table[0xE4] = KEY_RIGHTCTRL;
  table[0xE5] = KEY_RIGHTSHIFT;
  table[0xE6] = KEY_RIGHTALT;
  table[0xE7] = KEY_RIGHTMETA;

  return table;
}
} // namespace xwrap
