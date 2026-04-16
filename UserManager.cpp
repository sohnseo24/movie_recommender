#include "UserManager.h"
#include <iostream>

// 5번: 사용자 추가
void UserManager::addUser(const User& user) {
    users.push_back(user);
}

// 6번: 전체 출력
void UserManager::printAllUsers() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다." << std::endl;
        return;
    }
    for (const auto& u : users) {
        u.display(); 
    }
}

// 반복문을 이용한 사용자 이름 검색
User* UserManager::findByName(const std::string& name) {
    // 벡터를 처음부터 끝까지 돌면서 이름을 비교
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getName() == name) {
            return &users[i]; // 찾으면 해당 사용자의 주소 즉 포인터 반환
        }
    }
    return nullptr; // 끝까지 못 찾으면 없다는 뜻으로 nullptr 반환
}