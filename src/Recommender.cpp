#include <iostream>
#include "Recommender.h"
#include <algorithm> // std::sort를 쓰기 위해 필요
#include <set>
#include <map>
using namespace std;

vector<int> Recommender::findSimilarUsers(int targetUserId, int k){
    //1단계: (유사도 , userId)쌍을 저장할 벡터 생성 (STL pair활용)
    vector<pair<double, int>> similarity; //<first(=유사도), second(=Id)>임

    //2단계: 내 평점 가져오기
    vector<Rating> myRatings = rm.findByUser(targetUserId);
    //[엣지케이스 1번]: 평점이 0개인 사용자->유사한 사용자 찾을 수 없음
    if (myRatings.empty()){
        cout<< "평점 데이터가 부족하여 유사한 사용자를 찾을 수 없습니다"<<endl;
        return vector<int>(); //빈벡터 반환
    }

    //3단계: 전체 사용자를 돌며 유사도 계산 (자기자신제외)
    const vector<User>& allUsers= um.getAllUsers();
    for(const auto& otherUser: allUsers){
        int otherId= otherUser.getId(); //otherId 저장
        if(otherId==targetUserId) continue; //자기자신 제외

        vector<Rating> otherRatings= rm.findByUser(otherId);//otherId로 다른사람 평점 찾아 otherRatings벡터에 저장

        //유사도 계산(double타입으로)
        double sim= SimilarityCalculator::calculate(myRatings, otherRatings);
        //[엣지케이스 2번]: 공통영화가 없어 유사도 계산이 불가능한(-1.0)경우를 제외하기
        if (sim >SimilarityCalculator::ERROR_NO_COMMON_MOVIES){//공통 영화가 있는 경우만 similarity벡터에 추가
            similarity.push_back({sim, otherId}); 
        }
    }
    //4단계: 정렬 + 람다식 활용 (내림차순 정렬)
    sort(similarity.begin(), similarity.end(),
    [](const pair<double, int>& a, const pair<double, int>& b){
        return a.first > b.first; //first(유사도)가 큰 순서대로
    });
    //5단계: 상위 K명의 사용자 ID만 골라내서 반환
    vector<int> topKUsers;
    for(size_t i=0; i< static_cast<size_t>(k) && i<similarity.size(); i++){ 
        //엣지 케이스 처리: k까지 해야하는데 similarity.size()가 k보다 작을 수도 있으니까 방지하기 위해서 &&로 조건 추가해줌
        topKUsers.push_back(similarity[i].second);
    }
    return topKUsers;
}

std::vector<Movie*> Recommender::recommend(int targetUserId, int k, int n) {
    // 1단계: 내 평점 가져오기 및 본 영화 필터링용 set 구축
    std::vector<Rating> myRatings = rm.findByUser(targetUserId);
    if (myRatings.empty()) {
        std::cout << "평점 기록이 없어 추천을 진행할 수 없습니다." << std::endl;
        return {};
    }
    std::set<int> watchedMovieIds;
    for(const auto& r : myRatings) watchedMovieIds.insert(r.getMovieId());

    // 2~3단계: 타인과의 유사도 계산 후 상위 K명 선택
    std::vector<int> topKUsers = findSimilarUsers(targetUserId, k);
    if (topKUsers.empty()) return {}; 

    // 4단계 분리-> 후보 영화 수집 및 가중 평균 점수 누적 함수 호출
    std::map<int, double> movieScores = collectCandidateScores(myRatings, watchedMovieIds, topKUsers);

    // 5단계 분리-> 점수순 내림차순 정렬 함수 호출
    std::vector<std::pair<int, double>> finalRank = sortCandidates(movieScores);

    // 최종 반환 분리-> 상위 N개 Movie 객체 포인터 안전 적재 및 반환
    return buildFinalRecommendations(finalRank, n);
}

// [4단계]: 후보 영화 수집 및 가중평균 누적 점수 계산 구현
std::map<int, double> Recommender::collectCandidateScores(
    const std::vector<Rating>& myRatings, 
    const std::set<int>& watchedMovieIds, 
    const std::vector<int>& topKUsers
) {
    std::map<int, double> movieScores;

    for(int friendId : topKUsers){
        std::vector<Rating> friendRatings = rm.findByUser(friendId); 
        double similarity = SimilarityCalculator::calculate(myRatings, friendRatings);

        for(const auto& r : friendRatings){
            int movieId = r.getMovieId();
            
            // 필터링: 내가 안본 영화만 모으기
            if(watchedMovieIds.find(movieId) == watchedMovieIds.end()){
                // 가중평균 누적 점수 연산
                movieScores[movieId] += (similarity * r.getScore());
            }
        }
    }
    return movieScores;
}

// [5단계-A]: 누적된 영화 점수들을 내림차순 정렬 구현
std::vector<std::pair<int, double>> Recommender::sortCandidates(
    const std::map<int, double>& movieScores
) {
    std::vector<std::pair<int, double>> finalRank;
    
    for (auto const& [id, score] : movieScores){
        finalRank.push_back({id, score});
    }
    
    std::sort(finalRank.begin(), finalRank.end(), [](const auto& a, const auto& b){
        return a.second > b.second; 
    });
    
    return finalRank;
}

// [5단계-B]: 상위 N개 추출 및 참조자 기반 예외 처리 필터링 구현 
std::vector<Movie*> Recommender::buildFinalRecommendations(
    const std::vector<std::pair<int, double>>& finalRank, 
    int n
) {
    std::vector<Movie*> result;
    
    for(size_t i = 0; i < static_cast<size_t>(n) && i < finalRank.size(); i++){
        try {
            // 포인터 대신 MovieManager가 제공하는 const Movie& 참조자로 안전하게 영화를 조회
            const Movie& m = mm.findById(finalRank[i].first); 

            // Recommender 리턴 타입 스펙(Movie*)을 맞추기 위해 실제 메모리 주소값(&m) 추출 후 적재
            result.push_back(const_cast<Movie*>(&m));

        } catch (const std::out_of_range& e) {
            // 유령 영화 ID 예외 발생 시 프로그램 다운을 막고 안전하게 로그만 출력 후 스킵
            std::cerr << "[경고] 추천 리스트 빌드 중 예외 발생: " << e.what() << std::endl;
        }
    } 
    return result;
}

