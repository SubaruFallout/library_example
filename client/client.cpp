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
