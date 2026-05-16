#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager: public BaseManager{
private:
    std::vector<Movie> movies; // 영화 데이터를 담는 벡터

public:
    void addMovie(const Movie& m); //1번: 영화 추가
    void printAllMovies() const;//3번: 전체 목록 출력
    void sortByRating(); // 4번: 평점순 정렬 출력
    Movie* findByTitle(const std::string& title); //2번: 제목으로 검색
    Movie* findById(int movieId) const; //Recommender의 메인추천함수 recommend의 5단계:상위 n개의 영화반환을 위해서 추가함

    void loadFromFile(const std::string& filename) override;//프로그램 시작시 CSV파일에서 데이터를 로드한다.
    void saveToFile(const std::string& filename) const override;//프로그램 종료시 데이터를 CSV파일에 저장한다.
    //이 함수는 저장만 하고 MovieManager내부 값을 바꾸지 않으므로 const를 씀

    int size() const override; //크기 반환 함수 추가
};

