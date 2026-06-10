#include <iostream>
#include <string>
#include <vector>
#include "BaseManager.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"
#include "Recommender.h"

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
    std::cout << " 9. 맞춤 영화 추천 받기\n";

    std::cout << "\n[ 확장 통계 기능 ]\n"; 
    std::cout << " 10. 전체 영화의 통합 평균 평점 조회\n";

    std::cout << "\n 0. 종료\n";
    std::cout << "\n선택 > ";
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    try {
        // 프로그램 시작 시 데이터 불러오기
        movieMgr.loadFromFile("data/movies.csv");
        userMgr.loadFromFile("data/users.csv");
        ratingMgr.loadFromFile("data/ratings.csv");
    } catch (const std::runtime_error& e) {
        std::cerr << "\n [시스템 초기화 실패] " << e.what() << std::endl;
        std::cerr << "필수 데이터 파일이 누락되어 프로그램을 실행할 수 없습니다. 강제 종료합니다." << std::endl;
        return -1; // 파일이 없으면 더 이상 무한 루프 메뉴를 켜지 않고 여기서 안전하게 종료 
    }

    Recommender rec(movieMgr, userMgr, ratingMgr);//원본매니저들을 딱 한번 전달하여 Recommender세팅


    int nextMovieId = 1;
    int nextUserId = 1;

    while (true) {
        showMenu();

        //=======================================잘목된 입력 처리

        std::string input; 
        if (!std::getline(std::cin, input)) break; 
        if (input.empty()) continue; //사용자가 아무것도 입력하지 않고 엔터만 쳤을 때를 처리

        int choice;
        try {
            choice = std::stoi(input);
        } catch (...) {
            std::cout << "숫자만 입력해주세요.\n"; 
            continue;
        }

        if (choice == 0) { //0을 눌렀을 때 종료됨.
            std::cout << "프로그램을 종료합니다.\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::string title, genre, yearStr;
                std::cout << "제목: "; std::getline(std::cin, title); 
                std::cout << "장르: "; std::getline(std::cin, genre);
                std::cout << "개봉연도: "; std::getline(std::cin, yearStr);
                movieMgr.addMovie(Movie(nextMovieId++, title, genre, std::stoi(yearStr)));//문자열로 받은 yearStr을 정수로 변환
                std::cout << "영화가 추가되었습니다.\n";
                break;
            }
            case 2: { //예외처리:findByTitle을 참조자 반환으로 수정함에 따라 메인수정
                std::string title;
                std::cout << "검색할 제목: "; std::getline(std::cin, title); 

                try{  
                    Movie& m = movieMgr.findByTitle(title);
                    std::cout << m << std::endl; // 정상 출력
                }catch(const std::out_of_range& e){//만약 영화가 없어서 함수가 예외를 throw하면 여기로 점프하여 안전하게 처리
                    std::cout << e.what() << std::endl;
                }
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
            case 7: {//예외처리:findByTitle을 참조자 반환으로 수정함에 따라 메인수정
                //1) 사용자로부터 정보수집
                std::string userName, movieTitle, scoreStr;
                std::cout << "사용자 이름: "; std::getline(std::cin, userName);
                std::cout << "영화 제목: "; std::getline(std::cin, movieTitle);
                std::cout << "평점(0~5): "; std::getline(std::cin, scoreStr);

                try {
                    // 2) [사용자 & 영화 검색] 2개 매니저 모두 참조자(&) 방식으로 수정:둘 중 하나라도 데이터가 없으면 즉시 해당 함수에서 예외(out_of_range)를 던져 catch 블록으로 순간이동
                    User& u = userMgr.findByName(userName);
                    Movie& m = movieMgr.findByTitle(movieTitle);

                    // 3) 검색했을 때 사용자와 영화가 모두 존재하므로 평점 계산하여 등록
                    double score = std::stod(scoreStr); // 문자열을 double 타입으로 변환
                    
                    //숫자가 유효한 범위 내에 있는지 검증 방어선 구축 
                    if (score < Movie::MIN_SCORE || score > Movie::MAX_SCORE) {
                        std::cout << "평점은 " << Movie::MIN_SCORE << "에서 " 
                                << Movie::MAX_SCORE << " 사이로 입력해 주세요.\n";
                        break; 
                    }

                    score = score * 2.0;

                    ratingMgr.addRating(Rating(u.getId(), m.getId(), score)); // 전체 평점 리스트에 기록
                    m.addRating(score); 

                    std::cout << "평점이 등록되었습니다.\n";

                } catch (const std::out_of_range& e) {
                    std::cout << "등록실패: " << e.what() << std::endl;
                } catch (const std::invalid_argument& e) {
                    // 혹시 사용자가 평점에 숫자가 아닌 'abc' 같은 걸 입력해 std::stod가 터졌을 때를 대비
                    std::cout << "올바른 평점 숫자를 입력해 주세요.\n";
                }
                break;
            }
            case 8: {//예외처리:findByTitle을 참조자 반환으로 수정함에 따라 메인수정
                std::string title;
                std::cout << "조회할 영화 제목: "; std::getline(std::cin, title);
                try {
                    Movie& m = movieMgr.findByTitle(title);
                    std::cout << "[" << m.getTitle() << "] 평점 목록:\n";
                    ratingMgr.printRatingsByMovie(m.getId());
                } catch (const std::out_of_range& e) {
                    std::cout << "해당 영화를 찾을 수 없습니다. (" << e.what() << ")\n";
                }
                break;
            }
            case 9: {
                //기준 사용자ID, k, n을 입력받는다
                std::string userIdStr, kStr, nStr;
                std::cout << "추천 대상 사용자 ID: "; std::getline(std::cin, userIdStr);
                std::cout << "참고할 유사 사용자 수(K): "; std::getline(std::cin, kStr);
                std::cout << "추천받을 영화 수(N): "; std::getline(std::cin, nStr);

                try {
                    //원래 타입으로 복귀
                    int targetId = std::stoi(userIdStr);
                    int k = std::stoi(kStr);
                    int n = std::stoi(nStr);

                // 이러면 recommendations는 상위n개의 영화객체의 주소가 저장된 벡터가 된다.
                std::vector<Movie*> recommendations = rec.recommend(targetId, k, n);

                if (recommendations.empty()) {//recommendations이 비어있으면 
                    std::cout << "추천할만한 새로운 영화가 없습니다.\n";
                } 
                else {//recommendations가 비어있지 않다면 연산자 오버로딩으로 n개의 영화 정보 출력
                    std::cout << "\n--[추천된 영화 목록 (상위 " << n << "개)]---\n";
                    for (const auto& moviePtr : recommendations) {
                        if (moviePtr) {
                            std::cout << *moviePtr << std::endl; // 연산자 오버로딩 출력 (Moive.h)
                        }
                    }
                }
                } 
                catch (...) { //모든 에러를 다 잡아줌
                    std::cout << "올바른 숫자를 입력해주세요.\n";
                } 

                break;
            }
            case 10: {
                try {
                    std::cout << "\n[시스템 통계 리포트]" << std::endl;
                    std::cout << " ▶ 전체 영화 통합 평균 평점: " << movieMgr.getTotalAverageRating() << "점" << std::endl;
                } catch (const std::exception& e) {
                    // 빈 벡터 나누기(division by zero) 등의 런타임 오류가 날 때를 방어
                    std::cerr << " [오류] 통계 계산 실패: " << e.what() << std::endl;
                }
                break;
            }
            
            default:
                std::cout << "올바른 메뉴 번호를 선택해주세요.\n";
                break;
        }
    } 
            
    //프로그램 종료시 데이터 저장
    movieMgr.saveToFile("data/movies.csv");
    userMgr.saveToFile("data/users.csv");
    ratingMgr.saveToFile("data/ratings.csv");

    std::cout << "모든 데이터가 안전하게 저장되었습니다." << std::endl;
    return 0;
}