#include "MovieManager.h"
#include <iostream>

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