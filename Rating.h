#pragma once

class Rating {
private:
    int    userId;    // 평가한 사용자
    int    movieId;   // 평가 대상 영화
    double score;     // 0.0 ~ 5.0

public:
    Rating();
    Rating(int userId, int movieId, double score);

    int getUserId() const;
    int getMovieId() const;
    double getScore() const;


    void display() const;

    // TODO: 생성자 (score 유효성 검사 포함)
    //       getter, display()
    // ⚠ score 가 0~5 범위인지 확인!
};

