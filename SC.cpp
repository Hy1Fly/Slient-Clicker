#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>

// 模拟人类点击的随机间隔范围（毫秒）
const int MIN_INTERVAL = 17; // 四舍五入为整数
const int MAX_INTERVAL = 50;
const int MAX_CPS_LEFT = 21;

// 函数用于设置控制台颜色
void setConsoleColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// 函数用于模拟鼠标点击（左键）
void leftClick() {
    HWND hwnd = GetForegroundWindow();
    // 模拟鼠标左键按下
    SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(0, 0));

    // 根据最大 CPS 计算点击间隔
    int clickInterval = static_cast<int>(1000.0 / MAX_CPS_LEFT);
    Sleep(clickInterval);

    // 模拟鼠标左键抬起
    SendMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
}
void rightClick() {
    HWND hwnd = GetForegroundWindow();
    // 模拟鼠标右键按下
    SendMessage(hwnd, WM_RBUTTONDOWN, MK_RBUTTON, MAKELONG(0, 0));

    // 随机生成点击间隔
    int clickInterval = MIN_INTERVAL + rand() % (MAX_INTERVAL - MIN_INTERVAL);
    Sleep(clickInterval);

    // 模拟鼠标右键释放
    SendMessage(hwnd, WM_RBUTTONUP, MK_RBUTTON, MAKELONG(0, 0));
}

int main() {
    // 设置控制台颜色
    setConsoleColor(15, 0); // 白色文字，黑色背景

    std::cout << "=============================\n";
    std::cout << "  Welcome to Slient Clicker  \n";
    std::cout << "=============================\n";
    
    std::cout << "Enter the new program name: ";
    std::string newProgramName;
    std::getline(std::cin, newProgramName);
    system(("title " + newProgramName).c_str());

    std::cout << "Press any key to start...\n";
    _getch();

    // 初始化随机数种子
    srand(static_cast<unsigned int>(time(nullptr)));

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    bool leftClickEnabled = true; // 开关左键点击
    bool rightClickEnabled = true; // 开关右键点击

    std::cout << "\nControls:\n";
    std::cout << "  'L' - Toggle Left Click\n";
    std::cout << "  'R' - Toggle Right Click\n";
    std::cout << "  'Esc' - Exit\n";
    std::cout << "=============================\n";

    while (true) {
        // 判断按键以切换左键和右键的点击状态
        if (GetAsyncKeyState('L') & 0x8000) {
            leftClickEnabled = !leftClickEnabled;
            std::cout << "Left Click " << (leftClickEnabled ? "Enabled" : "Disabled") << "\n";
            Sleep(500); // 防止快速切换
        }

        if (GetAsyncKeyState('R') & 0x8000) {
            rightClickEnabled = !rightClickEnabled;
            std::cout << "Right Click " << (rightClickEnabled ? "Enabled" : "Disabled") << "\n";
            Sleep(500); // 防止快速切换
        }

        // 判断 Esc 键是否按下，如果按下则退出
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }

        // 判断右键是否按下，如果按下则持续进行右键点击
        if (rightClickEnabled && GetAsyncKeyState(VK_RBUTTON)) {
            rightClick();
        }

        // 判断 M5 键是否按下，如果按下则持续进行左键点击
        if (leftClickEnabled && GetAsyncKeyState(VK_XBUTTON2)) {
            leftClick();
        }

        // 添加短暂的睡眠以避免过于频繁的CPU占用
        Sleep(10);
    }

    return 0;
}
