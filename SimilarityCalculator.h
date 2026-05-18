#pragma once
#include <iostream>
#include <Rating.h>
#include <vector>

class SimularityCarculator{
    int calculate(const std::vector<Rating>& user1, const std::vector<Rating>& user2);
};