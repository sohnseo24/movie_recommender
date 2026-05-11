#include "Rating.h"
#include "RatingManager.h"
#include <iostream>
#include <fstream>   // ifstream 사용을 위해
#include <sstream>   // stringstream 사용을 위해
#include <string>    // string, stoi, stod 사용을 위해

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(r);
}


void RatingManager::printRatingsByMovie(int movieId) const {
    int count = 0; // 찾은 평점의 개수를 저장
    for (size_t i = 0; i < ratings.size(); i++) {
        if (ratings[i].getMovieId() == movieId) {
            std::cout << ratings[i] << std::endl; 
            count++;
        }
    }
    if (count == 0) std::cout << "해당 영화에 대한 평점이 없습니다." << std::endl;
}

void RatingManager::loadRatings(const std::string& filename) { //CSV로딩을 위해 새로 추가
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

        std::getline(ss, token, ','); int userId = std::stoi(token);
        std::getline(ss, token, ','); int movieId = std::stoi(token);
        std::getline(ss, token, ','); int score = std::stoi(token);

        //읽어온 데이터를 바로 ratings 벡터에 추가!
        ratings.push_back(Rating(userId, movieId, score)); 
    }
    std::cout << "[알림] " << filename << " 데이터를 성공적으로 불러왔습니다." << std::endl;
}