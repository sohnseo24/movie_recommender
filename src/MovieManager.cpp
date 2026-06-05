#include "Movie.h"
#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>   // ifstream 사용을 위해
#include <sstream>   // stringstream 사용을 위해
#include <string>    // string, stoi, stod 사용을 위해
#include <numeric> // std::accumulate를 쓰기 위해 

using namespace std;

void MovieManager::addMovie(const Movie& m) {
    movies.push_back(m); //메모리 자동관리 , 동적 크기 조절을 위해 
}

void MovieManager::printAllMovies() const { 
    if (movies.empty()) {
        std::cout << "현재 등록된 영화가 없습니다." << std::endl;
        return;
    }
    for (const auto& m : movies) {
        std::cout << m << std::endl; 
    }
}


void MovieManager::sortByRating() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        // 평점이 다르면 평점 내림차순
        if (a.getAverageRating() != b.getAverageRating()) {
            return a.getAverageRating() > b.getAverageRating();
        }
        // 평점이 같으면 제목 가나다순(오름차순) 
        return a.getTitle() < b.getTitle();
    });
    
    std::cout << "\n[알림] 평점순(다중 기준)으로 정렬되었습니다." << std::endl;
}

Movie& MovieManager::findByTitle(const std::string& title) {
    for (Movie& m : movies) {
        // Movie 클래스의 operator==사용
        if (m == title) { 
            return m; // 찾으면 그 영화의 참조자 전달(수정:예외처리)
        }
    }
    throw std::out_of_range("Error: '" + title + "' 해당 제목의 영화를 찾을 수 없습니다.");//예외처리:nullptr 대신 호출자에게 검색 실패 예외를 명시적으로 던짐.
}

const Movie& MovieManager::findById(int movieId) const{//Recommender의 메인추천함수 recommend의 5단계:상위 n개의 영화반환을 위해서 추가함
    // const 함수 내부라 원본을 지키기 위해 일단 const Movie&로 꺼내기
    for (const Movie& m: movies) {//movies(영화들 모아놓은 벡터)에서 movie(영화하나) 하나씩 꺼내서 
        if(m.getId()==movieId){
            return m; //(수정:예외처리) 
        }
    }
    throw std::out_of_range("Error: ID [" + std::to_string(movieId) + "]에 해당하는 영화가 존재하지 않습니다.");//예외처리:ID 범위 초과 및 검색 실패 
}

void MovieManager::loadFromFile(const std::string& filename) { //CSV로딩을 위해 새로 추가
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("치명적 오류: 영화 데이터 파일('" + filename + "')을 열 수 없습니다.");
    }

    std::string line;
    std::getline(file, line); // 헤더 스킵

    int lineNum = 1; //[예외처리3: 추가] 에러가 발생한 라인 번호를 추적하기 위한 변수 (헤더가 1번 줄)
    
    while (std::getline(file, line)) {
        lineNum++; // 줄을 읽을 때마다 카운트 업
        try{
            std::stringstream ss(line);
            std::string token;

            std::getline(ss, token, ','); int id = std::stoi(token);
            std::getline(ss, token, ','); std::string title = token;
            std::getline(ss, token, ','); int year = std::stoi(token);
            std::getline(ss, token, ','); double rating = std::stod(token);

            //읽어온 데이터를 바로 movies 벡터에 추가
            movies.push_back(Movie(id, title, year, rating));

        }catch(const std::exception& e) {
            // 파싱 에러 시 프로그램이 죽지 않고, 에러 로그만 찍은 뒤 continue 처리
                std::cerr << " [CSV 데이터 손상] 영화 매니저 " << lineNum << "번 줄 건너뜀 (원인: " << e.what() << ")" << std::endl;
                // 루프 안이라서 별도의 조치 없이 다음 데이터 줄로 자연스럽게 넘어갈것 
            }
    }
    std::cout << "[알림] " << filename << " 데이터를 성공적으로 불러왔습니다." << std::endl;

}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename); // 파일 열기

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 저장 실패" << std::endl;
        return;
    }

    // 1. 헤더 작성
    file << "id,title,year,rating" << std::endl;

    // 2. 데이터 작성
    for (const auto& m : movies) {
        file << m.getId() << "," //콘솔창에 글자를 쓸 때 std::cout <<을 쓰는 것처럼, 여기서는 file <<을 사용해 콘솔창 대신 열어둔 파일 내부에 글자를 씀
             << m.getTitle() << "," 
             << m.getReleaseYear() << "," 
             << m.getAverageRating() << std::endl; 
    }

    file.close();
    std::cout << "[알림] " << filename << " 저장 완료: " << movies.size() << "건" << std::endl;
}

int MovieManager::size() const {
    return movies.size(); // 영화 벡터의 크기 반환!
}

double MovieManager::getTotalAverageRating() const {
    // 예외 처리: 빈 vector를 나누면 발생하는 division by zero 방어 
    if (movies.empty()) {
        throw std::runtime_error("영화 데이터가 없습니다."); 
    }

    // Modern C++ STL 방식: std::accumulate + Lambda 활용 
    double sum = std::accumulate(
        movies.begin(), movies.end(), 0.0,
        [](double acc, const Movie& m) {
            return acc + m.getAverageRating(); // 누적값(acc)에 각 영화의 평점을 더해나감 
        }
    );

    return sum / movies.size(); 
}
