#pragma once
#include "Rating.h"
#include <vector>

class SimilarityCalculator{
public: 
    static constexpr int COMMON_MOVIE_WEIGHT = 10;
    static constexpr double ERROR_NO_COMMON_MOVIES = -1.0;//공통영화가 없을 때 리턴값 -100에서 -1.0으로 확정수정(가중평균을 구하려면 소수점 단위의 숫자를 쳐야 정밀한 계산 가능)


    //두 사용자의 평점 목록을 받아 유사도 점수를 반환한다.
    //클수록 더 비슷한 취향.
    //공통으로 평가한 영화가 한편도 없으면 -100을 반환
    static double calculate( //가중평균을 위해 double로 바꿈
        const std::vector<Rating>& user1, const std::vector<Rating>& user2);
};