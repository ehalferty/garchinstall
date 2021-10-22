#include <stdio.h>
#include <string.h>
#include "keycode_names.h"
const char *keycode_to_key_name(unsigned int id) {
  if (id == 0) { return "RESERVED"; }
  else if (id == 1) { return "ESC"; }
  else if (id == 2) { return "1"; }
  else if (id == 3) { return "2"; }
  else if (id == 4) { return "3"; }
  else if (id == 5) { return "4"; }
  else if (id == 6) { return "5"; }
  else if (id == 7) { return "6"; }
  else if (id == 8) { return "7"; }
  else if (id == 9) { return "8"; }
  else if (id == 10) { return "9"; }
  else if (id == 11) { return "0"; }
  else if (id == 12) { return "MINUS"; }
  else if (id == 13) { return "EQUAL"; }
  else if (id == 14) { return "BACKSPACE"; }
  else if (id == 15) { return "TAB"; }
  else if (id == 16) { return "Q"; }
  else if (id == 17) { return "W"; }
  else if (id == 18) { return "E"; }
  else if (id == 19) { return "R"; }
  else if (id == 20) { return "T"; }
  else if (id == 21) { return "Y"; }
  else if (id == 22) { return "U"; }
  else if (id == 23) { return "I"; }
  else if (id == 24) { return "O"; }
  else if (id == 25) { return "P"; }
  else if (id == 26) { return "LEFTBRACE"; }
  else if (id == 27) { return "RIGHTBRACE"; }
  else if (id == 28) { return "ENTER"; }
  else if (id == 29) { return "LEFTCTRL"; }
  else if (id == 30) { return "A"; }
  else if (id == 31) { return "S"; }
  else if (id == 32) { return "D"; }
  else if (id == 33) { return "F"; }
  else if (id == 34) { return "G"; }
  else if (id == 35) { return "H"; }
  else if (id == 36) { return "J"; }
  else if (id == 37) { return "K"; }
  else if (id == 38) { return "L"; }
  else if (id == 39) { return "SEMICOLON"; }
  else if (id == 40) { return "APOSTROPHE"; }
  else if (id == 41) { return "GRAVE"; }
  else if (id == 42) { return "LEFTSHIFT"; }
  else if (id == 43) { return "BACKSLASH"; }
  else if (id == 44) { return "Z"; }
  else if (id == 45) { return "X"; }
  else if (id == 46) { return "C"; }
  else if (id == 47) { return "V"; }
  else if (id == 48) { return "B"; }
  else if (id == 49) { return "N"; }
  else if (id == 50) { return "M"; }
  else if (id == 51) { return "COMMA"; }
  else if (id == 52) { return "DOT"; }
  else if (id == 53) { return "SLASH"; }
  else if (id == 54) { return "RIGHTSHIFT"; }
  else if (id == 55) { return "KPASTERISK"; }
  else if (id == 56) { return "LEFTALT"; }
  else if (id == 57) { return "SPACE"; }
  else if (id == 58) { return "CAPSLOCK"; }
  else if (id == 59) { return "F1"; }
  else if (id == 60) { return "F2"; }
  else if (id == 61) { return "F3"; }
  else if (id == 62) { return "F4"; }
  else if (id == 63) { return "F5"; }
  else if (id == 64) { return "F6"; }
  else if (id == 65) { return "F7"; }
  else if (id == 66) { return "F8"; }
  else if (id == 67) { return "F9"; }
  else if (id == 68) { return "F10"; }
  else if (id == 69) { return "NUMLOCK"; }
  else if (id == 70) { return "SCROLLLOCK"; }
  else if (id == 71) { return "KP7"; }
  else if (id == 72) { return "KP8"; }
  else if (id == 73) { return "KP9"; }
  else if (id == 74) { return "KPMINUS"; }
  else if (id == 75) { return "KP4"; }
  else if (id == 76) { return "KP5"; }
  else if (id == 77) { return "KP6"; }
  else if (id == 78) { return "KPPLUS"; }
  else if (id == 79) { return "KP1"; }
  else if (id == 80) { return "KP2"; }
  else if (id == 81) { return "KP3"; }
  else if (id == 82) { return "KP0"; }
  else if (id == 83) { return "KPDOT"; }
  else if (id == 85) { return "ZENKAKUHANKAKU"; }
  else if (id == 86) { return "102ND"; }
  else if (id == 87) { return "F11"; }
  else if (id == 88) { return "F12"; }
  else if (id == 89) { return "RO"; }
  else if (id == 90) { return "KATAKANA"; }
  else if (id == 91) { return "HIRAGANA"; }
  else if (id == 92) { return "HENKAN"; }
  else if (id == 93) { return "KATAKANAHIRAGANA"; }
  else if (id == 94) { return "MUHENKAN"; }
  else if (id == 95) { return "KPJPCOMMA"; }
  else if (id == 96) { return "KPENTER"; }
  else if (id == 97) { return "RIGHTCTRL"; }
  else if (id == 98) { return "KPSLASH"; }
  else if (id == 99) { return "SYSRQ"; }
  else if (id == 100) { return "RIGHTALT"; }
  else if (id == 101) { return "LINEFEED"; }
  else if (id == 102) { return "HOME"; }
  else if (id == 103) { return "UP"; }
  else if (id == 104) { return "PAGEUP"; }
  else if (id == 105) { return "LEFT"; }
  else if (id == 106) { return "RIGHT"; }
  else if (id == 107) { return "END"; }
  else if (id == 108) { return "DOWN"; }
  else if (id == 109) { return "PAGEDOWN"; }
  else if (id == 110) { return "INSERT"; }
  else if (id == 111) { return "DELETE"; }
  else if (id == 112) { return "MACRO"; }
  else if (id == 113) { return "MUTE"; }
  else if (id == 114) { return "VOLUMEDOWN"; }
  else if (id == 115) { return "VOLUMEUP"; }
  else if (id == 116) { return "POWER"; }
  else if (id == 117) { return "KPEQUAL"; }
  else if (id == 118) { return "KPPLUSMINUS"; }
  else if (id == 119) { return "PAUSE"; }
  else if (id == 120) { return "SCALE"; }
  else if (id == 121) { return "KPCOMMA"; }
  else if (id == 122) { return "HANGEUL"; }
  else if (id == 0) { return "HANGUEL"; }
  else if (id == 123) { return "HANJA"; }
  else if (id == 124) { return "YEN"; }
  else if (id == 125) { return "LEFTMETA"; }
  else if (id == 126) { return "RIGHTMETA"; }
  else if (id == 127) { return "COMPOSE"; }
  else if (id == 128) { return "STOP"; }
  else if (id == 129) { return "AGAIN"; }
  else if (id == 130) { return "PROPS"; }
  else if (id == 131) { return "UNDO"; }
  else if (id == 132) { return "FRONT"; }
  else if (id == 133) { return "COPY"; }
  else if (id == 134) { return "OPEN"; }
  else if (id == 135) { return "PASTE"; }
  else if (id == 136) { return "FIND"; }
  else if (id == 137) { return "CUT"; }
  else if (id == 138) { return "HELP"; }
  else if (id == 139) { return "MENU"; }
  else if (id == 140) { return "CALC"; }
  else if (id == 141) { return "SETUP"; }
  else if (id == 142) { return "SLEEP"; }
  else if (id == 143) { return "WAKEUP"; }
  else if (id == 144) { return "FILE"; }
  else if (id == 145) { return "SENDFILE"; }
  else if (id == 146) { return "DELETEFILE"; }
  else if (id == 147) { return "XFER"; }
  else if (id == 148) { return "PROG1"; }
  else if (id == 149) { return "PROG2"; }
  else if (id == 150) { return "WWW"; }
  else if (id == 151) { return "MSDOS"; }
  else if (id == 152) { return "COFFEE"; }
  else if (id == 0) { return "SCREENLOCK"; }
  else if (id == 153) { return "ROTATE_DISPLAY"; }
  else if (id == 0) { return "DIRECTION"; }
  else if (id == 154) { return "CYCLEWINDOWS"; }
  else if (id == 155) { return "MAIL"; }
  else if (id == 156) { return "BOOKMARKS"; }
  else if (id == 157) { return "COMPUTER"; }
  else if (id == 158) { return "BACK"; }
  else if (id == 159) { return "FORWARD"; }
  else if (id == 160) { return "CLOSECD"; }
  else if (id == 161) { return "EJECTCD"; }
  else if (id == 162) { return "EJECTCLOSECD"; }
  else if (id == 163) { return "NEXTSONG"; }
  else if (id == 164) { return "PLAYPAUSE"; }
  else if (id == 165) { return "PREVIOUSSONG"; }
  else if (id == 166) { return "STOPCD"; }
  else if (id == 167) { return "RECORD"; }
  else if (id == 168) { return "REWIND"; }
  else if (id == 169) { return "PHONE"; }
  else if (id == 170) { return "ISO"; }
  else if (id == 171) { return "CONFIG"; }
  else if (id == 172) { return "HOMEPAGE"; }
  else if (id == 173) { return "REFRESH"; }
  else if (id == 174) { return "EXIT"; }
  else if (id == 175) { return "MOVE"; }
  else if (id == 176) { return "EDIT"; }
  else if (id == 177) { return "SCROLLUP"; }
  else if (id == 178) { return "SCROLLDOWN"; }
  else if (id == 179) { return "KPLEFTPAREN"; }
  else if (id == 180) { return "KPRIGHTPAREN"; }
  else if (id == 181) { return "NEW"; }
  else if (id == 182) { return "REDO"; }
  else if (id == 183) { return "F13"; }
  else if (id == 184) { return "F14"; }
  else if (id == 185) { return "F15"; }
  else if (id == 186) { return "F16"; }
  else if (id == 187) { return "F17"; }
  else if (id == 188) { return "F18"; }
  else if (id == 189) { return "F19"; }
  else if (id == 190) { return "F20"; }
  else if (id == 191) { return "F21"; }
  else if (id == 192) { return "F22"; }
  else if (id == 193) { return "F23"; }
  else if (id == 194) { return "F24"; }
  else if (id == 200) { return "PLAYCD"; }
  else if (id == 201) { return "PAUSECD"; }
  else if (id == 202) { return "PROG3"; }
  else if (id == 203) { return "PROG4"; }
  else if (id == 204) { return "DASHBOARD"; }
  else if (id == 205) { return "SUSPEND"; }
  else if (id == 206) { return "CLOSE"; }
  else if (id == 207) { return "PLAY"; }
  else if (id == 208) { return "FASTFORWARD"; }
  else if (id == 209) { return "BASSBOOST"; }
  else if (id == 210) { return "PRINT"; }
  else if (id == 211) { return "HP"; }
  else if (id == 212) { return "CAMERA"; }
  else if (id == 213) { return "SOUND"; }
  else if (id == 214) { return "QUESTION"; }
  else if (id == 215) { return "EMAIL"; }
  else if (id == 216) { return "CHAT"; }
  else if (id == 217) { return "SEARCH"; }
  else if (id == 218) { return "CONNECT"; }
  else if (id == 219) { return "FINANCE"; }
  else if (id == 220) { return "SPORT"; }
  else if (id == 221) { return "SHOP"; }
  else if (id == 222) { return "ALTERASE"; }
  else if (id == 223) { return "CANCEL"; }
  else if (id == 224) { return "BRIGHTNESSDOWN"; }
  else if (id == 225) { return "BRIGHTNESSUP"; }
  else if (id == 226) { return "MEDIA"; }
  else if (id == 227) { return "SWITCHVIDEOMODE"; }
  else if (id == 228) { return "KBDILLUMTOGGLE"; }
  else if (id == 229) { return "KBDILLUMDOWN"; }
  else if (id == 230) { return "KBDILLUMUP"; }
  else if (id == 231) { return "SEND"; }
  else if (id == 232) { return "REPLY"; }
  else if (id == 233) { return "FORWARDMAIL"; }
  else if (id == 234) { return "SAVE"; }
  else if (id == 235) { return "DOCUMENTS"; }
  else if (id == 236) { return "BATTERY"; }
  else if (id == 237) { return "BLUETOOTH"; }
  else if (id == 238) { return "WLAN"; }
  else if (id == 239) { return "UWB"; }
  else if (id == 240) { return "UNKNOWN"; }
  else if (id == 241) { return "VIDEO_NEXT"; }
  else if (id == 242) { return "VIDEO_PREV"; }
  else if (id == 243) { return "BRIGHTNESS_CYCLE"; }
  else if (id == 244) { return "BRIGHTNESS_AUTO"; }
  else if (id == 0) { return "BRIGHTNESS_ZERO"; }
  else if (id == 245) { return "DISPLAY_OFF"; }
  else if (id == 246) { return "WWAN"; }
  else if (id == 0) { return "WIMAX"; }
  else if (id == 247) { return "RFKILL"; }
  else if (id == 248) { return "MICMUTE"; }
  else if (id == 352) { return "OK"; }
  else if (id == 353) { return "SELECT"; }
  else if (id == 354) { return "GOTO"; }
  else if (id == 355) { return "CLEAR"; }
  else if (id == 356) { return "POWER2"; }
  else if (id == 357) { return "OPTION"; }
  else if (id == 358) { return "INFO"; }
  else if (id == 359) { return "TIME"; }
  else if (id == 360) { return "VENDOR"; }
  else if (id == 361) { return "ARCHIVE"; }
  else if (id == 362) { return "PROGRAM"; }
  else if (id == 363) { return "CHANNEL"; }
  else if (id == 364) { return "FAVORITES"; }
  else if (id == 365) { return "EPG"; }
  else if (id == 366) { return "PVR"; }
  else if (id == 367) { return "MHP"; }
  else if (id == 368) { return "LANGUAGE"; }
  else if (id == 369) { return "TITLE"; }
  else if (id == 370) { return "SUBTITLE"; }
  else if (id == 371) { return "ANGLE"; }
  else if (id == 372) { return "FULL_SCREEN"; }
  else if (id == 0) { return "ZOOM"; }
  else if (id == 373) { return "MODE"; }
  else if (id == 374) { return "KEYBOARD"; }
  else if (id == 375) { return "ASPECT_RATIO"; }
  else if (id == 0) { return "SCREEN"; }
  else if (id == 376) { return "PC"; }
  else if (id == 377) { return "TV"; }
  else if (id == 378) { return "TV2"; }
  else if (id == 379) { return "VCR"; }
  else if (id == 380) { return "VCR2"; }
  else if (id == 381) { return "SAT"; }
  else if (id == 382) { return "SAT2"; }
  else if (id == 383) { return "CD"; }
  else if (id == 384) { return "TAPE"; }
  else if (id == 385) { return "RADIO"; }
  else if (id == 386) { return "TUNER"; }
  else if (id == 387) { return "PLAYER"; }
  else if (id == 388) { return "TEXT"; }
  else if (id == 389) { return "DVD"; }
  else if (id == 390) { return "AUX"; }
  else if (id == 391) { return "MP3"; }
  else if (id == 392) { return "AUDIO"; }
  else if (id == 393) { return "VIDEO"; }
  else if (id == 394) { return "DIRECTORY"; }
  else if (id == 395) { return "LIST"; }
  else if (id == 396) { return "MEMO"; }
  else if (id == 397) { return "CALENDAR"; }
  else if (id == 398) { return "RED"; }
  else if (id == 399) { return "GREEN"; }
  else if (id == 400) { return "YELLOW"; }
  else if (id == 401) { return "BLUE"; }
  else if (id == 402) { return "CHANNELUP"; }
  else if (id == 403) { return "CHANNELDOWN"; }
  else if (id == 404) { return "FIRST"; }
  else if (id == 405) { return "LAST"; }
  else if (id == 406) { return "AB"; }
  else if (id == 407) { return "NEXT"; }
  else if (id == 408) { return "RESTART"; }
  else if (id == 409) { return "SLOW"; }
  else if (id == 410) { return "SHUFFLE"; }
  else if (id == 411) { return "BREAK"; }
  else if (id == 412) { return "PREVIOUS"; }
  else if (id == 413) { return "DIGITS"; }
  else if (id == 414) { return "TEEN"; }
  else if (id == 415) { return "TWEN"; }
  else if (id == 416) { return "VIDEOPHONE"; }
  else if (id == 417) { return "GAMES"; }
  else if (id == 418) { return "ZOOMIN"; }
  else if (id == 419) { return "ZOOMOUT"; }
  else if (id == 420) { return "ZOOMRESET"; }
  else if (id == 421) { return "WORDPROCESSOR"; }
  else if (id == 422) { return "EDITOR"; }
  else if (id == 423) { return "SPREADSHEET"; }
  else if (id == 424) { return "GRAPHICSEDITOR"; }
  else if (id == 425) { return "PRESENTATION"; }
  else if (id == 426) { return "DATABASE"; }
  else if (id == 427) { return "NEWS"; }
  else if (id == 428) { return "VOICEMAIL"; }
  else if (id == 429) { return "ADDRESSBOOK"; }
  else if (id == 430) { return "MESSENGER"; }
  else if (id == 431) { return "DISPLAYTOGGLE"; }
  else if (id == 0) { return "BRIGHTNESS_TOGGLE"; }
  else if (id == 432) { return "SPELLCHECK"; }
  else if (id == 433) { return "LOGOFF"; }
  else if (id == 434) { return "DOLLAR"; }
  else if (id == 435) { return "EURO"; }
  else if (id == 436) { return "FRAMEBACK"; }
  else if (id == 437) { return "FRAMEFORWARD"; }
  else if (id == 438) { return "CONTEXT_MENU"; }
  else if (id == 439) { return "MEDIA_REPEAT"; }
  else if (id == 440) { return "10CHANNELSUP"; }
  else if (id == 441) { return "10CHANNELSDOWN"; }
  else if (id == 442) { return "IMAGES"; }
  else if (id == 444) { return "NOTIFICATION_CENTER"; }
  else if (id == 445) { return "PICKUP_PHONE"; }
  else if (id == 446) { return "HANGUP_PHONE"; }
  else if (id == 448) { return "DEL_EOL"; }
  else if (id == 449) { return "DEL_EOS"; }
  else if (id == 450) { return "INS_LINE"; }
  else if (id == 451) { return "DEL_LINE"; }
  else if (id == 464) { return "FN"; }
  else if (id == 465) { return "FN_ESC"; }
  else if (id == 466) { return "FN_F1"; }
  else if (id == 467) { return "FN_F2"; }
  else if (id == 468) { return "FN_F3"; }
  else if (id == 469) { return "FN_F4"; }
  else if (id == 470) { return "FN_F5"; }
  else if (id == 471) { return "FN_F6"; }
  else if (id == 472) { return "FN_F7"; }
  else if (id == 473) { return "FN_F8"; }
  else if (id == 474) { return "FN_F9"; }
  else if (id == 475) { return "FN_F10"; }
  else if (id == 476) { return "FN_F11"; }
  else if (id == 477) { return "FN_F12"; }
  else if (id == 478) { return "FN_1"; }
  else if (id == 479) { return "FN_2"; }
  else if (id == 480) { return "FN_D"; }
  else if (id == 481) { return "FN_E"; }
  else if (id == 482) { return "FN_F"; }
  else if (id == 483) { return "FN_S"; }
  else if (id == 484) { return "FN_B"; }
  else if (id == 485) { return "FN_RIGHT_SHIFT"; }
  else if (id == 497) { return "BRL_DOT1"; }
  else if (id == 498) { return "BRL_DOT2"; }
  else if (id == 499) { return "BRL_DOT3"; }
  else if (id == 500) { return "BRL_DOT4"; }
  else if (id == 501) { return "BRL_DOT5"; }
  else if (id == 502) { return "BRL_DOT6"; }
  else if (id == 503) { return "BRL_DOT7"; }
  else if (id == 504) { return "BRL_DOT8"; }
  else if (id == 505) { return "BRL_DOT9"; }
  else if (id == 506) { return "BRL_DOT10"; }
  else if (id == 512) { return "NUMERIC_0"; }
  else if (id == 513) { return "NUMERIC_1"; }
  else if (id == 514) { return "NUMERIC_2"; }
  else if (id == 515) { return "NUMERIC_3"; }
  else if (id == 516) { return "NUMERIC_4"; }
  else if (id == 517) { return "NUMERIC_5"; }
  else if (id == 518) { return "NUMERIC_6"; }
  else if (id == 519) { return "NUMERIC_7"; }
  else if (id == 520) { return "NUMERIC_8"; }
  else if (id == 521) { return "NUMERIC_9"; }
  else if (id == 522) { return "NUMERIC_STAR"; }
  else if (id == 523) { return "NUMERIC_POUND"; }
  else if (id == 524) { return "NUMERIC_A"; }
  else if (id == 525) { return "NUMERIC_B"; }
  else if (id == 526) { return "NUMERIC_C"; }
  else if (id == 527) { return "NUMERIC_D"; }
  else if (id == 528) { return "CAMERA_FOCUS"; }
  else if (id == 529) { return "WPS_BUTTON"; }
  else if (id == 530) { return "TOUCHPAD_TOGGLE"; }
  else if (id == 531) { return "TOUCHPAD_ON"; }
  else if (id == 532) { return "TOUCHPAD_OFF"; }
  else if (id == 533) { return "CAMERA_ZOOMIN"; }
  else if (id == 534) { return "CAMERA_ZOOMOUT"; }
  else if (id == 535) { return "CAMERA_UP"; }
  else if (id == 536) { return "CAMERA_DOWN"; }
  else if (id == 537) { return "CAMERA_LEFT"; }
  else if (id == 538) { return "CAMERA_RIGHT"; }
  else if (id == 539) { return "ATTENDANT_ON"; }
  else if (id == 540) { return "ATTENDANT_OFF"; }
  else if (id == 541) { return "ATTENDANT_TOGGLE"; }
  else if (id == 542) { return "LIGHTS_TOGGLE"; }
  else if (id == 560) { return "ALS_TOGGLE"; }
  else if (id == 561) { return "ROTATE_LOCK_TOGGLE"; }
  else if (id == 576) { return "BUTTONCONFIG"; }
  else if (id == 577) { return "TASKMANAGER"; }
  else if (id == 578) { return "JOURNAL"; }
  else if (id == 579) { return "CONTROLPANEL"; }
  else if (id == 580) { return "APPSELECT"; }
  else if (id == 581) { return "SCREENSAVER"; }
  else if (id == 582) { return "VOICECOMMAND"; }
  else if (id == 583) { return "ASSISTANT"; }
  else if (id == 584) { return "KBD_LAYOUT_NEXT"; }
  else if (id == 585) { return "EMOJI_PICKER"; }
  else if (id == 592) { return "BRIGHTNESS_MIN"; }
  else if (id == 593) { return "BRIGHTNESS_MAX"; }
  else if (id == 608) { return "KBDINPUTASSIST_PREV"; }
  else if (id == 609) { return "KBDINPUTASSIST_NEXT"; }
  else if (id == 610) { return "KBDINPUTASSIST_PREVGROUP"; }
  else if (id == 611) { return "KBDINPUTASSIST_NEXTGROUP"; }
  else if (id == 612) { return "KBDINPUTASSIST_ACCEPT"; }
  else if (id == 613) { return "KBDINPUTASSIST_CANCEL"; }
  else if (id == 614) { return "RIGHT_UP"; }
  else if (id == 615) { return "RIGHT_DOWN"; }
  else if (id == 616) { return "LEFT_UP"; }
  else if (id == 617) { return "LEFT_DOWN"; }
  else if (id == 618) { return "ROOT_MENU"; }
  else if (id == 619) { return "MEDIA_TOP_MENU"; }
  else if (id == 620) { return "NUMERIC_11"; }
  else if (id == 621) { return "NUMERIC_12"; }
  else if (id == 622) { return "AUDIO_DESC"; }
  else if (id == 623) { return "3D_MODE"; }
  else if (id == 624) { return "NEXT_FAVORITE"; }
  else if (id == 625) { return "STOP_RECORD"; }
  else if (id == 626) { return "PAUSE_RECORD"; }
  else if (id == 627) { return "VOD"; }
  else if (id == 628) { return "UNMUTE"; }
  else if (id == 629) { return "FASTREVERSE"; }
  else if (id == 630) { return "SLOWREVERSE"; }
  else if (id == 631) { return "DATA"; }
  else if (id == 632) { return "ONSCREEN_KEYBOARD"; }
  else if (id == 633) { return "PRIVACY_SCREEN_TOGGLE"; }
  else if (id == 634) { return "SELECTIVE_SCREENSHOT"; }
  else if (id == 656) { return "MACRO1"; }
  else if (id == 657) { return "MACRO2"; }
  else if (id == 658) { return "MACRO3"; }
  else if (id == 659) { return "MACRO4"; }
  else if (id == 660) { return "MACRO5"; }
  else if (id == 661) { return "MACRO6"; }
  else if (id == 662) { return "MACRO7"; }
  else if (id == 663) { return "MACRO8"; }
  else if (id == 664) { return "MACRO9"; }
  else if (id == 665) { return "MACRO10"; }
  else if (id == 666) { return "MACRO11"; }
  else if (id == 667) { return "MACRO12"; }
  else if (id == 668) { return "MACRO13"; }
  else if (id == 669) { return "MACRO14"; }
  else if (id == 670) { return "MACRO15"; }
  else if (id == 671) { return "MACRO16"; }
  else if (id == 672) { return "MACRO17"; }
  else if (id == 673) { return "MACRO18"; }
  else if (id == 674) { return "MACRO19"; }
  else if (id == 675) { return "MACRO20"; }
  else if (id == 676) { return "MACRO21"; }
  else if (id == 677) { return "MACRO22"; }
  else if (id == 678) { return "MACRO23"; }
  else if (id == 679) { return "MACRO24"; }
  else if (id == 680) { return "MACRO25"; }
  else if (id == 681) { return "MACRO26"; }
  else if (id == 682) { return "MACRO27"; }
  else if (id == 683) { return "MACRO28"; }
  else if (id == 684) { return "MACRO29"; }
  else if (id == 685) { return "MACRO30"; }
  else if (id == 688) { return "MACRO_RECORD_START"; }
  else if (id == 689) { return "MACRO_RECORD_STOP"; }
  else if (id == 690) { return "MACRO_PRESET_CYCLE"; }
  else if (id == 691) { return "MACRO_PRESET1"; }
  else if (id == 692) { return "MACRO_PRESET2"; }
  else if (id == 693) { return "MACRO_PRESET3"; }
  else if (id == 696) { return "KBD_LCD_MENU1"; }
  else if (id == 697) { return "KBD_LCD_MENU2"; }
  else if (id == 698) { return "KBD_LCD_MENU3"; }
  else if (id == 699) { return "KBD_LCD_MENU4"; }
  else if (id == 700) { return "KBD_LCD_MENU5"; }
  else if (id == 0) { return "MIN_INTERESTING"; }
  else if (id == 767) { return "MAX"; }
  return (const char *)0;
}
int key_name_to_keycode(const char *name) {
  if (0 == strncmp(name, "RESERVED", (unsigned long int)9)) { return 0; }
  else if (0 == strncmp(name, "ESC", (unsigned long int)4)) { return 1; }
  else if (0 == strncmp(name, "1", (unsigned long int)2)) { return 2; }
  else if (0 == strncmp(name, "2", (unsigned long int)2)) { return 3; }
  else if (0 == strncmp(name, "3", (unsigned long int)2)) { return 4; }
  else if (0 == strncmp(name, "4", (unsigned long int)2)) { return 5; }
  else if (0 == strncmp(name, "5", (unsigned long int)2)) { return 6; }
  else if (0 == strncmp(name, "6", (unsigned long int)2)) { return 7; }
  else if (0 == strncmp(name, "7", (unsigned long int)2)) { return 8; }
  else if (0 == strncmp(name, "8", (unsigned long int)2)) { return 9; }
  else if (0 == strncmp(name, "9", (unsigned long int)2)) { return 10; }
  else if (0 == strncmp(name, "0", (unsigned long int)2)) { return 11; }
  else if (0 == strncmp(name, "MINUS", (unsigned long int)6)) { return 12; }
  else if (0 == strncmp(name, "EQUAL", (unsigned long int)6)) { return 13; }
  else if (0 == strncmp(name, "BACKSPACE", (unsigned long int)10)) { return 14; }
  else if (0 == strncmp(name, "TAB", (unsigned long int)4)) { return 15; }
  else if (0 == strncmp(name, "Q", (unsigned long int)2)) { return 16; }
  else if (0 == strncmp(name, "W", (unsigned long int)2)) { return 17; }
  else if (0 == strncmp(name, "E", (unsigned long int)2)) { return 18; }
  else if (0 == strncmp(name, "R", (unsigned long int)2)) { return 19; }
  else if (0 == strncmp(name, "T", (unsigned long int)2)) { return 20; }
  else if (0 == strncmp(name, "Y", (unsigned long int)2)) { return 21; }
  else if (0 == strncmp(name, "U", (unsigned long int)2)) { return 22; }
  else if (0 == strncmp(name, "I", (unsigned long int)2)) { return 23; }
  else if (0 == strncmp(name, "O", (unsigned long int)2)) { return 24; }
  else if (0 == strncmp(name, "P", (unsigned long int)2)) { return 25; }
  else if (0 == strncmp(name, "LEFTBRACE", (unsigned long int)10)) { return 26; }
  else if (0 == strncmp(name, "RIGHTBRACE", (unsigned long int)11)) { return 27; }
  else if (0 == strncmp(name, "ENTER", (unsigned long int)6)) { return 28; }
  else if (0 == strncmp(name, "LEFTCTRL", (unsigned long int)9)) { return 29; }
  else if (0 == strncmp(name, "A", (unsigned long int)2)) { return 30; }
  else if (0 == strncmp(name, "S", (unsigned long int)2)) { return 31; }
  else if (0 == strncmp(name, "D", (unsigned long int)2)) { return 32; }
  else if (0 == strncmp(name, "F", (unsigned long int)2)) { return 33; }
  else if (0 == strncmp(name, "G", (unsigned long int)2)) { return 34; }
  else if (0 == strncmp(name, "H", (unsigned long int)2)) { return 35; }
  else if (0 == strncmp(name, "J", (unsigned long int)2)) { return 36; }
  else if (0 == strncmp(name, "K", (unsigned long int)2)) { return 37; }
  else if (0 == strncmp(name, "L", (unsigned long int)2)) { return 38; }
  else if (0 == strncmp(name, "SEMICOLON", (unsigned long int)10)) { return 39; }
  else if (0 == strncmp(name, "APOSTROPHE", (unsigned long int)11)) { return 40; }
  else if (0 == strncmp(name, "GRAVE", (unsigned long int)6)) { return 41; }
  else if (0 == strncmp(name, "LEFTSHIFT", (unsigned long int)10)) { return 42; }
  else if (0 == strncmp(name, "BACKSLASH", (unsigned long int)10)) { return 43; }
  else if (0 == strncmp(name, "Z", (unsigned long int)2)) { return 44; }
  else if (0 == strncmp(name, "X", (unsigned long int)2)) { return 45; }
  else if (0 == strncmp(name, "C", (unsigned long int)2)) { return 46; }
  else if (0 == strncmp(name, "V", (unsigned long int)2)) { return 47; }
  else if (0 == strncmp(name, "B", (unsigned long int)2)) { return 48; }
  else if (0 == strncmp(name, "N", (unsigned long int)2)) { return 49; }
  else if (0 == strncmp(name, "M", (unsigned long int)2)) { return 50; }
  else if (0 == strncmp(name, "COMMA", (unsigned long int)6)) { return 51; }
  else if (0 == strncmp(name, "DOT", (unsigned long int)4)) { return 52; }
  else if (0 == strncmp(name, "SLASH", (unsigned long int)6)) { return 53; }
  else if (0 == strncmp(name, "RIGHTSHIFT", (unsigned long int)11)) { return 54; }
  else if (0 == strncmp(name, "KPASTERISK", (unsigned long int)11)) { return 55; }
  else if (0 == strncmp(name, "LEFTALT", (unsigned long int)8)) { return 56; }
  else if (0 == strncmp(name, "SPACE", (unsigned long int)6)) { return 57; }
  else if (0 == strncmp(name, "CAPSLOCK", (unsigned long int)9)) { return 58; }
  else if (0 == strncmp(name, "F1", (unsigned long int)3)) { return 59; }
  else if (0 == strncmp(name, "F2", (unsigned long int)3)) { return 60; }
  else if (0 == strncmp(name, "F3", (unsigned long int)3)) { return 61; }
  else if (0 == strncmp(name, "F4", (unsigned long int)3)) { return 62; }
  else if (0 == strncmp(name, "F5", (unsigned long int)3)) { return 63; }
  else if (0 == strncmp(name, "F6", (unsigned long int)3)) { return 64; }
  else if (0 == strncmp(name, "F7", (unsigned long int)3)) { return 65; }
  else if (0 == strncmp(name, "F8", (unsigned long int)3)) { return 66; }
  else if (0 == strncmp(name, "F9", (unsigned long int)3)) { return 67; }
  else if (0 == strncmp(name, "F10", (unsigned long int)4)) { return 68; }
  else if (0 == strncmp(name, "NUMLOCK", (unsigned long int)8)) { return 69; }
  else if (0 == strncmp(name, "SCROLLLOCK", (unsigned long int)11)) { return 70; }
  else if (0 == strncmp(name, "KP7", (unsigned long int)4)) { return 71; }
  else if (0 == strncmp(name, "KP8", (unsigned long int)4)) { return 72; }
  else if (0 == strncmp(name, "KP9", (unsigned long int)4)) { return 73; }
  else if (0 == strncmp(name, "KPMINUS", (unsigned long int)8)) { return 74; }
  else if (0 == strncmp(name, "KP4", (unsigned long int)4)) { return 75; }
  else if (0 == strncmp(name, "KP5", (unsigned long int)4)) { return 76; }
  else if (0 == strncmp(name, "KP6", (unsigned long int)4)) { return 77; }
  else if (0 == strncmp(name, "KPPLUS", (unsigned long int)7)) { return 78; }
  else if (0 == strncmp(name, "KP1", (unsigned long int)4)) { return 79; }
  else if (0 == strncmp(name, "KP2", (unsigned long int)4)) { return 80; }
  else if (0 == strncmp(name, "KP3", (unsigned long int)4)) { return 81; }
  else if (0 == strncmp(name, "KP0", (unsigned long int)4)) { return 82; }
  else if (0 == strncmp(name, "KPDOT", (unsigned long int)6)) { return 83; }
  else if (0 == strncmp(name, "ZENKAKUHANKAKU", (unsigned long int)15)) { return 85; }
  else if (0 == strncmp(name, "102ND", (unsigned long int)6)) { return 86; }
  else if (0 == strncmp(name, "F11", (unsigned long int)4)) { return 87; }
  else if (0 == strncmp(name, "F12", (unsigned long int)4)) { return 88; }
  else if (0 == strncmp(name, "RO", (unsigned long int)3)) { return 89; }
  else if (0 == strncmp(name, "KATAKANA", (unsigned long int)9)) { return 90; }
  else if (0 == strncmp(name, "HIRAGANA", (unsigned long int)9)) { return 91; }
  else if (0 == strncmp(name, "HENKAN", (unsigned long int)7)) { return 92; }
  else if (0 == strncmp(name, "KATAKANAHIRAGANA", (unsigned long int)17)) { return 93; }
  else if (0 == strncmp(name, "MUHENKAN", (unsigned long int)9)) { return 94; }
  else if (0 == strncmp(name, "KPJPCOMMA", (unsigned long int)10)) { return 95; }
  else if (0 == strncmp(name, "KPENTER", (unsigned long int)8)) { return 96; }
  else if (0 == strncmp(name, "RIGHTCTRL", (unsigned long int)10)) { return 97; }
  else if (0 == strncmp(name, "KPSLASH", (unsigned long int)8)) { return 98; }
  else if (0 == strncmp(name, "SYSRQ", (unsigned long int)6)) { return 99; }
  else if (0 == strncmp(name, "RIGHTALT", (unsigned long int)9)) { return 100; }
  else if (0 == strncmp(name, "LINEFEED", (unsigned long int)9)) { return 101; }
  else if (0 == strncmp(name, "HOME", (unsigned long int)5)) { return 102; }
  else if (0 == strncmp(name, "UP", (unsigned long int)3)) { return 103; }
  else if (0 == strncmp(name, "PAGEUP", (unsigned long int)7)) { return 104; }
  else if (0 == strncmp(name, "LEFT", (unsigned long int)5)) { return 105; }
  else if (0 == strncmp(name, "RIGHT", (unsigned long int)6)) { return 106; }
  else if (0 == strncmp(name, "END", (unsigned long int)4)) { return 107; }
  else if (0 == strncmp(name, "DOWN", (unsigned long int)5)) { return 108; }
  else if (0 == strncmp(name, "PAGEDOWN", (unsigned long int)9)) { return 109; }
  else if (0 == strncmp(name, "INSERT", (unsigned long int)7)) { return 110; }
  else if (0 == strncmp(name, "DELETE", (unsigned long int)7)) { return 111; }
  else if (0 == strncmp(name, "MACRO", (unsigned long int)6)) { return 112; }
  else if (0 == strncmp(name, "MUTE", (unsigned long int)5)) { return 113; }
  else if (0 == strncmp(name, "VOLUMEDOWN", (unsigned long int)11)) { return 114; }
  else if (0 == strncmp(name, "VOLUMEUP", (unsigned long int)9)) { return 115; }
  else if (0 == strncmp(name, "POWER", (unsigned long int)6)) { return 116; }
  else if (0 == strncmp(name, "KPEQUAL", (unsigned long int)8)) { return 117; }
  else if (0 == strncmp(name, "KPPLUSMINUS", (unsigned long int)12)) { return 118; }
  else if (0 == strncmp(name, "PAUSE", (unsigned long int)6)) { return 119; }
  else if (0 == strncmp(name, "SCALE", (unsigned long int)6)) { return 120; }
  else if (0 == strncmp(name, "KPCOMMA", (unsigned long int)8)) { return 121; }
  else if (0 == strncmp(name, "HANGEUL", (unsigned long int)8)) { return 122; }
  else if (0 == strncmp(name, "HANGUEL", (unsigned long int)8)) { return 0; }
  else if (0 == strncmp(name, "HANJA", (unsigned long int)6)) { return 123; }
  else if (0 == strncmp(name, "YEN", (unsigned long int)4)) { return 124; }
  else if (0 == strncmp(name, "LEFTMETA", (unsigned long int)9)) { return 125; }
  else if (0 == strncmp(name, "RIGHTMETA", (unsigned long int)10)) { return 126; }
  else if (0 == strncmp(name, "COMPOSE", (unsigned long int)8)) { return 127; }
  else if (0 == strncmp(name, "STOP", (unsigned long int)5)) { return 128; }
  else if (0 == strncmp(name, "AGAIN", (unsigned long int)6)) { return 129; }
  else if (0 == strncmp(name, "PROPS", (unsigned long int)6)) { return 130; }
  else if (0 == strncmp(name, "UNDO", (unsigned long int)5)) { return 131; }
  else if (0 == strncmp(name, "FRONT", (unsigned long int)6)) { return 132; }
  else if (0 == strncmp(name, "COPY", (unsigned long int)5)) { return 133; }
  else if (0 == strncmp(name, "OPEN", (unsigned long int)5)) { return 134; }
  else if (0 == strncmp(name, "PASTE", (unsigned long int)6)) { return 135; }
  else if (0 == strncmp(name, "FIND", (unsigned long int)5)) { return 136; }
  else if (0 == strncmp(name, "CUT", (unsigned long int)4)) { return 137; }
  else if (0 == strncmp(name, "HELP", (unsigned long int)5)) { return 138; }
  else if (0 == strncmp(name, "MENU", (unsigned long int)5)) { return 139; }
  else if (0 == strncmp(name, "CALC", (unsigned long int)5)) { return 140; }
  else if (0 == strncmp(name, "SETUP", (unsigned long int)6)) { return 141; }
  else if (0 == strncmp(name, "SLEEP", (unsigned long int)6)) { return 142; }
  else if (0 == strncmp(name, "WAKEUP", (unsigned long int)7)) { return 143; }
  else if (0 == strncmp(name, "FILE", (unsigned long int)5)) { return 144; }
  else if (0 == strncmp(name, "SENDFILE", (unsigned long int)9)) { return 145; }
  else if (0 == strncmp(name, "DELETEFILE", (unsigned long int)11)) { return 146; }
  else if (0 == strncmp(name, "XFER", (unsigned long int)5)) { return 147; }
  else if (0 == strncmp(name, "PROG1", (unsigned long int)6)) { return 148; }
  else if (0 == strncmp(name, "PROG2", (unsigned long int)6)) { return 149; }
  else if (0 == strncmp(name, "WWW", (unsigned long int)4)) { return 150; }
  else if (0 == strncmp(name, "MSDOS", (unsigned long int)6)) { return 151; }
  else if (0 == strncmp(name, "COFFEE", (unsigned long int)7)) { return 152; }
  else if (0 == strncmp(name, "SCREENLOCK", (unsigned long int)11)) { return 0; }
  else if (0 == strncmp(name, "ROTATE_DISPLAY", (unsigned long int)15)) { return 153; }
  else if (0 == strncmp(name, "DIRECTION", (unsigned long int)10)) { return 0; }
  else if (0 == strncmp(name, "CYCLEWINDOWS", (unsigned long int)13)) { return 154; }
  else if (0 == strncmp(name, "MAIL", (unsigned long int)5)) { return 155; }
  else if (0 == strncmp(name, "BOOKMARKS", (unsigned long int)10)) { return 156; }
  else if (0 == strncmp(name, "COMPUTER", (unsigned long int)9)) { return 157; }
  else if (0 == strncmp(name, "BACK", (unsigned long int)5)) { return 158; }
  else if (0 == strncmp(name, "FORWARD", (unsigned long int)8)) { return 159; }
  else if (0 == strncmp(name, "CLOSECD", (unsigned long int)8)) { return 160; }
  else if (0 == strncmp(name, "EJECTCD", (unsigned long int)8)) { return 161; }
  else if (0 == strncmp(name, "EJECTCLOSECD", (unsigned long int)13)) { return 162; }
  else if (0 == strncmp(name, "NEXTSONG", (unsigned long int)9)) { return 163; }
  else if (0 == strncmp(name, "PLAYPAUSE", (unsigned long int)10)) { return 164; }
  else if (0 == strncmp(name, "PREVIOUSSONG", (unsigned long int)13)) { return 165; }
  else if (0 == strncmp(name, "STOPCD", (unsigned long int)7)) { return 166; }
  else if (0 == strncmp(name, "RECORD", (unsigned long int)7)) { return 167; }
  else if (0 == strncmp(name, "REWIND", (unsigned long int)7)) { return 168; }
  else if (0 == strncmp(name, "PHONE", (unsigned long int)6)) { return 169; }
  else if (0 == strncmp(name, "ISO", (unsigned long int)4)) { return 170; }
  else if (0 == strncmp(name, "CONFIG", (unsigned long int)7)) { return 171; }
  else if (0 == strncmp(name, "HOMEPAGE", (unsigned long int)9)) { return 172; }
  else if (0 == strncmp(name, "REFRESH", (unsigned long int)8)) { return 173; }
  else if (0 == strncmp(name, "EXIT", (unsigned long int)5)) { return 174; }
  else if (0 == strncmp(name, "MOVE", (unsigned long int)5)) { return 175; }
  else if (0 == strncmp(name, "EDIT", (unsigned long int)5)) { return 176; }
  else if (0 == strncmp(name, "SCROLLUP", (unsigned long int)9)) { return 177; }
  else if (0 == strncmp(name, "SCROLLDOWN", (unsigned long int)11)) { return 178; }
  else if (0 == strncmp(name, "KPLEFTPAREN", (unsigned long int)12)) { return 179; }
  else if (0 == strncmp(name, "KPRIGHTPAREN", (unsigned long int)13)) { return 180; }
  else if (0 == strncmp(name, "NEW", (unsigned long int)4)) { return 181; }
  else if (0 == strncmp(name, "REDO", (unsigned long int)5)) { return 182; }
  else if (0 == strncmp(name, "F13", (unsigned long int)4)) { return 183; }
  else if (0 == strncmp(name, "F14", (unsigned long int)4)) { return 184; }
  else if (0 == strncmp(name, "F15", (unsigned long int)4)) { return 185; }
  else if (0 == strncmp(name, "F16", (unsigned long int)4)) { return 186; }
  else if (0 == strncmp(name, "F17", (unsigned long int)4)) { return 187; }
  else if (0 == strncmp(name, "F18", (unsigned long int)4)) { return 188; }
  else if (0 == strncmp(name, "F19", (unsigned long int)4)) { return 189; }
  else if (0 == strncmp(name, "F20", (unsigned long int)4)) { return 190; }
  else if (0 == strncmp(name, "F21", (unsigned long int)4)) { return 191; }
  else if (0 == strncmp(name, "F22", (unsigned long int)4)) { return 192; }
  else if (0 == strncmp(name, "F23", (unsigned long int)4)) { return 193; }
  else if (0 == strncmp(name, "F24", (unsigned long int)4)) { return 194; }
  else if (0 == strncmp(name, "PLAYCD", (unsigned long int)7)) { return 200; }
  else if (0 == strncmp(name, "PAUSECD", (unsigned long int)8)) { return 201; }
  else if (0 == strncmp(name, "PROG3", (unsigned long int)6)) { return 202; }
  else if (0 == strncmp(name, "PROG4", (unsigned long int)6)) { return 203; }
  else if (0 == strncmp(name, "DASHBOARD", (unsigned long int)10)) { return 204; }
  else if (0 == strncmp(name, "SUSPEND", (unsigned long int)8)) { return 205; }
  else if (0 == strncmp(name, "CLOSE", (unsigned long int)6)) { return 206; }
  else if (0 == strncmp(name, "PLAY", (unsigned long int)5)) { return 207; }
  else if (0 == strncmp(name, "FASTFORWARD", (unsigned long int)12)) { return 208; }
  else if (0 == strncmp(name, "BASSBOOST", (unsigned long int)10)) { return 209; }
  else if (0 == strncmp(name, "PRINT", (unsigned long int)6)) { return 210; }
  else if (0 == strncmp(name, "HP", (unsigned long int)3)) { return 211; }
  else if (0 == strncmp(name, "CAMERA", (unsigned long int)7)) { return 212; }
  else if (0 == strncmp(name, "SOUND", (unsigned long int)6)) { return 213; }
  else if (0 == strncmp(name, "QUESTION", (unsigned long int)9)) { return 214; }
  else if (0 == strncmp(name, "EMAIL", (unsigned long int)6)) { return 215; }
  else if (0 == strncmp(name, "CHAT", (unsigned long int)5)) { return 216; }
  else if (0 == strncmp(name, "SEARCH", (unsigned long int)7)) { return 217; }
  else if (0 == strncmp(name, "CONNECT", (unsigned long int)8)) { return 218; }
  else if (0 == strncmp(name, "FINANCE", (unsigned long int)8)) { return 219; }
  else if (0 == strncmp(name, "SPORT", (unsigned long int)6)) { return 220; }
  else if (0 == strncmp(name, "SHOP", (unsigned long int)5)) { return 221; }
  else if (0 == strncmp(name, "ALTERASE", (unsigned long int)9)) { return 222; }
  else if (0 == strncmp(name, "CANCEL", (unsigned long int)7)) { return 223; }
  else if (0 == strncmp(name, "BRIGHTNESSDOWN", (unsigned long int)15)) { return 224; }
  else if (0 == strncmp(name, "BRIGHTNESSUP", (unsigned long int)13)) { return 225; }
  else if (0 == strncmp(name, "MEDIA", (unsigned long int)6)) { return 226; }
  else if (0 == strncmp(name, "SWITCHVIDEOMODE", (unsigned long int)16)) { return 227; }
  else if (0 == strncmp(name, "KBDILLUMTOGGLE", (unsigned long int)15)) { return 228; }
  else if (0 == strncmp(name, "KBDILLUMDOWN", (unsigned long int)13)) { return 229; }
  else if (0 == strncmp(name, "KBDILLUMUP", (unsigned long int)11)) { return 230; }
  else if (0 == strncmp(name, "SEND", (unsigned long int)5)) { return 231; }
  else if (0 == strncmp(name, "REPLY", (unsigned long int)6)) { return 232; }
  else if (0 == strncmp(name, "FORWARDMAIL", (unsigned long int)12)) { return 233; }
  else if (0 == strncmp(name, "SAVE", (unsigned long int)5)) { return 234; }
  else if (0 == strncmp(name, "DOCUMENTS", (unsigned long int)10)) { return 235; }
  else if (0 == strncmp(name, "BATTERY", (unsigned long int)8)) { return 236; }
  else if (0 == strncmp(name, "BLUETOOTH", (unsigned long int)10)) { return 237; }
  else if (0 == strncmp(name, "WLAN", (unsigned long int)5)) { return 238; }
  else if (0 == strncmp(name, "UWB", (unsigned long int)4)) { return 239; }
  else if (0 == strncmp(name, "UNKNOWN", (unsigned long int)8)) { return 240; }
  else if (0 == strncmp(name, "VIDEO_NEXT", (unsigned long int)11)) { return 241; }
  else if (0 == strncmp(name, "VIDEO_PREV", (unsigned long int)11)) { return 242; }
  else if (0 == strncmp(name, "BRIGHTNESS_CYCLE", (unsigned long int)17)) { return 243; }
  else if (0 == strncmp(name, "BRIGHTNESS_AUTO", (unsigned long int)16)) { return 244; }
  else if (0 == strncmp(name, "BRIGHTNESS_ZERO", (unsigned long int)16)) { return 0; }
  else if (0 == strncmp(name, "DISPLAY_OFF", (unsigned long int)12)) { return 245; }
  else if (0 == strncmp(name, "WWAN", (unsigned long int)5)) { return 246; }
  else if (0 == strncmp(name, "WIMAX", (unsigned long int)6)) { return 0; }
  else if (0 == strncmp(name, "RFKILL", (unsigned long int)7)) { return 247; }
  else if (0 == strncmp(name, "MICMUTE", (unsigned long int)8)) { return 248; }
  else if (0 == strncmp(name, "OK", (unsigned long int)3)) { return 352; }
  else if (0 == strncmp(name, "SELECT", (unsigned long int)7)) { return 353; }
  else if (0 == strncmp(name, "GOTO", (unsigned long int)5)) { return 354; }
  else if (0 == strncmp(name, "CLEAR", (unsigned long int)6)) { return 355; }
  else if (0 == strncmp(name, "POWER2", (unsigned long int)7)) { return 356; }
  else if (0 == strncmp(name, "OPTION", (unsigned long int)7)) { return 357; }
  else if (0 == strncmp(name, "INFO", (unsigned long int)5)) { return 358; }
  else if (0 == strncmp(name, "TIME", (unsigned long int)5)) { return 359; }
  else if (0 == strncmp(name, "VENDOR", (unsigned long int)7)) { return 360; }
  else if (0 == strncmp(name, "ARCHIVE", (unsigned long int)8)) { return 361; }
  else if (0 == strncmp(name, "PROGRAM", (unsigned long int)8)) { return 362; }
  else if (0 == strncmp(name, "CHANNEL", (unsigned long int)8)) { return 363; }
  else if (0 == strncmp(name, "FAVORITES", (unsigned long int)10)) { return 364; }
  else if (0 == strncmp(name, "EPG", (unsigned long int)4)) { return 365; }
  else if (0 == strncmp(name, "PVR", (unsigned long int)4)) { return 366; }
  else if (0 == strncmp(name, "MHP", (unsigned long int)4)) { return 367; }
  else if (0 == strncmp(name, "LANGUAGE", (unsigned long int)9)) { return 368; }
  else if (0 == strncmp(name, "TITLE", (unsigned long int)6)) { return 369; }
  else if (0 == strncmp(name, "SUBTITLE", (unsigned long int)9)) { return 370; }
  else if (0 == strncmp(name, "ANGLE", (unsigned long int)6)) { return 371; }
  else if (0 == strncmp(name, "FULL_SCREEN", (unsigned long int)12)) { return 372; }
  else if (0 == strncmp(name, "ZOOM", (unsigned long int)5)) { return 0; }
  else if (0 == strncmp(name, "MODE", (unsigned long int)5)) { return 373; }
  else if (0 == strncmp(name, "KEYBOARD", (unsigned long int)9)) { return 374; }
  else if (0 == strncmp(name, "ASPECT_RATIO", (unsigned long int)13)) { return 375; }
  else if (0 == strncmp(name, "SCREEN", (unsigned long int)7)) { return 0; }
  else if (0 == strncmp(name, "PC", (unsigned long int)3)) { return 376; }
  else if (0 == strncmp(name, "TV", (unsigned long int)3)) { return 377; }
  else if (0 == strncmp(name, "TV2", (unsigned long int)4)) { return 378; }
  else if (0 == strncmp(name, "VCR", (unsigned long int)4)) { return 379; }
  else if (0 == strncmp(name, "VCR2", (unsigned long int)5)) { return 380; }
  else if (0 == strncmp(name, "SAT", (unsigned long int)4)) { return 381; }
  else if (0 == strncmp(name, "SAT2", (unsigned long int)5)) { return 382; }
  else if (0 == strncmp(name, "CD", (unsigned long int)3)) { return 383; }
  else if (0 == strncmp(name, "TAPE", (unsigned long int)5)) { return 384; }
  else if (0 == strncmp(name, "RADIO", (unsigned long int)6)) { return 385; }
  else if (0 == strncmp(name, "TUNER", (unsigned long int)6)) { return 386; }
  else if (0 == strncmp(name, "PLAYER", (unsigned long int)7)) { return 387; }
  else if (0 == strncmp(name, "TEXT", (unsigned long int)5)) { return 388; }
  else if (0 == strncmp(name, "DVD", (unsigned long int)4)) { return 389; }
  else if (0 == strncmp(name, "AUX", (unsigned long int)4)) { return 390; }
  else if (0 == strncmp(name, "MP3", (unsigned long int)4)) { return 391; }
  else if (0 == strncmp(name, "AUDIO", (unsigned long int)6)) { return 392; }
  else if (0 == strncmp(name, "VIDEO", (unsigned long int)6)) { return 393; }
  else if (0 == strncmp(name, "DIRECTORY", (unsigned long int)10)) { return 394; }
  else if (0 == strncmp(name, "LIST", (unsigned long int)5)) { return 395; }
  else if (0 == strncmp(name, "MEMO", (unsigned long int)5)) { return 396; }
  else if (0 == strncmp(name, "CALENDAR", (unsigned long int)9)) { return 397; }
  else if (0 == strncmp(name, "RED", (unsigned long int)4)) { return 398; }
  else if (0 == strncmp(name, "GREEN", (unsigned long int)6)) { return 399; }
  else if (0 == strncmp(name, "YELLOW", (unsigned long int)7)) { return 400; }
  else if (0 == strncmp(name, "BLUE", (unsigned long int)5)) { return 401; }
  else if (0 == strncmp(name, "CHANNELUP", (unsigned long int)10)) { return 402; }
  else if (0 == strncmp(name, "CHANNELDOWN", (unsigned long int)12)) { return 403; }
  else if (0 == strncmp(name, "FIRST", (unsigned long int)6)) { return 404; }
  else if (0 == strncmp(name, "LAST", (unsigned long int)5)) { return 405; }
  else if (0 == strncmp(name, "AB", (unsigned long int)3)) { return 406; }
  else if (0 == strncmp(name, "NEXT", (unsigned long int)5)) { return 407; }
  else if (0 == strncmp(name, "RESTART", (unsigned long int)8)) { return 408; }
  else if (0 == strncmp(name, "SLOW", (unsigned long int)5)) { return 409; }
  else if (0 == strncmp(name, "SHUFFLE", (unsigned long int)8)) { return 410; }
  else if (0 == strncmp(name, "BREAK", (unsigned long int)6)) { return 411; }
  else if (0 == strncmp(name, "PREVIOUS", (unsigned long int)9)) { return 412; }
  else if (0 == strncmp(name, "DIGITS", (unsigned long int)7)) { return 413; }
  else if (0 == strncmp(name, "TEEN", (unsigned long int)5)) { return 414; }
  else if (0 == strncmp(name, "TWEN", (unsigned long int)5)) { return 415; }
  else if (0 == strncmp(name, "VIDEOPHONE", (unsigned long int)11)) { return 416; }
  else if (0 == strncmp(name, "GAMES", (unsigned long int)6)) { return 417; }
  else if (0 == strncmp(name, "ZOOMIN", (unsigned long int)7)) { return 418; }
  else if (0 == strncmp(name, "ZOOMOUT", (unsigned long int)8)) { return 419; }
  else if (0 == strncmp(name, "ZOOMRESET", (unsigned long int)10)) { return 420; }
  else if (0 == strncmp(name, "WORDPROCESSOR", (unsigned long int)14)) { return 421; }
  else if (0 == strncmp(name, "EDITOR", (unsigned long int)7)) { return 422; }
  else if (0 == strncmp(name, "SPREADSHEET", (unsigned long int)12)) { return 423; }
  else if (0 == strncmp(name, "GRAPHICSEDITOR", (unsigned long int)15)) { return 424; }
  else if (0 == strncmp(name, "PRESENTATION", (unsigned long int)13)) { return 425; }
  else if (0 == strncmp(name, "DATABASE", (unsigned long int)9)) { return 426; }
  else if (0 == strncmp(name, "NEWS", (unsigned long int)5)) { return 427; }
  else if (0 == strncmp(name, "VOICEMAIL", (unsigned long int)10)) { return 428; }
  else if (0 == strncmp(name, "ADDRESSBOOK", (unsigned long int)12)) { return 429; }
  else if (0 == strncmp(name, "MESSENGER", (unsigned long int)10)) { return 430; }
  else if (0 == strncmp(name, "DISPLAYTOGGLE", (unsigned long int)14)) { return 431; }
  else if (0 == strncmp(name, "BRIGHTNESS_TOGGLE", (unsigned long int)18)) { return 0; }
  else if (0 == strncmp(name, "SPELLCHECK", (unsigned long int)11)) { return 432; }
  else if (0 == strncmp(name, "LOGOFF", (unsigned long int)7)) { return 433; }
  else if (0 == strncmp(name, "DOLLAR", (unsigned long int)7)) { return 434; }
  else if (0 == strncmp(name, "EURO", (unsigned long int)5)) { return 435; }
  else if (0 == strncmp(name, "FRAMEBACK", (unsigned long int)10)) { return 436; }
  else if (0 == strncmp(name, "FRAMEFORWARD", (unsigned long int)13)) { return 437; }
  else if (0 == strncmp(name, "CONTEXT_MENU", (unsigned long int)13)) { return 438; }
  else if (0 == strncmp(name, "MEDIA_REPEAT", (unsigned long int)13)) { return 439; }
  else if (0 == strncmp(name, "10CHANNELSUP", (unsigned long int)13)) { return 440; }
  else if (0 == strncmp(name, "10CHANNELSDOWN", (unsigned long int)15)) { return 441; }
  else if (0 == strncmp(name, "IMAGES", (unsigned long int)7)) { return 442; }
  else if (0 == strncmp(name, "NOTIFICATION_CENTER", (unsigned long int)20)) { return 444; }
  else if (0 == strncmp(name, "PICKUP_PHONE", (unsigned long int)13)) { return 445; }
  else if (0 == strncmp(name, "HANGUP_PHONE", (unsigned long int)13)) { return 446; }
  else if (0 == strncmp(name, "DEL_EOL", (unsigned long int)8)) { return 448; }
  else if (0 == strncmp(name, "DEL_EOS", (unsigned long int)8)) { return 449; }
  else if (0 == strncmp(name, "INS_LINE", (unsigned long int)9)) { return 450; }
  else if (0 == strncmp(name, "DEL_LINE", (unsigned long int)9)) { return 451; }
  else if (0 == strncmp(name, "FN", (unsigned long int)3)) { return 464; }
  else if (0 == strncmp(name, "FN_ESC", (unsigned long int)7)) { return 465; }
  else if (0 == strncmp(name, "FN_F1", (unsigned long int)6)) { return 466; }
  else if (0 == strncmp(name, "FN_F2", (unsigned long int)6)) { return 467; }
  else if (0 == strncmp(name, "FN_F3", (unsigned long int)6)) { return 468; }
  else if (0 == strncmp(name, "FN_F4", (unsigned long int)6)) { return 469; }
  else if (0 == strncmp(name, "FN_F5", (unsigned long int)6)) { return 470; }
  else if (0 == strncmp(name, "FN_F6", (unsigned long int)6)) { return 471; }
  else if (0 == strncmp(name, "FN_F7", (unsigned long int)6)) { return 472; }
  else if (0 == strncmp(name, "FN_F8", (unsigned long int)6)) { return 473; }
  else if (0 == strncmp(name, "FN_F9", (unsigned long int)6)) { return 474; }
  else if (0 == strncmp(name, "FN_F10", (unsigned long int)7)) { return 475; }
  else if (0 == strncmp(name, "FN_F11", (unsigned long int)7)) { return 476; }
  else if (0 == strncmp(name, "FN_F12", (unsigned long int)7)) { return 477; }
  else if (0 == strncmp(name, "FN_1", (unsigned long int)5)) { return 478; }
  else if (0 == strncmp(name, "FN_2", (unsigned long int)5)) { return 479; }
  else if (0 == strncmp(name, "FN_D", (unsigned long int)5)) { return 480; }
  else if (0 == strncmp(name, "FN_E", (unsigned long int)5)) { return 481; }
  else if (0 == strncmp(name, "FN_F", (unsigned long int)5)) { return 482; }
  else if (0 == strncmp(name, "FN_S", (unsigned long int)5)) { return 483; }
  else if (0 == strncmp(name, "FN_B", (unsigned long int)5)) { return 484; }
  else if (0 == strncmp(name, "FN_RIGHT_SHIFT", (unsigned long int)15)) { return 485; }
  else if (0 == strncmp(name, "BRL_DOT1", (unsigned long int)9)) { return 497; }
  else if (0 == strncmp(name, "BRL_DOT2", (unsigned long int)9)) { return 498; }
  else if (0 == strncmp(name, "BRL_DOT3", (unsigned long int)9)) { return 499; }
  else if (0 == strncmp(name, "BRL_DOT4", (unsigned long int)9)) { return 500; }
  else if (0 == strncmp(name, "BRL_DOT5", (unsigned long int)9)) { return 501; }
  else if (0 == strncmp(name, "BRL_DOT6", (unsigned long int)9)) { return 502; }
  else if (0 == strncmp(name, "BRL_DOT7", (unsigned long int)9)) { return 503; }
  else if (0 == strncmp(name, "BRL_DOT8", (unsigned long int)9)) { return 504; }
  else if (0 == strncmp(name, "BRL_DOT9", (unsigned long int)9)) { return 505; }
  else if (0 == strncmp(name, "BRL_DOT10", (unsigned long int)10)) { return 506; }
  else if (0 == strncmp(name, "NUMERIC_0", (unsigned long int)10)) { return 512; }
  else if (0 == strncmp(name, "NUMERIC_1", (unsigned long int)10)) { return 513; }
  else if (0 == strncmp(name, "NUMERIC_2", (unsigned long int)10)) { return 514; }
  else if (0 == strncmp(name, "NUMERIC_3", (unsigned long int)10)) { return 515; }
  else if (0 == strncmp(name, "NUMERIC_4", (unsigned long int)10)) { return 516; }
  else if (0 == strncmp(name, "NUMERIC_5", (unsigned long int)10)) { return 517; }
  else if (0 == strncmp(name, "NUMERIC_6", (unsigned long int)10)) { return 518; }
  else if (0 == strncmp(name, "NUMERIC_7", (unsigned long int)10)) { return 519; }
  else if (0 == strncmp(name, "NUMERIC_8", (unsigned long int)10)) { return 520; }
  else if (0 == strncmp(name, "NUMERIC_9", (unsigned long int)10)) { return 521; }
  else if (0 == strncmp(name, "NUMERIC_STAR", (unsigned long int)13)) { return 522; }
  else if (0 == strncmp(name, "NUMERIC_POUND", (unsigned long int)14)) { return 523; }
  else if (0 == strncmp(name, "NUMERIC_A", (unsigned long int)10)) { return 524; }
  else if (0 == strncmp(name, "NUMERIC_B", (unsigned long int)10)) { return 525; }
  else if (0 == strncmp(name, "NUMERIC_C", (unsigned long int)10)) { return 526; }
  else if (0 == strncmp(name, "NUMERIC_D", (unsigned long int)10)) { return 527; }
  else if (0 == strncmp(name, "CAMERA_FOCUS", (unsigned long int)13)) { return 528; }
  else if (0 == strncmp(name, "WPS_BUTTON", (unsigned long int)11)) { return 529; }
  else if (0 == strncmp(name, "TOUCHPAD_TOGGLE", (unsigned long int)16)) { return 530; }
  else if (0 == strncmp(name, "TOUCHPAD_ON", (unsigned long int)12)) { return 531; }
  else if (0 == strncmp(name, "TOUCHPAD_OFF", (unsigned long int)13)) { return 532; }
  else if (0 == strncmp(name, "CAMERA_ZOOMIN", (unsigned long int)14)) { return 533; }
  else if (0 == strncmp(name, "CAMERA_ZOOMOUT", (unsigned long int)15)) { return 534; }
  else if (0 == strncmp(name, "CAMERA_UP", (unsigned long int)10)) { return 535; }
  else if (0 == strncmp(name, "CAMERA_DOWN", (unsigned long int)12)) { return 536; }
  else if (0 == strncmp(name, "CAMERA_LEFT", (unsigned long int)12)) { return 537; }
  else if (0 == strncmp(name, "CAMERA_RIGHT", (unsigned long int)13)) { return 538; }
  else if (0 == strncmp(name, "ATTENDANT_ON", (unsigned long int)13)) { return 539; }
  else if (0 == strncmp(name, "ATTENDANT_OFF", (unsigned long int)14)) { return 540; }
  else if (0 == strncmp(name, "ATTENDANT_TOGGLE", (unsigned long int)17)) { return 541; }
  else if (0 == strncmp(name, "LIGHTS_TOGGLE", (unsigned long int)14)) { return 542; }
  else if (0 == strncmp(name, "ALS_TOGGLE", (unsigned long int)11)) { return 560; }
  else if (0 == strncmp(name, "ROTATE_LOCK_TOGGLE", (unsigned long int)19)) { return 561; }
  else if (0 == strncmp(name, "BUTTONCONFIG", (unsigned long int)13)) { return 576; }
  else if (0 == strncmp(name, "TASKMANAGER", (unsigned long int)12)) { return 577; }
  else if (0 == strncmp(name, "JOURNAL", (unsigned long int)8)) { return 578; }
  else if (0 == strncmp(name, "CONTROLPANEL", (unsigned long int)13)) { return 579; }
  else if (0 == strncmp(name, "APPSELECT", (unsigned long int)10)) { return 580; }
  else if (0 == strncmp(name, "SCREENSAVER", (unsigned long int)12)) { return 581; }
  else if (0 == strncmp(name, "VOICECOMMAND", (unsigned long int)13)) { return 582; }
  else if (0 == strncmp(name, "ASSISTANT", (unsigned long int)10)) { return 583; }
  else if (0 == strncmp(name, "KBD_LAYOUT_NEXT", (unsigned long int)16)) { return 584; }
  else if (0 == strncmp(name, "EMOJI_PICKER", (unsigned long int)13)) { return 585; }
  else if (0 == strncmp(name, "BRIGHTNESS_MIN", (unsigned long int)15)) { return 592; }
  else if (0 == strncmp(name, "BRIGHTNESS_MAX", (unsigned long int)15)) { return 593; }
  else if (0 == strncmp(name, "KBDINPUTASSIST_PREV", (unsigned long int)20)) { return 608; }
  else if (0 == strncmp(name, "KBDINPUTASSIST_NEXT", (unsigned long int)20)) { return 609; }
  else if (0 == strncmp(name, "KBDINPUTASSIST_PREVGROUP", (unsigned long int)25)) { return 610; }
  else if (0 == strncmp(name, "KBDINPUTASSIST_NEXTGROUP", (unsigned long int)25)) { return 611; }
  else if (0 == strncmp(name, "KBDINPUTASSIST_ACCEPT", (unsigned long int)22)) { return 612; }
  else if (0 == strncmp(name, "KBDINPUTASSIST_CANCEL", (unsigned long int)22)) { return 613; }
  else if (0 == strncmp(name, "RIGHT_UP", (unsigned long int)9)) { return 614; }
  else if (0 == strncmp(name, "RIGHT_DOWN", (unsigned long int)11)) { return 615; }
  else if (0 == strncmp(name, "LEFT_UP", (unsigned long int)8)) { return 616; }
  else if (0 == strncmp(name, "LEFT_DOWN", (unsigned long int)10)) { return 617; }
  else if (0 == strncmp(name, "ROOT_MENU", (unsigned long int)10)) { return 618; }
  else if (0 == strncmp(name, "MEDIA_TOP_MENU", (unsigned long int)15)) { return 619; }
  else if (0 == strncmp(name, "NUMERIC_11", (unsigned long int)11)) { return 620; }
  else if (0 == strncmp(name, "NUMERIC_12", (unsigned long int)11)) { return 621; }
  else if (0 == strncmp(name, "AUDIO_DESC", (unsigned long int)11)) { return 622; }
  else if (0 == strncmp(name, "3D_MODE", (unsigned long int)8)) { return 623; }
  else if (0 == strncmp(name, "NEXT_FAVORITE", (unsigned long int)14)) { return 624; }
  else if (0 == strncmp(name, "STOP_RECORD", (unsigned long int)12)) { return 625; }
  else if (0 == strncmp(name, "PAUSE_RECORD", (unsigned long int)13)) { return 626; }
  else if (0 == strncmp(name, "VOD", (unsigned long int)4)) { return 627; }
  else if (0 == strncmp(name, "UNMUTE", (unsigned long int)7)) { return 628; }
  else if (0 == strncmp(name, "FASTREVERSE", (unsigned long int)12)) { return 629; }
  else if (0 == strncmp(name, "SLOWREVERSE", (unsigned long int)12)) { return 630; }
  else if (0 == strncmp(name, "DATA", (unsigned long int)5)) { return 631; }
  else if (0 == strncmp(name, "ONSCREEN_KEYBOARD", (unsigned long int)18)) { return 632; }
  else if (0 == strncmp(name, "PRIVACY_SCREEN_TOGGLE", (unsigned long int)22)) { return 633; }
  else if (0 == strncmp(name, "SELECTIVE_SCREENSHOT", (unsigned long int)21)) { return 634; }
  else if (0 == strncmp(name, "MACRO1", (unsigned long int)7)) { return 656; }
  else if (0 == strncmp(name, "MACRO2", (unsigned long int)7)) { return 657; }
  else if (0 == strncmp(name, "MACRO3", (unsigned long int)7)) { return 658; }
  else if (0 == strncmp(name, "MACRO4", (unsigned long int)7)) { return 659; }
  else if (0 == strncmp(name, "MACRO5", (unsigned long int)7)) { return 660; }
  else if (0 == strncmp(name, "MACRO6", (unsigned long int)7)) { return 661; }
  else if (0 == strncmp(name, "MACRO7", (unsigned long int)7)) { return 662; }
  else if (0 == strncmp(name, "MACRO8", (unsigned long int)7)) { return 663; }
  else if (0 == strncmp(name, "MACRO9", (unsigned long int)7)) { return 664; }
  else if (0 == strncmp(name, "MACRO10", (unsigned long int)8)) { return 665; }
  else if (0 == strncmp(name, "MACRO11", (unsigned long int)8)) { return 666; }
  else if (0 == strncmp(name, "MACRO12", (unsigned long int)8)) { return 667; }
  else if (0 == strncmp(name, "MACRO13", (unsigned long int)8)) { return 668; }
  else if (0 == strncmp(name, "MACRO14", (unsigned long int)8)) { return 669; }
  else if (0 == strncmp(name, "MACRO15", (unsigned long int)8)) { return 670; }
  else if (0 == strncmp(name, "MACRO16", (unsigned long int)8)) { return 671; }
  else if (0 == strncmp(name, "MACRO17", (unsigned long int)8)) { return 672; }
  else if (0 == strncmp(name, "MACRO18", (unsigned long int)8)) { return 673; }
  else if (0 == strncmp(name, "MACRO19", (unsigned long int)8)) { return 674; }
  else if (0 == strncmp(name, "MACRO20", (unsigned long int)8)) { return 675; }
  else if (0 == strncmp(name, "MACRO21", (unsigned long int)8)) { return 676; }
  else if (0 == strncmp(name, "MACRO22", (unsigned long int)8)) { return 677; }
  else if (0 == strncmp(name, "MACRO23", (unsigned long int)8)) { return 678; }
  else if (0 == strncmp(name, "MACRO24", (unsigned long int)8)) { return 679; }
  else if (0 == strncmp(name, "MACRO25", (unsigned long int)8)) { return 680; }
  else if (0 == strncmp(name, "MACRO26", (unsigned long int)8)) { return 681; }
  else if (0 == strncmp(name, "MACRO27", (unsigned long int)8)) { return 682; }
  else if (0 == strncmp(name, "MACRO28", (unsigned long int)8)) { return 683; }
  else if (0 == strncmp(name, "MACRO29", (unsigned long int)8)) { return 684; }
  else if (0 == strncmp(name, "MACRO30", (unsigned long int)8)) { return 685; }
  else if (0 == strncmp(name, "MACRO_RECORD_START", (unsigned long int)19)) { return 688; }
  else if (0 == strncmp(name, "MACRO_RECORD_STOP", (unsigned long int)18)) { return 689; }
  else if (0 == strncmp(name, "MACRO_PRESET_CYCLE", (unsigned long int)19)) { return 690; }
  else if (0 == strncmp(name, "MACRO_PRESET1", (unsigned long int)14)) { return 691; }
  else if (0 == strncmp(name, "MACRO_PRESET2", (unsigned long int)14)) { return 692; }
  else if (0 == strncmp(name, "MACRO_PRESET3", (unsigned long int)14)) { return 693; }
  else if (0 == strncmp(name, "KBD_LCD_MENU1", (unsigned long int)14)) { return 696; }
  else if (0 == strncmp(name, "KBD_LCD_MENU2", (unsigned long int)14)) { return 697; }
  else if (0 == strncmp(name, "KBD_LCD_MENU3", (unsigned long int)14)) { return 698; }
  else if (0 == strncmp(name, "KBD_LCD_MENU4", (unsigned long int)14)) { return 699; }
  else if (0 == strncmp(name, "KBD_LCD_MENU5", (unsigned long int)14)) { return 700; }
  else if (0 == strncmp(name, "MIN_INTERESTING", (unsigned long int)16)) { return 0; }
  else if (0 == strncmp(name, "MAX", (unsigned long int)4)) { return 767; }
  return -1;
}
