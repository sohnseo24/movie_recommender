#include <iostream>
#include <string>
#include <vector>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"

void showMenu() {
    std::cout << "\n=== Movie Recommender ===\n";
    std::cout << "\n[ 영화 ]\n";
    std::cout << " 1. 영화 추가\n";
    std::cout << " 2. 제목으로 검색\n";
    std::cout << " 3. 전체 목록 출력\n";
    std::cout << " 4. 평점순 정렬 출력\n";
    
    std::cout << "\n[ 사용자 ]\n";
    std::cout << " 5. 사용자 추가\n";
    std::cout << " 6. 사용자 목록 출력\n";
    
    std::cout << "\n[ 평점 ]\n";
    std::cout << " 7. 평점 입력\n";
    std::cout << " 8. 영화별 평점 보기\n";
    std::cout << " 9. 사용자 유사도 계산\n";
    
    std::cout << "\n 0. 종료\n";
    std::cout << "\n선택 > ";
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    //프로그램 시작 시 데이터 불러오기
    movieMgr.loadMovies("data/movies.csv");
    userMgr.loadUsers("data/users.csv");
    ratingMgr.loadRatings("data/ratings.csv");


    int nextMovieId = 1;
    int nextUserId = 1;

    while (true) {
        showMenu();

        //=======================================잘목된 입력 처리

        std::string input; //일단 문자열(큰 범위)로 입력을 받을 것
        if (!std::getline(std::cin, input)) break; //cin을 쓰면 입력 버퍼에 개행 문자가 남아 버퍼가 꼬여 getline사용
        //사용자가 강제로 입력을 종료(Ctrl+Z 등)했을 때 프로그램이 강제로 멈추게 함.
        if (input.empty()) continue; //사용자가 아무것도 입력하지 않고 엔터만 쳤을 때를 처리

        int choice;
        try {
            choice = std::stoi(input);//try로 일단 이렇게 실행
        } catch (...) {
            std::cout << "숫자만 입력해주세요.\n"; //stoi는 문자열을 정수로 변환하고 문자열이 아닌경우 예외 발생시킨다.
            continue;
        }

        //=======================================여기서부터 진짜 시작
        if (choice == 0) { //0을 눌렀을 때 종료됨.
            std::cout << "프로그램을 종료합니다.\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::string title, genre, yearStr;
                std::cout << "제목: "; std::getline(std::cin, title); 
                //getline을 사용하면 엔터 키가 남아서 생기는 문제를 예방할 뿐만아니라 공백이 있는 영화 제목도 받을 수 있음
                std::cout << "장르: "; std::getline(std::cin, genre);
                std::cout << "개봉연도: "; std::getline(std::cin, yearStr);
                //int year; std::cin >> year; 이렇게 받으면 엔터가 버퍼에 남아 다음 영화를 입력받을 때 제목입력시 엔터를 받고 끝나버리기 때문에 
                //getline(엔터까지 읽고 엔터까지 버퍼에서 삭제시켜주는)을 쓴 것.
                movieMgr.addMovie(Movie(nextMovieId++, title, genre, std::stoi(yearStr)));//문자열로 받은 yearStr을 정수로 변환
                std::cout << "영화가 추가되었습니다.\n";
                break;
            }
            case 2: { 
                std::string title;
                std::cout << "검색할 제목: "; std::getline(std::cin, title); 
                Movie* m = movieMgr.findByTitle(title);
                if (m) std::cout << *m << std::endl;
                else std::cout << "해당 영화를 찾을 수 없습니다.\n";
                break;
            }
            case 3:
                movieMgr.printAllMovies();
                break;
            case 4:
                movieMgr.sortByRating();
                movieMgr.printAllMovies();
                break;
            case 5: {
                std::string name, email;
                std::cout << "이름: "; std::getline(std::cin, name);
                std::cout << "이메일: "; std::getline(std::cin, email);
                userMgr.addUser(User(nextUserId++, name, email));
                std::cout << "사용자가 추가되었습니다.\n";
                break;
            }
            case 6:
                userMgr.printAllUsers();
                break;
            case 7: {
                //1) 사용자로부터 정보수집
                std::string userName, movieTitle, scoreStr;
                std::cout << "사용자 이름: "; std::getline(std::cin, userName);
                std::cout << "영화 제목: "; std::getline(std::cin, movieTitle);
                std::cout << "평점(0~5): "; std::getline(std::cin, scoreStr);
                //2) 그 정보를 가지고 검색
                User* u = userMgr.findByName(userName);
                Movie* m = movieMgr.findByTitle(movieTitle);

                //3) 검색했을 떄 있는 영화인지 판단 후 평점 계산하여 등록

                if (u && m) { //둘다 nullptr을 반환하지 않으면 사용자와 영화가 모두 존재하는 구나 알 수 있음
                    double score = std::stod(scoreStr); //scoreStr을 문자열로 받았기 때문에 double타입으로 만들어 줌.

                    ratingMgr.addRating(Rating(u->getId(), m->getId(), score));//전체 평점 리스트에 누가 몇점 줬는지 기록
                    m->addRating(score);//개별 영화의 평점 계산을 위해 
                    //객체를 직접 가졌을 떄는 m.addRating이라고 썼을 텐데 m은 주소만 가진 것이므로 ->를 써야 한다.
                    std::cout << "평점이 등록되었습니다.\n";
                } else {
                    std::cout << "사용자 또는 영화를 찾을 수 없습니다.\n";
                }
                break;
            }
            case 8: {
                std::string title;
                std::cout << "조회할 영화 제목: "; std::getline(std::cin, title);
                Movie* m = movieMgr.findByTitle(title);
                if (m) { //nullptr이 아니라면
                    std::cout << "[" << m->getTitle() << "] 평점 목록:\n";
                    ratingMgr.printRatingsByMovie(m->getId());
                } else { //nullptr 이라면
                    std::cout << "해당 영화를 찾을 수 없습니다.\n";
                }
                break;
            }
            case 9: {
                std::string targetName;
                std::cout << "유사도를 계산할 사용자 이름: ";
                std::getline(std::cin, targetName);

                // 1) 기준이 될 사용자 찾기
                User* targetUser = userMgr.findByName(targetName);
                if (!targetUser) {
                    std::cout << "사용자를 찾을 수 없습니다.\n";
                    break;
                }

                int targetId = targetUser->getId();
                // 2) 기준 사용자의 모든 평점 기록 가져오기
                std::vector<Rating> myRatings = ratingMgr.findByUser(targetId);

                int bestUser = -1;
                int bestSim = -101; // 초기값 (최솟값보다 작게)

                // 3) 전체 사용자를 순회하며 유사도 비교
                // userMgr에서 전체 사용자 리스트를 가져와서 반복문 돌리기
                const std::vector<User>& allUsers = userMgr.getAllUsers(); 

                for (const auto& otherUser : allUsers) {
                    int otherId = otherUser.getId();
                    
                    if (otherId == targetId) continue; // 자기 자신은 제외

                    // 비교할 상대방의 평점 목록 가져오기
                    std::vector<Rating> otherRatings = ratingMgr.findByUser(otherId);
                    
                    // 유사도 계산기 작동
                    int sim = SimilarityCalculator::calculate(myRatings, otherRatings);

                    // 최댓값 갱신 패턴
                    if (sim > bestSim) {
                        bestSim = sim;
                        bestUser = otherId;
                    }
                }

                // 4) 결과 출력
                if (bestUser != -1 && bestSim != -100) {
                    std::cout << "\n[분석 결과]" << std::endl;
                    std::cout << targetName << "님과 가장 취향이 비슷한 사용자는 User ID: " << bestUser << "입니다." << std::endl;
                    std::cout << "(유사도 점수: " << bestSim << "점)" << std::endl;
                } else {
                    std::cout << "유사한 사용자를 찾을 수 없습니다. (공통 평점 부족)\n";
                }
                break;
            }
            default:
                std::cout << "잘못된 선택입니다.\n";
                break;
        }
    }
    //프로그램 종료시 데이터 저장
    movieMgr.saveMovies("data/movies.csv");
    userMgr.saveUsers("data/users.csv");
    ratingMgr.saveRatings("data/ratings.csv");

    std::cout << "모든 데이터가 안전하게 저장되었습니다." << std::endl;
    return 0;
}