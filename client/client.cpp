#include "client.h"

int Client::GetId() {
    return id_;
}

const std::string& Client::GetName() {
    return name_;
}

const std::unordered_set<int>& Client::GetRentedBookIdList() {
    return rentedBookIdList_;
}

void Client::AddRentedBookId (int bookId) {
    rentedBookIdList_.insert(bookId);
}

void Client::RemoveRentedBookId (int bookId) {
    rentedBookIdList_.erase(bookId);
}
