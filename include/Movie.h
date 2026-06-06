#pragma once
#include <string>
#include <iostream>

class Movie {
private:
    int         id;
    std::string title;
    std::string genre;
    int         releaseYear;
    double      totalRating;
    int         ratingCount;

public:
    //평점 시스템의 경계값을 static constexpr 상수로 추출
    static constexpr double MIN_SCORE = 0.0;
    static constexpr double MAX_SCORE = 5.0;

    Movie();
    Movie(int id, const std::string& title,
          const std::string& genre, int releaseYear);
    Movie(int id, const std::string& title, int releaseYear, double rating);//CSV로딩용 생성자 추가(개봉연도와 평점을 받는 생성자 추가)

    // getter함수들
    int         getId()              const;
    std::string getTitle()           const;
    std::string getGenre()           const;
    int         getReleaseYear()     const;
    double      getAverageRating()   const;
    int         getRatingCount()     const;

    // 연산자 오버로딩 선언 (구현은 cpp로 이동)
    bool operator<(const Movie& other) const;
    bool operator==(const std::string& searchTitle) const;
    
    // friend 함수는 클래스 내부에서 선언만 함
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);

    // setter 및 기능 함수들
    void setReleaseYear(int releaseYear);
    void addRating(double r);
    void display() const;
};