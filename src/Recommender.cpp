#include <iostream>
#include "Recommender.h"
#include <algorithm> // std::sort를 쓰기 위해 필요
#include <set>
#include <map>
using namespace std;

vector<int> Recommender::findSimilarUsers(int targetUserId, int k){
    //1) (유사도 , userId)쌍을 저장할 벡터 생성 (STL pair활용)
    vector<pair<double, int>> similarity; //<first(=유사도), second(=Id)>임

    //2) 내 평점 가져오기
    vector<Rating> myRatings = rm.findByUser(targetUserId);
    //[엣지케이스 1번]: 평점이 0개인 사용자->유사한 사용자 찾을 수 없음
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



vector<Movie*> Recommender::recommend(int targetUserId, int k, int n){//n:최종 상위 몇개영화 반환할건지
    //1단계(나): 내 평점 가져오기->내가 이미 본 영화 ID들 set에 저장(STL set활용->중복제거 및 빠른 검색)
    vector<Rating> myRatings=rm.findByUser(targetUserId);
    if (myRatings.empty()){//[엣지케이스 1번]: 평점이 0개인 사용자-> 나에 대한 정보가 없어 추천자체가 불가능
        cout<<"평점 기록이 없어 추천을 진행할 수 없습니다."<<endl;
        return {}; //빈 벡터 반환 
    }
    set<int> watchedMovieIds;
    for(const auto& r: myRatings){
        watchedMovieIds.insert(r.getMovieId());
    }

    //2~3단계(타인): 모든 사용자와의 유사도를 계산해서 상위 K명 선택, 후에 4단계에서 topKUsers에 저장된 Id를 friendId로 받아 findByUser로 그 friendId에 해당하는 타인의 평점을 friendRatings에 저장 
    vector<int> topKUsers=findSimilarUsers(targetUserId, k, um, rm);
    if(topKUsers.empty()) return{}; 

    //4단계: 후보영화 수집 및 점수 누적(필터링:내가 안본 영화만 모으기=>가중평균:유사도가 높은 사용자들의 평점에 가중치주기
    //=>정렬:점수높은 순으로 영화나열=>반환: 상위 N개만 골라 반환)
    //STL map활용 map<영화 ID, 누적점수>
    map<int, double> movieScores;

    for(int friendId: topKUsers){
        vector<Rating> friendRatings= rm.findByUser(friendId); //findByUser를 쓰면 그 사용자의 userRatings라는 벡터를 돌려줌
        double similarity=SimilarityCalculator::calculate(myRatings,friendRatings);//가중치를 계산하기 위해서 친구와 나의 유사도를 다시 계산

        for(const auto& r: friendRatings){
            int movieId =r.getMovieId();//friendRatings는 RatingManager에 의해 userRatings벡터니까(즉 user의 모든 평점을 다 모아놓은 벡터니까 거기서 movieId를 뽑는다.)
            
            //필터링: 내가 안본 영화만 모아야 함(set 검색)
            if(watchedMovieIds.find(movieId)== watchedMovieIds.end()){
                //가중평균: 유사도 * 친구 평점을 점수로 누적
                movieScores[movieId] +=(similarity * r.getScore());//map에 추가하면 이미 있는 아이디에 대해서는 누적해서 더하고, 없는 아이디에 대해서는 추가로 만들어서 저장한다.
            }
        }
    }

    //5단계: 점수계산&정렬반환 (sort,람다)
    vector<pair<int, double>> finalRank;
    for (auto const& [id, score]: movieScores){
        finalRank.push_back({id, score});
    }
    sort(finalRank.begin(), finalRank.end(),[](const auto& a, const auto& b){
        return a.second > b.second; //점수가 큰 순서대로 정렬(내림차순)
    });
    //상위 n개의 Movie객체 포인터 담기
    vector<Movie*> result;
    for(int i=0; i<n&&i<finalRank.size(); i++){
        Movie* m= mm.findById(finalRank[i].first);
        if(m != nullptr) result.push_back(m); //MovieManager가 영화를 성공적으로 찾아왔을 때만 담는다
    }
    return result;
}
//<Movie*>는 Movie객체가 메모리 어디에 있는지 가리키는 주소값(포인터)를 의미
//Movie객체 자체(용량이 큼)를 복사하면 비효율적이므로 주소만 넘겨주는 것
//MovieManager가 이미 모든 영화 정보를 들고 있기 때문에 recommend는 그냥 이 영화가 좋다 추천하는 역할-> 주소만 콕 집어서 알려주는게 훨씬 효율적
