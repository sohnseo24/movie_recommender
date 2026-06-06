#include "SimilarityCalculator.h"
#include <cstdlib> //std::abs

double SimilarityCalculator::calculate(
    const std::vector<Rating>& user1, 
    const std::vector<Rating>& user2)
{
    int commonCount=0;//공통으로 본 영화 수 
    int scoreDiffSum=0; //평점 차이의 합

    //이중 반복문: user1의 모든 평점* user2의 모든 평점
    for(const Rating&r1: user1){
        for(const Rating& r2: user2){
            if(r1.getMovieId()==r2.getMovieId()){
                commonCount++;
                scoreDiffSum+=std::abs(r1.getScore()-r2.getScore());
            }
        }
    }
    //공통 영화가 없으면 비교 자체가 불가능->매우 낮은 점수
    if(commonCount==0){
        return ERROR_NO_COMMON_MOVIES; 
    }
    //단순 유사도 공식
    return commonCount*COMMON_MOVIE_WEIGHT-scoreDiffSum;
}