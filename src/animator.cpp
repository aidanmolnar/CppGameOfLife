#include "animator.hpp"
#include <iostream>
#include <windows.h>

void Animator::play(int frame_time)
{
    SetConsoleOutputCP(CP_UTF8);

    while (true)
    {
        // Clear the console
        std::cout << "\x1b[2H"
                  << "\x1b[2J" << std::flush;

        draw();
        Sleep(frame_time);
    }
}