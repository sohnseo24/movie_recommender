#pragma once
#include <vector>
#include "Rating.h"

class RatingManager {
private:
    std::vector<Rating> ratings; 

public:
    void addRating(const Rating& r); //7번: 평점 입력
    void printRatingsByMovie(int movieId) const; //8번: 영화별 평점 보기
    void loadRatings(const std::string& filename);//프로그램 시작시 CSV파일에서 데이터를 로드한다.
    void saveRatings(const std::string& filename) const;//프로그램 종료시 데이터를 CSV파일에 저장한다.
    //이 함수는 저장만 하고 RatingManager내부 값을 바꾸지 않으므로 const를 씀

    std::vector<Rating> findByUser(int userId) const; 
    //사용자의 ID를 넣으면 그 사람이 남긴 모든 평점을 뽑아주는 기능
};