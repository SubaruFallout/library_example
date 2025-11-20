#include <memory>
#include <unordered_map>

#include "client/client.h"
#include "book/book.h"

class Library {
  public:
    Library() = default;

    void AddNewBook(const std::string& bookName, const std::string& authorName);
    void AddNewClient(const std::string& clientName);

    std::shared_ptr<Book> GetBookById(int bookId);
    std::shared_ptr<Book> GetBookByName(const std::string& bookName);

    std::shared_ptr<Client> GetClientById(int clientId);

    void RentBookToClient(int clientId, int bookId);

    void ReturnBookFromClient(int clientId, int bookId);

  private:
    std::shared_ptr<std::unordered_map<int, std::shared_ptr<Book>>> bookList_;
    std::shared_ptr<std::unordered_map<int, std::shared_ptr<Client>>> clientList_;

    int lastBookId_;
    int lastClientId_;
};
