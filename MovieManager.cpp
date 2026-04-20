#include "MovieManager.h"
#include <iostream>
#include <algorithm>

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