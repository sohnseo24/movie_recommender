#include <iostream>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

using namespace std;

// 메뉴판 출력 함수
void printMenu() {
    cout << "\n=== Movie Recommender ===" << endl;
    cout << "[ 영화 ]" << endl;
    cout << "1. 영화 추가" << endl;
    cout << "2. 제목으로 검색" << endl;
    cout << "3. 전체 목록 출력" << endl;
    cout << "4. 평점순 정렬 출력" << endl;
    cout << "\n[ 사용자 ]" << endl;
    cout << "5. 사용자 추가" << endl;
    cout << "6. 사용자 목록 출력" << endl;
    cout << "\n[ 평점 ]" << endl;
    cout << "7. 평점 입력" << endl;
    cout << "8. 영화별 평점 보기" << endl;
    cout << "\n0. 종료" << endl;
    cout << "선택 > ";
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    int choice;

    while (true) {
        printMenu();
        cin >> choice;

        if (choice == 0) {
            cout << "프로그램을 종료합니다." << endl;
            break;
        }

        switch (choice) {
            case 1: { //1번: 영화 추가
                int id, year;
                string title, genre;
                cout << "영화 ID: "; 
                cin >> id;
                cin.ignore(); //오류 해결: 정수 입력 후 남은 엔터를 제거하여 getline이 정상 작동하게 함
                cout << "제목: "; getline(cin, title);
                cout << "장르: "; getline(cin, genre);
                cout << "개봉연도: "; cin >> year;
                movieMgr.addMovie(Movie(id, title, genre, year));
                break;
            }
            case 2: { //2번: 제목으로 검색
                string title;
                cout << "검색할 제목: ";
                cin.ignore(); //오류 해결: 메뉴 선택 시 입력한 엔터를 제거
                getline(cin, title);
                
                // MovieManager에서 만든 포인터 반환 함수 사용
                Movie* found = movieMgr.findByTitle(title);
                if (found != nullptr) {
                    cout << "\n[검색 결과]" << endl;
                    cout << *found << endl; // operator<< 오버로딩 활용
                } else {
                    cout << "해당 제목의 영화를 찾을 수 없습니다." << endl;
                }
                break;
            }
            case 3: // 3번: 전체 목록 출력
                movieMgr.printAllMovies();
                break;
            case 4: //4번: 평점순 정렬 출력
                movieMgr.sortByRating();
                movieMgr.printAllMovies();
                break;
        }
    }

    return 0;
}
