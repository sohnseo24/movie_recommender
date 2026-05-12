#include "Recommender.h"
#include <algorithm> // std::sort를 쓰기 위해 필요
#include <iostream>




// 보조함수1 구현: 유사한 사용자 K명 찾기 
std::vector<int> Recommender::findSimilarUsers(int targetUserId, int k, 
                                              const UserManager& um, 
                                              const RatingManager& rm) {
    // (유사도 점수, 사용자ID) 쌍을 저장할 리스트
    std::vector<std::pair<double, int>> scores;

    // 기준 사용자의 평점 목록 가져오기
    std::vector<Rating> targetRatings = rm.findByUser(targetUserId);
    
    // 전체 사용자를 돌며 유사도 계산
    for (const auto& otherUser : um.getAllUsers()) {
        int otherId = otherUser.getId();
        if (otherId == targetUserId) continue; // 자기 자신은 제외

        std::vector<Rating> otherRatings = rm.findByUser(otherId);
        
        // 지난번에 만든 계산기 사용!
        double sim = SimilarityCalculator::calculate(targetRatings, otherRatings);
        
        // 엣지케이스 2 처리: 유사도가 있는 경우에만 후보에 넣기
        if (sim > -100) { 
            scores.push_back({sim, otherId});
        }  
    }

    // 유사도 점수 높은 순(내림차순)으로 정렬
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    // 상위 k명만 뽑아서 ID 반환
    std::vector<int> topK;
    for (int i = 0; i < k && i < scores.size(); ++i) {
        topK.push_back(scores[i].second);
    }
    
    return topK;
}