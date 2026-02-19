#ifndef SAFE_INPUT
#define SAFE_INPUT
#include <iostream>

int input_int(const std::string& prompt, int min, int max);

char input_yes_no(const std::string& prompt);

#endif