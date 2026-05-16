#pragma once
#include <vector>
#include <string>
#include "Rating.h"
#include "BaseManager.h"

class RatingManager: public BaseManager{
private:
    std::vector<Rating> ratings; 

public:
    void addRating(const Rating& r); //7번: 평점 입력
    void printRatingsByMovie(int movieId) const; //8번: 영화별 평점 보기

    void loadFromFile(const std::string& filename) override;//프로그램 시작시 CSV파일에서 데이터를 로드한다.
    void saveToFile(const std::string& filename) const override;//프로그램 종료시 데이터를 CSV파일에 저장한다.
    //이 함수는 저장만 하고 RatingManager내부 값을 바꾸지 않으므로 const를 씀

    std::vector<Rating> findByUser(int userId) const; 
    //9번: 사용자의 ID를 넣으면 그 사람이 남긴 모든 평점을 뽑아주는 기능

    int size() const override; //크기 반환 함수 추가
};