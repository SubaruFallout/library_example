#pragma once

#include <optional>
#include <string>

#include "nlohmann/json.hpp"

class Book {
  public:
    friend class BookSerializer;

    Book() = default;

    Book(int id, const std::string& name, const std::string& authorName) :
        id_(id), name_(name), authorName_(authorName) {}

    int GetId() const;

    const std::string& GetName() const;

    const std::string& GetAuthorName() const;

  private:
    int id_;
    std::string authorName_;
    std::string name_;
};

class BookSerializer {
  public:
    BookSerializer() = delete;
    
    static nlohmann::json ToJson(const Book& book);
    
    static Book FromJson(const nlohmann::json& j);

};
