#include "client.h"

#define CLIENT_ID_JSON_FIELD_NAME "id"
#define CLIENT_NAME_JSON_FIELD_NAME "name"
#define CLIENT_RENTED_BOOK_ID_LIST "rentedBookIdList"

int Client::GetId() const {
  return id_;
}

const std::string& Client::GetName() const {
  return name_;
}

std::vector<std::shared_ptr<const Book>> Client::GetRentedBookList() const {
  std::vector<std::shared_ptr<const Book>> bookList;
  for (const auto& [bookId, book]: rentedBookList_) {
    bookList.push_back(book);
  }
  return bookList;
}

bool Client::IsRentingThisBook(const Book& book) const {
  return rentedBookList_.find(book.GetId()) != rentedBookList_.end();
}

void Client::AddRentedBook(std::shared_ptr<const Book> book) {
  rentedBookList_[book->GetId()] = book;
}

void Client::RemoveRentedBook(const Book& book) {
  rentedBookList_.erase(book.GetId());
}


nlohmann::json ClientSerializer::ToJson(const Client& client) {
  nlohmann::json j;
  j[CLIENT_ID_JSON_FIELD_NAME] = client.id_;
  j[CLIENT_NAME_JSON_FIELD_NAME] = client.name_;
  for (const auto& [bookId, book] : client.rentedBookList_) {
    j[CLIENT_RENTED_BOOK_ID_LIST].push_back(bookId);
  }
  return j;
}

Client ClientSerializer::FromJson(const nlohmann::json& j, 
                                  const std::unordered_map<int, std::shared_ptr<Book>>& bookList) {
  Client client;
  client.id_ = j[CLIENT_ID_JSON_FIELD_NAME].get<int>();
  client.name_ = j[CLIENT_NAME_JSON_FIELD_NAME].get<std::string>();
  if (j.contains(CLIENT_RENTED_BOOK_ID_LIST)) {
    for (const auto& rentedBookId: j[CLIENT_RENTED_BOOK_ID_LIST]) {
      client.rentedBookList_[rentedBookId] = bookList.at(rentedBookId);
    }
  }

  return client;
}