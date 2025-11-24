#include "client.h"

int Client::GetId() const {
    return id_;
}

const std::string& Client::GetName() const {
    return name_;
}

const std::unordered_set<int>& Client::GetRentedBookIdList() const {
    return rentedBookIdList_;
}

void Client::AddRentedBookId (int bookId) {
    rentedBookIdList_.insert(bookId);
}

void Client::RemoveRentedBookId (int bookId) {
    rentedBookIdList_.erase(bookId);
}

Client::Client (const json& j) {
    id_ = j["id"].get<int>();
    name_ = j["name"].get<std::string>();
    rentedBookIdList_ = j["rentedBookIdList"].get<std::unordered_set<int>>();
}

json Client::ToJson() const {
    json j;
    j["id"] = id_;
    j["name"] = name_;
    j["rentedBookIdList"] = rentedBookIdList_;
    return j;
}
