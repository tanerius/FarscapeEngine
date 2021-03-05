#pragma once

// Based off of glfw3.h
/* The unknown key */
#define FS_KEY_UNKNOWN            -1

/* Printable keys */
#define FS_KEY_SPACE              32
#define FS_KEY_APOSTROPHE         39  /* ' */
#define FS_KEY_COMMA              44  /* , */
#define FS_KEY_MINUS              45  /* - */
#define FS_KEY_PERIOD             46  /* . */
#define FS_KEY_SLASH              47  /* / */
#define FS_KEY_0                  48
#define FS_KEY_1                  49
#define FS_KEY_2                  50
#define FS_KEY_3                  51
#define FS_KEY_4                  52
#define FS_KEY_5                  53
#define FS_KEY_6                  54
#define FS_KEY_7                  55
#define FS_KEY_8                  56
#define FS_KEY_9                  57
#define FS_KEY_SEMICOLON          59  /* ; */
#define FS_KEY_EQUAL              61  /* = */
#define FS_KEY_A                  65
#define FS_KEY_B                  66
#define FS_KEY_C                  67
#define FS_KEY_D                  68
#define FS_KEY_E                  69
#define FS_KEY_F                  70
#define FS_KEY_G                  71
#define FS_KEY_H                  72
#define FS_KEY_I                  73
#define FS_KEY_J                  74
#define FS_KEY_K                  75
#define FS_KEY_L                  76
#define FS_KEY_M                  77
#define FS_KEY_N                  78
#define FS_KEY_O                  79
#define FS_KEY_P                  80
#define FS_KEY_Q                  81
#define FS_KEY_R                  82
#define FS_KEY_S                  83
#define FS_KEY_T                  84
#define FS_KEY_U                  85
#define FS_KEY_V                  86
#define FS_KEY_W                  87
#define FS_KEY_X                  88
#define FS_KEY_Y                  89
#define FS_KEY_Z                  90
#define FS_KEY_LEFT_BRACKET       91  /* [ */
#define FS_KEY_BACKSLASH          92  /* \ */
#define FS_KEY_RIGHT_BRACKET      93  /* ] */
#define FS_KEY_GRAVE_ACCENT       96  /* ` */
#define FS_KEY_WORLD_1            161 /* non-US #1 */
#define FS_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define FS_KEY_ESCAPE             256
#define FS_KEY_ENTER              257
#define FS_KEY_TAB                258
#define FS_KEY_BACKSPACE          259
#define FS_KEY_INSERT             260
#define FS_KEY_DELETE             261
#define FS_KEY_RIGHT              262
#define FS_KEY_LEFT               263
#define FS_KEY_DOWN               264
#define FS_KEY_UP                 265
#define FS_KEY_PAGE_UP            266
#define FS_KEY_PAGE_DOWN          267
#define FS_KEY_HOME               268
#define FS_KEY_END                269
#define FS_KEY_CAPS_LOCK          280
#define FS_KEY_SCROLL_LOCK        281
#define FS_KEY_NUM_LOCK           282
#define FS_KEY_PRINT_SCREEN       283
#define FS_KEY_PAUSE              284
#define FS_KEY_F1                 290
#define FS_KEY_F2                 291
#define FS_KEY_F3                 292
#define FS_KEY_F4                 293
#define FS_KEY_F5                 294
#define FS_KEY_F6                 295
#define FS_KEY_F7                 296
#define FS_KEY_F8                 297
#define FS_KEY_F9                 298
#define FS_KEY_F10                299
#define FS_KEY_F11                300
#define FS_KEY_F12                301
#define FS_KEY_F13                302
#define FS_KEY_F14                303
#define FS_KEY_F15                304
#define FS_KEY_F16                305
#define FS_KEY_F17                306
#define FS_KEY_F18                307
#define FS_KEY_F19                308
#define FS_KEY_F20                309
#define FS_KEY_F21                310
#define FS_KEY_F22                311
#define FS_KEY_F23                312
#define FS_KEY_F24                313
#define FS_KEY_F25                314
#define FS_KEY_KP_0               320
#define FS_KEY_KP_1               321
#define FS_KEY_KP_2               322
#define FS_KEY_KP_3               323
#define FS_KEY_KP_4               324
#define FS_KEY_KP_5               325
#define FS_KEY_KP_6               326
#define FS_KEY_KP_7               327
#define FS_KEY_KP_8               328
#define FS_KEY_KP_9               329
#define FS_KEY_KP_DECIMAL         330
#define FS_KEY_KP_DIVIDE          331
#define FS_KEY_KP_MULTIPLY        332
#define FS_KEY_KP_SUBTRACT        333
#define FS_KEY_KP_ADD             334
#define FS_KEY_KP_ENTER           335
#define FS_KEY_KP_EQUAL           336
#define FS_KEY_LEFT_SHIFT         340
#define FS_KEY_LEFT_CONTROL       341
#define FS_KEY_LEFT_ALT           342
#define FS_KEY_LEFT_SUPER         343
#define FS_KEY_RIGHT_SHIFT        344
#define FS_KEY_RIGHT_CONTROL      345
#define FS_KEY_RIGHT_ALT          346
#define FS_KEY_RIGHT_SUPER        347
#define FS_KEY_MENU               348

#define FS_KEY_LAST               FS_KEY_MENU