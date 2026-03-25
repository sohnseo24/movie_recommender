#include <iostream>
#include <vector>
#include "Movie.h"
#include "User.h"
#include "Rating.h"

int main() {
    //1. Movie객체들을 vector에 담음
    std::vector <Movie> movies;
    movies.push_back(Movie(1,"기생충", "드라마", 2019));
    movies.push_back(Movie(2,"인셉션", "SF", 2010));

    //2. User 객체 생성
    User u1(1,"손서영","sohnseo24@gmail.com");
    
    //3. Rating 객체생성, 유효성 검사 포함함
    Rating r1(1,1,4.8); //정상
    Rating r2(1,2,9.9); //유효성 검사로 인해 0.0 처리됨

    //4. 결과 출력
    std::cout << "영화 목록 (vector)" <<std::endl;
    for (const auto& m : movies){
        m.display();
    }
    std::cout<<"\n사용자 정보"<<std::endl;
    u1.display();

    std::cout<<"\n평점 기록"<<std::endl;
    r1.display();
    r2.display();

    return 0;
    }




    