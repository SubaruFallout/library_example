#include "library.h"
#include <iostream>

void Library::AddNewBook(const std::string& bookName, const std::string& authorName) {
    bookList_.emplace(lastBookId_, Book(lastBookId_, bookName, authorName));
    lastBookId_++;
}

void Library::AddNewClient(const std::string& clientName) {
    clientList_.emplace(lastClientId_, Client(lastClientId_, clientName));
    lastClientId_++;
}

const Book& Library::GetBookById(int bookId) {
    return bookList_[bookId];
}
const Book& Library::GetBookByName(const std::string& bookName) {
    for (auto& [bookId, book]: bookList_) {
        if (book.GetName() == bookName) {
            return book;
        }
    }
    return Book();  // TODO 
}

const Client& Library::GetClientById(int clientId) {
    return clientList_[clientId];
}

void Library::RentBookToClient(int clientId, int bookId) {
    if (bookList_[bookId].IsAtClient()) {
        return;
    }
    clientList_[clientId].AddRentedBookId(bookId);
    bookList_[bookId].UpdateOwnership(std::make_optional<int>(clientId));
}

void Library::ReturnBookFromClient(int clientId, int bookId) {
    clientList_[clientId].RemoveRentedBookId(bookId);
    bookList_[bookId].UpdateOwnership(std::nullopt);
}

const std::unordered_map<int, Book>& Library::GetBookList() {
    return bookList_;
}

const std::unordered_map<int, Client>& Library::GetClientList() {
    return clientList_;
}

Library::Library(const json& j) {
    lastBookId_ = j["lastBookId"].get<int>();
    lastClientId_ = j["lastClientId"].get<int>();
    for (auto& j_book : j["bookList"]) {
        Book book(j_book);
        bookList_[book.GetId()] = std::move(book);
    }

    for (auto& j_client : j["clientList"]) {
        Client client(j_client);
        clientList_[client.GetId()] = std::move(client);
    }
}

json Library::ToJson() {
    json j;
    j["lastBookId"] = lastBookId_;
    j["lastClientId"] = lastClientId_;
    for (auto& [bookId, book] : bookList_) {
        j["bookList"].push_back(book.ToJson());
    }

    for (auto& [clientId, client] : clientList_) {
        j["clientList"].push_back(client.ToJson());
    }

    return j;
}
