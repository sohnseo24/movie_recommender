#include <iostream>
#include <string>
#include <vector>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

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
    
    std::cout << "\n 0. 종료\n";
    std::cout << "\n선택 > ";
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    int nextMovieId = 1;
    int nextUserId = 1;

    while (true) {
        showMenu();

        std::string input;
        if (!std::getline(std::cin, input)) break;
        if (input.empty()) continue;

        int choice;
        try {
            choice = std::stoi(input);
        } catch (...) {
            std::cout << "숫자만 입력해주세요.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "프로그램을 종료합니다.\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::string title, genre, yearStr;
                std::cout << "제목: "; std::getline(std::cin, title);
                std::cout << "장르: "; std::getline(std::cin, genre);
                std::cout << "개봉연도: "; std::getline(std::cin, yearStr);
                movieMgr.addMovie(Movie(nextMovieId++, title, genre, std::stoi(yearStr)));
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
                std::string userName, movieTitle, scoreStr;
                std::cout << "사용자 이름: "; std::getline(std::cin, userName);
                std::cout << "영화 제목: "; std::getline(std::cin, movieTitle);
                std::cout << "평점(0~5): "; std::getline(std::cin, scoreStr);

                User* u = userMgr.findByName(userName);
                Movie* m = movieMgr.findByTitle(movieTitle);

                if (u && m) {
                    double score = std::stod(scoreStr);
                    ratingMgr.addRating(Rating(u->getId(), m->getId(), score));
                    m->addRating(score);
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
                if (m) {
                    std::cout << "[" << m->getTitle() << "] 평점 목록:\n";
                    ratingMgr.printRatingsByMovie(m->getId());
                } else {
                    std::cout << "해당 영화를 찾을 수 없습니다.\n";
                }
                break;
            }
            default:
                std::cout << "잘못된 선택입니다.\n";
                break;
        }
    }
    return 0;
}