#include "Rating.h"
#include <iostream>

//기본 생성자
Rating::Rating()
    :userId(0), movieId(0), score(0.0) {}

Rating::Rating(int userId, int movieId, double s)
    :userId(userId), movieId(movieId){
        if(s<0.0 || s>5.0){
            std::cout<<"Warning: Invalid score. Setting to 0.0"<<std::endl;
            score=0.0;
        }
        else{
            score=s;
        }
    }

int Rating::getUserId()         const {return userId;}
int Rating::getMovieId()    const {return movieId;}
double Rating::getScore()   const {return score;}
    
void Rating::display() const {           // 중복 제거 — 하나만 유지
    std::cout << "userId: "<< userId << std::endl
    << "movieId: " << movieId << std::endl
    << "score: " << score << std::endl;
}