#include "Movie.h"
#include "MovieManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>   // ifstream 사용을 위해
#include <sstream>   // stringstream 사용을 위해
#include <string>    // string, stoi, stod 사용을 위해
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

Movie* MovieManager::findByTitle(const std::string& title) {
    for (Movie& m : movies) {
        // Movie 클래스의 operator==사용
        if (m == title) { 
            return &m; // 찾으면 그 영화의 주소 전달
        }
    }
    return nullptr; // 못 찾으면 nullptr 전달
}

void MovieManager::loadMovies(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 열 수 없습니다" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // 헤더 스킵

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); int id = std::stoi(token);
        std::getline(ss, token, ','); std::string title = token;
        std::getline(ss, token, ','); int year = std::stoi(token);
        std::getline(ss, token, ','); double rating = std::stod(token);

        // 핵심: 읽어온 데이터를 바로 movies 벡터에 추가!
        movies.push_back(Movie(id, title, year, rating)); 
    }
    std::cout << "[알림] " << filename << " 데이터를 성공적으로 불러왔습니다." << std::endl;
}