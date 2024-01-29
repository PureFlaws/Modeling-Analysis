#pragma once
#include <iostream>
#include <vector>
#include <functional>

void DisplayMenu(const std::vector<std::string>& menuItems, const std::vector<std::function<void()>>& actions);
