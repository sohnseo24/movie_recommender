#pragma once
#include <vector>
#include <string>
#include "User.h"

class UserManager {
private:
    std::vector<User> users; 

public:
    // 5번: 사용자 추가
    void addUser(const User& user);

    // 6번: 사용자 목록 출력
    void printAllUsers() const;

    // 7번 평점 입력을 위해 미리 만드는 검색 기능
    User* findByName(const std::string& name);
    
};