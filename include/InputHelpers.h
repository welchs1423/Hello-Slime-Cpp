#ifndef INPUT_HELPERS_H
#define INPUT_HELPERS_H

#include <iostream>
#include <limits>

inline int readIntInRange(int minVal, int maxVal)
{
    int choice = 0;
    while (true)
    {
        if (std::cin >> choice)
        {
            if (choice >= minVal && choice <= maxVal)
                return choice;
            std::cout << minVal << "에서 " << maxVal << " 사이의 숫자를 입력하세요.\n";
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "숫자를 입력해 주세요.\n";
        }
    }
}

#endif
