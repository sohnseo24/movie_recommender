#pragma once
#include <vector>
#include "Movie.h"

class MovieManager {
private:
    std::vector<Movie> movies; // 영화 데이터를 담는 벡터

public:
    void addMovie(const Movie& m); //1번: 영화 추가
    void printAllMovies() const;//3번: 전체 목록 출력
    void sortByRating(); // 4번: 평점순 정렬 출력
    Movie* findByTitle(const std::string& title); //2번: 제목으로 검색
};

