#pragma once

#include <memory>
#include <stack>
#include <unordered_map>

#include "nlohmann/json.hpp"

#include "book/book.h"
#include "client/client.h"

class Library {
  public:
    friend class LibrarySerializer;

    Library() = default;

    std::shared_ptr<const Book> AddNewBook(const std::string& bookName, const std::string& authorName);
    bool RemoveBook(const Book& book);
    std::shared_ptr<const Client> AddNewClient(const std::string& clientName);
    bool RemoveClient(const Client& client);

    std::vector<std::shared_ptr<const Book>> FindBookByName(const std::string& bookName) const;
    std::shared_ptr<const Client> GetClientById(int clientId) const;

    bool RentBookToClient(const Client& client, std::shared_ptr<const Book> book);
    bool ReturnBookFromClient(const Client& client, std::shared_ptr<const Book> book);

  private:
    std::unordered_map<int, std::shared_ptr<Book>> bookList_;
    std::unordered_set<int> rentedBookIdList_;
    std::unordered_map<int, std::shared_ptr<Client>> clientList_;

    int largestBookId_ = 0;
    int largestClientId_ = 0;
    mutable std::stack<int> releasedBookIds_;
    mutable std::stack<int> releasedClientIds_;
};

class LibrarySerializer {
  public:
    LibrarySerializer() = delete;
    
    static nlohmann::json ToJson(const Library& library);
    
    static Library FromJson(const nlohmann::json& j);

};
