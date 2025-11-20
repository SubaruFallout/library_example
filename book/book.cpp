#include "book.h"

int Book::GetId() {
    return id_;
}

const std::string& Book::GetName() {
    return name_;
}

const std::string& Book::GetAuthorName() {
    return authorName_;
}

bool Book::IsAtClient() {
    return clientId_.has_value();
}

int Book::GetClientId() {
    return *clientId_;
}

void Book::UpdateOwnership(std::optional<int> clientId) {
    clientId_ = clientId;
}
