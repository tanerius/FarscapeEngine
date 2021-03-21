#pragma once

#include <sstream>
namespace Farscape
{
    typedef enum class KeyCode : unsigned short
    {
        // From glfw3.h
        Space = 32,
        Apostrophe = 39, /* ' */
        Comma = 44, /* , */
        Minus = 45, /* - */
        Period = 46, /* . */
        Slash = 47, /* / */

        D0 = 48, /* 0 */
        D1 = 49, /* 1 */
        D2 = 50, /* 2 */
        D3 = 51, /* 3 */
        D4 = 52, /* 4 */
        D5 = 53, /* 5 */
        D6 = 54, /* 6 */
        D7 = 55, /* 7 */
        D8 = 56, /* 8 */
        D9 = 57, /* 9 */

        Semicolon = 59, /* ; */
        Equal = 61, /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket = 91,  /* [ */
        Backslash = 92,  /* \ */
        RightBracket = 93,  /* ] */
        GraveAccent = 96,  /* ` */

        World1 = 161, /* non-US #1 */
        World2 = 162, /* non-US #2 */

        /* Function keys */
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        /* Keypad */
        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348
    } Key;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
    {
        os << static_cast<int32_t>(keyCode);
        return os;
    }
}

// Based off of glfw3.h
/* The unknown key */
#define FS_KEY_UNKNOWN            -1

/* Printable keys */
#define FS_KEY_SPACE              ::Farscape::Key::Space
#define FS_KEY_APOSTROPHE         ::Farscape::Key::Apostrophe  /* ' */
#define FS_KEY_COMMA              ::Farscape::Key::Comma  /* , */
#define FS_KEY_MINUS              ::Farscape::Key::Minus  /* - */
#define FS_KEY_PERIOD             ::Farscape::Key::Period  /* . */
#define FS_KEY_SLASH              ::Farscape::Key::Slash  /* / */
#define FS_KEY_0                  ::Farscape::Key::D0
#define FS_KEY_1                  ::Farscape::Key::D1
#define FS_KEY_2                  ::Farscape::Key::D2
#define FS_KEY_3                  ::Farscape::Key::D3
#define FS_KEY_4                  ::Farscape::Key::D4
#define FS_KEY_5                  ::Farscape::Key::D5
#define FS_KEY_6                  ::Farscape::Key::D6
#define FS_KEY_7                  ::Farscape::Key::D7
#define FS_KEY_8                  ::Farscape::Key::D8
#define FS_KEY_9                  ::Farscape::Key::D9
#define FS_KEY_SEMICOLON          ::Farscape::Key::Semicolon  /* ; */
#define FS_KEY_EQUAL              ::Farscape::Key::Equal  /* = */
#define FS_KEY_A                  ::Farscape::Key::A
#define FS_KEY_B                  ::Farscape::Key::B
#define FS_KEY_C                  ::Farscape::Key::C
#define FS_KEY_D                  ::Farscape::Key::D
#define FS_KEY_E                  ::Farscape::Key::E
#define FS_KEY_F                  ::Farscape::Key::F
#define FS_KEY_G                  ::Farscape::Key::G
#define FS_KEY_H                  ::Farscape::Key::H
#define FS_KEY_I                  ::Farscape::Key::I
#define FS_KEY_J                  ::Farscape::Key::J
#define FS_KEY_K                  ::Farscape::Key::K
#define FS_KEY_L                  ::Farscape::Key::L
#define FS_KEY_M                  ::Farscape::Key::M
#define FS_KEY_N                  ::Farscape::Key::N
#define FS_KEY_O                  ::Farscape::Key::O
#define FS_KEY_P                  ::Farscape::Key::P
#define FS_KEY_Q                  ::Farscape::Key::Q
#define FS_KEY_R                  ::Farscape::Key::R
#define FS_KEY_S                  ::Farscape::Key::S
#define FS_KEY_T                  ::Farscape::Key::T
#define FS_KEY_U                  ::Farscape::Key::U
#define FS_KEY_V                  ::Farscape::Key::V
#define FS_KEY_W                  ::Farscape::Key::W
#define FS_KEY_X                  ::Farscape::Key::X
#define FS_KEY_Y                  ::Farscape::Key::Y
#define FS_KEY_Z                  ::Farscape::Key::Z
#define FS_KEY_LEFT_BRACKET       ::Farscape::Key::LeftBracket  /* [ */
#define FS_KEY_BACKSLASH          ::Farscape::Key::Backslash  /* \ */
#define FS_KEY_RIGHT_BRACKET      ::Farscape::Key::RightBracket  /* ] */
#define FS_KEY_GRAVE_ACCENT       ::Farscape::Key::GraveAccent  /* ` */
#define FS_KEY_WORLD_1            ::Farscape::Key::World1 /* non-US #1 */
#define FS_KEY_WORLD_2            ::Farscape::Key::World2 /* non-US #2 */

