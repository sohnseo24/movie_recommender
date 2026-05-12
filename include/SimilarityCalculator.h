#include "Rating.h"
#include <vector>
class SimilarityCalculator{
public: 
    //두 사용자의 평점 목록을 받아 유사도 점수를 반환한다.
    //클수록 더 비슷한 취향.
    //공통으로 평가한 영화가 한편도 없으면 -100을 반환
    static double calculate( //가중평균을 위해 double로 바꿈
        const std::vector<Rating>& user1, const std::vector<Rating>& user2);
};