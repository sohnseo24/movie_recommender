#include "Movie.h"
#include <iostream>

// 기본 생성자
Movie::Movie()
    : id(0), title(""), genre(""), releaseYear(0), totalRating(0.0), ratingCount(0) {}

// 4인자 생성자
Movie::Movie(int id, const std::string& title, const std::string& genre, int year)
    : id(id), title(title), genre(genre), releaseYear(year), totalRating(0.0), ratingCount(0) {}
// CSV로딩용 생성자 추가(개봉연도와 평점을 받는 생성자 추가)
// 완벽한 방어: CSV 로딩용 생성자 수정
Movie::Movie(int id, const std::string& title, int releaseYear, double rating) 
    : id(id), title(title), genre(""), releaseYear(releaseYear), totalRating(rating), ratingCount(1) {}
// Getter 구현
int         Movie::getId()           const { return id; }
std::string Movie::getTitle()        const { return title; }
std::string Movie::getGenre()        const { return genre; }
int         Movie::getReleaseYear()  const { return releaseYear; }
int         Movie::getRatingCount()  const { return ratingCount; }

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;
    return totalRating / ratingCount;
}

// 연산자 오버로딩 구현
bool Movie::operator<(const Movie& other) const {
    return this->id < other.id;
}

bool Movie::operator==(const std::string& searchTitle) const {
    return this->title == searchTitle;
}

// 출력 연산자 구현
std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << "[" << m.id << "] " << m.title 
       << " (" << m.releaseYear << ") | 장르: " << m.genre 
       << " | 평점: " << m.getAverageRating(); 
    return os;
}

// Setter 및 기능 함수
void Movie::setReleaseYear(int year) { 
    this->releaseYear = year; 
}

void Movie::addRating(double r) {
    if (r >= Movie::MIN_SCORE && r <= Movie::MAX_SCORE) {
        totalRating += r;
        ratingCount++;
    }
}

void Movie::display() const {
    std::cout << *this << " (" << ratingCount << "건)" << std::endl;
}