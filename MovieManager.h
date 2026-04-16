#pragma once
#include <vector>
#include "Movie.h"

class MovieManager {
private:
    std::vector<Movie> movies; // 영화 데이터를 담는 벡터

public:
    void addMovie(const Movie& m);
    void printAllMovies() const;
};