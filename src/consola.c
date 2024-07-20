//#include <windows.h>
#include "../include/consola.h"

void moverCursor(int x, int y){
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsola, pos);
}
void ocultarCursor() {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsola, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Ocultar el cursor
    SetConsoleCursorInfo(hConsola, &cursorInfo);
}

void cambiarColorFuente(WORD color) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsola, color);
}

void deshabilitarModoEdicionRapida() {
    HANDLE hConsola = GetStdHandle(STD_INPUT_HANDLE);
    DWORD modo;
    GetConsoleMode(hConsola, &modo);
    SetConsoleMode(hConsola, modo & ~ENABLE_QUICK_EDIT_MODE);
}

void establecerTamanioConsola(int ancho, int alto){
    HWND wConsola = GetConsoleWindow();
    RECT r;
    
    GetWindowRect(wConsola, &r); // Obtiene el tamaño actual de la consola
    MoveWindow(wConsola, r.left, r.top, ancho, alto, TRUE);
}
void dehabilitarRedimension(){
    HWND wConsola = GetConsoleWindow();
    LONG style = GetWindowLong(wConsola, GWL_STYLE);
    style &= ~WS_SIZEBOX;
    SetWindowLong(wConsola, GWL_STYLE, style);
}

void eliminarScroll() {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (GetConsoleScreenBufferInfo(hConsola, &info)) {
        COORD newSize;
        // El tamaño del búfer debe ser al menos tan grande como las dimensiones de la ventana.
        newSize.X = info.srWindow.Right - info.srWindow.Left + 1;
        newSize.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
        SetConsoleScreenBufferSize(hConsola, newSize);
    }
}

void cambiarIcono(){
    HWND wConsola = GetConsoleWindow();
    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
    SendMessage(wConsola, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    SendMessage(wConsola, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
}