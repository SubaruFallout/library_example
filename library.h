#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <memory>
#include <unordered_map>

#include "client/client.h"
#include "book/book.h"

class Library {
  public:
    Library() = default;

    void AddNewBook(const std::string& bookName, const std::string& authorName);
    void AddNewClient(const std::string& clientName);

    const Book& GetBookById(int bookId);
    const Book& GetBookByName(const std::string& bookName);

    const Client& GetClientById(int clientId);

    void RentBookToClient(int clientId, int bookId);

    void ReturnBookFromClient(int clientId, int bookId);

    const std::unordered_map<int, Book>& GetBookList();
    
    const std::unordered_map<int, Client>& GetClientList();

  private:
    std::unordered_map<int, Book> bookList_;
    std::unordered_map<int, Client> clientList_;

    int lastBookId_;
    int lastClientId_;
};

#endif  // LIBRARY_H_
