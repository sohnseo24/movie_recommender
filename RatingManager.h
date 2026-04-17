#pragma once
#include <vector>
#include "Rating.h"

class RatingManager {
private:
    std::vector<Rating> ratings; 

public:
    void addRating(const Rating& r);
    void printRatingsByMovie(int movieId) const; 
};