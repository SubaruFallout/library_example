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

Book::Book(const json& j) {
    id_ = j["id"].get<int>();
    authorName_ = j["authorName"].get<std::string>();
    name_ = j["name"].get<std::string>();
    if (j.contains("clientId")) {
        clientId_ = std::make_optional<int>(j["clientId"].get<int>());
    }
}

json Book::ToJson() const {
    json j;
    j["id"] = id_;
    j["authorName"] = authorName_;
    j["name"] = name_;
    if (clientId_.has_value()) {
        j["clientId"] = *clientId_;
    }
    return j;
}
