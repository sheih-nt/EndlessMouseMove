#include <X11/Xlib.h>
#include <unistd.h>    // для usleep
#include <iostream>

int main() {
    Display* d = XOpenDisplay(nullptr);
    if (!d) {
        std::cerr << "Cannot open display\n";
        return 1;
    }

    int screen = DefaultScreen(d);
    int width = DisplayWidth(d, screen);
    int height = DisplayHeight(d, screen);

    int x = width / 2;
    int y = height / 2;
    int dx = 6; // скорость по x
    int dy = 6; // скорость по y

    while (true) {
        // Перемещаем курсор
        XWarpPointer(d, None, DefaultRootWindow(d), 0,0,0,0, x, y);
        XFlush(d);

        // Меняем координаты
        x += dx;
        y += dy;

        // Проверяем границы экрана
        if (x <= 0 || x >= width) dx = -dx;
        if (y <= 0 || y >= height) dy = -dy;

        usleep(12500); // 50 мс
    }

    XCloseDisplay(d);
    return 0;
}
