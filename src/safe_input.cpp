#include "Safe_input.h"

int input_int(const std::string& prompt, int min, int max)
{
    std::string line;
    int num;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, line);
        try {
            num = std::stoi(line);
        } catch (...) {
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        if (num >= min && num <= max)
            return num;

        std::cout << "Number must be between " << min << " and " << max << ".\n";
    }
}
char input_yes_no(const std::string& prompt)
{
    std::string line;
    char ans;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, line);

        if (line.length() == 1)
        {
            ans = line[0];
            if (ans == 'y' || ans == 'n')
                return ans;
        }
        std::cout << "Please enter 'y' or 'n'.\n";
    }
}