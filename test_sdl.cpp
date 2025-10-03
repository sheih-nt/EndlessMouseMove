#include <X11/Xlib.h>
#include <unistd.h>    // для usleep
#include <iostream>

bool checkMouseClick(Display* d, Window win) {
    while (XPending(d)) {
        XEvent e;
        XNextEvent(d, &e);
        if (e.type == ButtonPress) {
            if (e.xbutton.button == Button1 || e.xbutton.button == Button3) {
                return true; // нажата ЛКМ или ПКМ
            }
        }
    }
    return false;
}

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
    int dx = 6;
    int dy = 6;

    Window root = DefaultRootWindow(d);

    // создаём невидимое окно только для ввода
    Window win = XCreateWindow(d, root,
                               0, 0, 1, 1, 0,
                               CopyFromParent, InputOnly,
                               CopyFromParent, 0, nullptr);

    // подписываемся на события кнопок мыши
    XSelectInput(d, win, ButtonPressMask);
    XMapWindow(d, win);

    while (true) {
        // двигаем курсор
        XWarpPointer(d, None, root, 0, 0, 0, 0, x, y);
        XFlush(d);

        if (checkMouseClick(d, win)) {
            break;
        }

        // меняем координаты
        x += dx;
        y += dy;

        if (x <= 0 || x >= width) dx = -dx;
        if (y <= 0 || y >= height) dy = -dy;

        usleep(12500);
    }

    XDestroyWindow(d, win);
    XCloseDisplay(d);
    return 0;
}