/* Function keys */
#define FS_KEY_ESCAPE             ::Farscape::Key::Escape
#define FS_KEY_ENTER              ::Farscape::Key::Enter
#define FS_KEY_TAB                ::Farscape::Key::Tab
#define FS_KEY_BACKSPACE          ::Farscape::Key::Backspace
#define FS_KEY_INSERT             ::Farscape::Key::Insert
#define FS_KEY_DELETE             ::Farscape::Key::Delete
#define FS_KEY_RIGHT              ::Farscape::Key::Right
#define FS_KEY_LEFT               ::Farscape::Key::Left
#define FS_KEY_DOWN               ::Farscape::Key::Down 
#define FS_KEY_UP                 ::Farscape::Key::Up
#define FS_KEY_PAGE_UP            ::Farscape::Key::PageUp
#define FS_KEY_PAGE_DOWN          ::Farscape::Key::PageDown
#define FS_KEY_HOME               ::Farscape::Key::Home
#define FS_KEY_END                ::Farscape::Key::End
#define FS_KEY_CAPS_LOCK          ::Farscape::Key::CapsLock
#define FS_KEY_SCROLL_LOCK        ::Farscape::Key::ScrollLock
#define FS_KEY_NUM_LOCK           ::Farscape::Key::NumLock
#define FS_KEY_PRINT_SCREEN       ::Farscape::Key::PrintScreen
#define FS_KEY_PAUSE              ::Farscape::Key::Pause
#define FS_KEY_F1                 ::Farscape::Key::F1
#define FS_KEY_F2                 ::Farscape::Key::F2
#define FS_KEY_F3                 ::Farscape::Key::F3
#define FS_KEY_F4                 ::Farscape::Key::F4
#define FS_KEY_F5                 ::Farscape::Key::F5
#define FS_KEY_F6                 ::Farscape::Key::F6
#define FS_KEY_F7                 ::Farscape::Key::F7
#define FS_KEY_F8                 ::Farscape::Key::F8
#define FS_KEY_F9                 ::Farscape::Key::F9
#define FS_KEY_F10                ::Farscape::Key::F10
#define FS_KEY_F11                ::Farscape::Key::F11
#define FS_KEY_F12                ::Farscape::Key::F12
#define FS_KEY_F13                ::Farscape::Key::F13
#define FS_KEY_F14                ::Farscape::Key::F14
#define FS_KEY_F15                ::Farscape::Key::F15
#define FS_KEY_F16                ::Farscape::Key::F16
#define FS_KEY_F17                ::Farscape::Key::F17
#define FS_KEY_F18                ::Farscape::Key::F18
#define FS_KEY_F19                ::Farscape::Key::F19
#define FS_KEY_F20                ::Farscape::Key::F20
#define FS_KEY_F21                ::Farscape::Key::F21
#define FS_KEY_F22                ::Farscape::Key::F22
#define FS_KEY_F23                ::Farscape::Key::F23
#define FS_KEY_F24                ::Farscape::Key::F24
#define FS_KEY_F25                ::Farscape::Key::F25


#define FS_KEY_KP_0               ::Farscape::Key::KP0
#define FS_KEY_KP_1               ::Farscape::Key::KP1
#define FS_KEY_KP_2               ::Farscape::Key::KP2
#define FS_KEY_KP_3               ::Farscape::Key::KP3
#define FS_KEY_KP_4               ::Farscape::Key::KP4
#define FS_KEY_KP_5               ::Farscape::Key::KP5
#define FS_KEY_KP_6               ::Farscape::Key::KP6
#define FS_KEY_KP_7               ::Farscape::Key::KP7
#define FS_KEY_KP_8               ::Farscape::Key::KP8
#define FS_KEY_KP_9               ::Farscape::Key::KP9
#define FS_KEY_KP_DECIMAL         ::Farscape::Key::KPDecimal
#define FS_KEY_KP_DIVIDE          ::Farscape::Key::KPDivide
#define FS_KEY_KP_MULTIPLY        ::Farscape::Key::KPMultiply
#define FS_KEY_KP_SUBTRACT        ::Farscape::Key::KPSubtract
#define FS_KEY_KP_ADD             ::Farscape::Key::KPAdd
#define FS_KEY_KP_ENTER           ::Farscape::Key::KPEnter
#define FS_KEY_KP_EQUAL           ::Farscape::Key::KPEqual


#define FS_KEY_LEFT_SHIFT         ::Farscape::Key::LeftShift
#define FS_KEY_LEFT_CONTROL       ::Farscape::Key::LeftControl
#define FS_KEY_LEFT_ALT           ::Farscape::Key::LeftAlt
#define FS_KEY_LEFT_SUPER         ::Farscape::Key::LeftSuper
#define FS_KEY_RIGHT_SHIFT        ::Farscape::Key::RightShift
#define FS_KEY_RIGHT_CONTROL      ::Farscape::Key::RightControl
#define FS_KEY_RIGHT_ALT          ::Farscape::Key::RightAlt
#define FS_KEY_RIGHT_SUPER        ::Farscape::Key::RightSuper
#define FS_KEY_MENU               ::Farscape::Key::Menu

#define FS_KEY_LAST               ::Farscape::Key::Menu