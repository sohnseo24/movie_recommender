#pragma once
#include <iostream>

class Rating {
private:
    int    userId;
    int    movieId;
    double score;

public:
    Rating();
    Rating(int userId, int movieId, double score);

    int    getUserId()  const;
    int    getMovieId() const;
    double getScore()   const;

    // 다른 객체들과 스타일 맞추기: 출력 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const Rating& r);

    void display() const;
};

