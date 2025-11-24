#ifndef BOOK_H_
#define BOOK_H_

#include <optional>
#include <string>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Book {
  public:
    Book() = default;

    Book(int id, const std::string& name, const std::string& authorName) :
        id_(id), name_(name), authorName_(authorName) {}
    
    Book(const json& j);

    int GetId() const;

    const std::string& GetName() const;

    const std::string& GetAuthorName() const;

    bool IsAtClient() const;

    int GetClientId() const;

    void UpdateOwnership(std::optional<int> clientId);

    json ToJson() const;

  private:
    int id_;
    std::string authorName_;
    std::string name_;
    std::optional<int> clientId_;
};

#endif  // BOOK_H_
