#pragma once
#include <vector>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"

class Recommender {
public:
    // 1. 메인 추천함수: 특정 유저에게 K명을 참고하여 N개의 영화 추천
    // 가중 평균 알고리즘을 사용하여 N개의 영화 추천
    std::vector<Movie*> recommend(int targetUserId, int k, int n, 
                                 const MovieManager& mm, 
                                 const UserManager& um, 
                                 const RatingManager& rm);

private:
    // 2. 보조함수1: 나와 가장 유사한 상위 K명의 사용자 ID를 찾아 반환
    std::vector<int> findSimilarUsers(int targetUserId, int k, 
                                     const UserManager& um, 
                                     const RatingManager& rm);
                                     
    // 3. 보조함수2: 특정 영화에 대한 예상 평점(가중 평균 계산)
    double predictRating(int targetUserId, int movieId, const std::vector<int>& topKUsers, 
                        const RatingManager& rm);
};

//엣지 케이스 목록 작성
//1) 신규 사용자: 평점 데이터가 하나도 없어 유사도 계산이 불가능한 경우.

//2) 고립된 취향: 다른 유저와 공통으로 본 영화가 하나도 없는 경우.

//3) 데이터 부족: 추천할만한 영화(내가 안 본 영화)가 N개보다 적은 경우.

//4) 평점 만점자: 모든 영화를 다 봐서 더 이상 추천할 새로운 영화가 없는 경우.