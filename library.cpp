#include "library.h"

void Library::AddNewBook(const std::string& bookName, const std::string& authorName) {
    bookList_->emplace(lastBookId_, std::make_shared<Book>(lastBookId_, bookName, authorName));
    lastBookId_++;
}

void Library::AddNewClient(const std::string& clientName) {
    clientList_->emplace(lastClientId_, std::make_shared<Client>(lastClientId_, clientName));
    lastClientId_++;
}

std::shared_ptr<Book> Library::GetBookById(int bookId) {
    return (*bookList_)[bookId];
    // return bookList_->at(bookId);
}
std::shared_ptr<Book> Library::GetBookByName(const std::string& bookName) {
    for (auto [bookId, book]: *bookList_) {
        if (book->GetName() == bookName) {
            return book;
        }
    }
    return std::make_shared<Book>();
}

std::shared_ptr<Client> Library::GetClientById(int clientId) {
    return (*clientList_)[clientId];
}

void Library::RentBookToClient(int clientId, int bookId) {
    if ((*bookList_)[bookId]->IsAtClient()) {
        return;
    }
    (*clientList_)[clientId]->AddRentedBookId(bookId);
    (*bookList_)[bookId]->UpdateOwnership(std::make_optional<int>(clientId));
}

void Library::ReturnBookFromClient(int clientId, int bookId) {
    (*clientList_)[clientId]->RemoveRentedBookId(bookId);
    (*bookList_)[bookId]->UpdateOwnership(std::nullopt);
}
