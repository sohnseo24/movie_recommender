#include "MovieManager.h"
#include <iostream>
#include <algorithm>

void MovieManager::addMovie(const Movie& m) {
    movies.push_back(m); 
}

void MovieManager::printAllMovies() const {
    if (movies.empty()) {
        std::cout << "현재 등록된 영화가 없습니다." << std::endl;
        return;
    }
    for (const auto& m : movies) {
        m.display(); // Movie 클래스의 display() 호출
    }
}

void MovieManager::sortByRating() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.getAverageRating() > b.getAverageRating(); 
    });
    
    std::cout << "평점순으로 영화를 정렬했습니다." << std::endl;
}