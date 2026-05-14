#include "Recommender.h"
#include <algorithm> // std::sort를 쓰기 위해 필요
#include <iostream>
using namespace std;

vector<int> Recommender::findSimilarUsers(int targetUserId, int k,
const UserManager& um, const RatingManager& rm){
    //1) (유사도 , userId)쌍을 저장할 벡터 생성 (STL pair활용)
    vector<pair<double, int>> similarity; //<first(=유사도), second(=Id)>임

    //2) 내 평점 가져오기
    vector<Rating> myRatings = rm.findByUser(targetUserId);
    //[엣지케이스 1번]: 평점이 0개인 사용자
    if (myRatings.empty()){
        cout<< "평점 데이터가 부족하여 유사한 사용자를 찾을 수 없습니다"<<endl;
        return vector<int>(); //빈벡터 반환
    }

    //3) 전체 사용자를 돌며 유사도 계산 (자기자신제외)
    const vector<User>& allUsers= um.getAllUsers();
    for(const auto& otherUser: allUsers){
        int otherId= otherUser.getId(); //otherId 저장
        if(otherId==targetUserId) continue; //자기자신 제외

        vector<Rating> otherRatings= rm.findByUser(otherId);//otherId로 다른사람 평점 찾아 otherRatings벡터에 저장

        //유사도 계산(double타입으로)
        double sim= SimilarityCalculator::calculate(myRatings, otherRatings);
        //[엣지케이스 2번]: 공통영화가 없어 유사도 계산이 불가능한(-1.0)경우를 제외하기
        if (sim >-1.0){//공통 영화가 있는 경우만 similarity벡터에 추가
            similarity.push_back({sim, otherId}); 
        }
    }
    //4) 정렬 + 람다식 활용 (내림차순 정렬)
    sort(similarity.begin(), similarity.end(),
    [](const pair<double, int>& a, const pair<double, int>& b){
        return a.first > b.first; //first(유사도)가 큰 순서대로
    });
    //5) 상위 K명의 사용자 ID만 골라내서 반환
    vector<int> topKUsers;
    for(int i=0; i<k && i<similarity.size(); i++){ //k까지 해야하는데 similarity.size()가 k보다 작을 수도 있으니까 방지하기 위해서 &&로 조건 추가해줌
        topKUsers.push_back(similarity[i].second);
    }
    return topKUsers;
}