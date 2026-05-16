#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "BaseManager.h"

class UserManager: public BaseManager{
private:
    std::vector<User> users; 

public:
    // 5번: 사용자 추가
    void addUser(const User& user);

    // 6번: 사용자 목록 출력
    void printAllUsers() const;

    // 7번 평점 입력을 위해 미리 만드는 검색 기능
    User* findByName(const std::string& name);

    void loadFromFile(const std::string& filename) override;//프로그램 시작시 CSV파일에서 데이터를 로드한다.
    void saveToFile(const std::string& filename) const override;//프로그램 종료시 데이터를 CSV파일에 저장한다.
    //이 함수는 저장만 하고 UserManager내부 값을 바꾸지 않으므로 const를 씀

    const std::vector<User>& getAllUsers() const; 
    //9번 유사도 계산: 전체 사용자를 한 명씩 비교하려면 전체 리스트를 받아올 수 있어야 한다.

    int size() const override;
};