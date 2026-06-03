#pragma once
#include <vector>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"

class Recommender {
public:
    Recommender(const MovieManager& movieMgr, const UserManager& userMgr, const RatingManager& ratingMgr)
        : mm(movieMgr), um(userMgr), rm(ratingMgr) {} //생성자 초기화 리스트

    // 1. 메인 추천함수: 특정 유저에게 K명을 참고하여 N개의 영화 추천
    // 가중 평균 알고리즘을 사용하여 N개의 영화 추천
    // findSimilarUsers가 찾아준 K명을 바탕으로 후보 영화를 수집하고, 가중 평균 점수를 계산해 정렬 후 반환하는 로직
    std::vector<Movie*> recommend(int targetUserId, int k, int n);

private:
    const MovieManager& mm;
    const UserManager& um;
    const RatingManager& rm;


    // 2. 보조함수: 나와 가장 유사한 상위 K명의 사용자 ID를 찾아 반환
    //(내 평점을 가져 온 후 날 제외하고 나머지 모든 사용자와 유사도 계산-> sort+람다를 사용해 유사도상위 K명 선택)
    std::vector<int> findSimilarUsers(int targetUserId, int k);
    
};

//엣지 케이스 목록 작성
//1) 평점 0개인 사용자: 평점 데이터가 하나도 없어 유사도 계산이 불가능한 경우.

//2) 유사사용자 K명 미만

//3) 추천할 영화 N개 미만  

//4) 평점 만점자: 모든 영화를 다 봐서 더 이상 추천할 새로운 영화가 없는 경우.