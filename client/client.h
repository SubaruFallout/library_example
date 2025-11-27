#pragma once

#include <string>
#include <unordered_set>

#include "nlohmann/json.hpp"

#include "../book/book.h" // Change to normal path

class Client {
  public:
    friend class ClientSerializer;

    Client() = default;

    Client(int id, const std::string& name) :
        id_(id), name_(name) {}

    int GetId() const;

    const std::string& GetName() const;

    std::vector<std::shared_ptr<const Book>> GetRentedBookList() const;

    bool IsRentingThisBook(const Book& book) const;

    void AddRentedBook(std::shared_ptr<const Book> book);

    void RemoveRentedBook(const Book& book);

  private:
    int id_;
    std::string name_;
    std::unordered_map<int, std::shared_ptr<const Book>> rentedBookList_;
};

class ClientSerializer {
  public:
    ClientSerializer() = delete;
    
    static nlohmann::json ToJson(const Client& client);
    
    static Client FromJson(const nlohmann::json& j, 
                           const std::unordered_map<int, std::shared_ptr<Book>>& bookList);
};
