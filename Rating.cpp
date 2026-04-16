#include "Rating.h"
#include <iostream>

Rating::Rating()
    : userId(0), movieId(0), score(0.0) {}

Rating::Rating(int userId, int movieId, double s)
    : userId(userId), movieId(movieId) {
    if (s < 0.0 || s > 5.0) {
        std::cout << "Warning: Invalid score. Setting to 0.0" << std::endl;
        score = 0.0;
    } else {
        score = s;
    }
}

int    Rating::getUserId()  const { return userId; }
int    Rating::getMovieId() const { return movieId; }
double Rating::getScore()   const { return score; }

// 출력 연산자 구현
std::ostream& operator<<(std::ostream& os, const Rating& r) {
    os << "User ID: " << r.userId << " | Movie ID: " << r.movieId << " | Score: " << r.score;
    return os;
}

void Rating::display() const {
    std::cout << *this << std::endl; 
}