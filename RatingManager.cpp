#include "RatingManager.h"
#include <iostream>

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(r);
}


void RatingManager::printRatingsByMovie(int movieId) const {
    int count = 0; // 찾은 평점의 개수를 저장
    for (int i = 0; i < ratings.size(); i++) {
        if (ratings[i].getMovieId() == movieId) {
            std::cout << ratings[i] << std::endl; 
            count++;
        }
    }
    if (count == 0) std::cout << "해당 영화에 대한 평점이 없습니다." << std::endl;
