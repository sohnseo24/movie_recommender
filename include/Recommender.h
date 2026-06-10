#pragma once
#include <vector>
#include <map>
#include <set>
#include <utility>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"

class Recommender {
public:
    Recommender(const MovieManager& movieMgr, const UserManager& userMgr, const RatingManager& ratingMgr)
        : mm(movieMgr), um(userMgr), rm(ratingMgr) {} //생성자 초기화 리스트

    // 1. 메인 추천함수: 특정 유저에게 K명을 참고하여 N개의 영화 추천
    std::vector<Movie*> recommend(int targetUserId, int k, int n);

private:
    const MovieManager& mm;
    const UserManager& um;
    const RatingManager& rm;


    // 2. 보조함수: 나와 가장 유사한 상위 K명의 사용자 ID를 찾아 반환
    std::vector<int> findSimilarUsers(int targetUserId, int k);

    //리팩토링 추가 구역
    // [분리된 4단계 스펙]: 후보 영화 수집 및 가중평균 누적 점수 계산
    std::map<int, double> collectCandidateScores(
        const std::vector<Rating>& myRatings, 
        const std::set<int>& watchedMovieIds, 
        const std::vector<int>& topKUsers
    );

    // [분리된 5단계-A 스펙]: 누적된 영화 점수들을 내림차순 정렬
    std::vector<std::pair<int, double>> sortCandidates(
        const std::map<int, double>& movieScores
    );

    // [분리된 5단계-B 스펙]: 상위 N개 추출 및 예외 처리를 거쳐 최종 Movie* 포인터 리스트 구축 🛡️
    std::vector<Movie*> buildFinalRecommendations(
        const std::vector<std::pair<int, double>>& finalRank, 
        int n
    );
    
};

//엣지 케이스 목록 작성
//1) 평점 0개인 사용자: 평점 데이터가 하나도 없어 유사도 계산이 불가능한 경우.

//2) 유사사용자 K명 미만

//3) 추천할 영화 N개 미만  

//4) 평점 만점자: 모든 영화를 다 봐서 더 이상 추천할 새로운 영화가 없는 경우.