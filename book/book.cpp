#include "book.h"

int Book::GetId() const {
    return id_;
}

const std::string& Book::GetName() const {
    return name_;
}

const std::string& Book::GetAuthorName() const {
    return authorName_;
}

bool Book::IsAtClient() const {
    return clientId_.has_value();
}

int Book::GetClientId() const {
    return *clientId_;
}

void Book::UpdateOwnership(std::optional<int> clientId) {
    clientId_ = clientId;
}
