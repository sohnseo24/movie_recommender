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
    void loadMovies(const std::string& filename);//프로그램 시작시 CSV파일에서 데이터를 로드한다.
    void saveMovies(const std::string& filename) const;//프로그램 종료시 데이터를 CSV파일에 저장한다.
    //이 함수는 저장만 하고 MovieManager내부 값을 바꾸지 않으므로 const를 씀
};

