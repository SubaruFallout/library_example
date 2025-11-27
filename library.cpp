#include "library.h"

#define METHOD_FAILED false
#define METHOD_SUCCESS true

#define LIBRARY_BOOK_LIST_JSON_FIELD_NAME "bookList"
#define LIBRARY_RENTED_BOOK_LIST_JSON_FIELD_NAME "rentedBookList"
#define LIBRARY_CLIENT_LIST_JSON_FIELD_NAME "clientList"
#define LIBRARY_RELEASED_BOOK_IDS_JSON_FIELD_NAME "releasedBookIds"
#define LIBRARY_RELEASED_CLIENT_IDS_JSON_FIELD_NAME "releasedClientIds"
#define LIBRARY_LARGEST_CLIENT_ID_JSON_FIELD_NAME "largestClientId"
#define LIBRARY_LARGEST_BOOK_ID_JSON_FIELD_NAME "largestBookId"

std::shared_ptr<const Book> Library::AddNewBook(const std::string &bookName, const std::string &authorName) {
  int currentBookId;
  if (!releasedBookIds_.empty()) {
    currentBookId = releasedBookIds_.top();
    releasedBookIds_.pop();
  } else {
    currentBookId = largestBookId_;
    largestBookId_++;
  }

  std::shared_ptr<Book> newBook = std::make_shared<Book>(currentBookId, bookName, authorName);
  bookList_.emplace(currentBookId, newBook);
  return newBook;
}

std::shared_ptr<const Client> Library::AddNewClient(const std::string &clientName) {
  int currentClientId;
  if (!releasedClientIds_.empty()) {
    currentClientId = releasedClientIds_.top();
    releasedClientIds_.pop();
  } else {
    currentClientId = largestClientId_;
    largestClientId_++;
  }
  
  std::shared_ptr<Client> newClient = std::make_shared<Client>(currentClientId, clientName);
  clientList_.emplace(currentClientId, newClient);
  return newClient;
}

std::vector<std::shared_ptr<const Book>> Library::FindBookByName(const std::string &bookName) const {
  std::vector<std::shared_ptr<const Book>> foundBooks;
  for (const auto &[bookId, book] : bookList_) {
    if (book->GetName() == bookName) {
      foundBooks.push_back(book);
    }
  }
  return foundBooks;
}

std::shared_ptr<const Client> Library::GetClientById(int clientId) const {
  if (clientList_.find(clientId) != clientList_.end()) {
    return clientList_.at(clientId);
  }
  return std::shared_ptr<const Client>();
}

bool Library::RentBookToClient(const Client& client, std::shared_ptr<const Book> book) {
  // Check if client exists
  if (clientList_.find(client.GetId()) == clientList_.end()) {
    return METHOD_FAILED;
  }
  // Check if book exists
  if (bookList_.find(book->GetId()) == bookList_.end()) {
    return METHOD_FAILED;
  }

  // Check if book already rented
  if (rentedBookIdList_.find(book->GetId()) != rentedBookIdList_.end()) {
    return METHOD_FAILED;
  }

  clientList_[client.GetId()]->AddRentedBook(book);

  rentedBookIdList_.insert(book->GetId());

  return METHOD_SUCCESS;
}

bool Library::ReturnBookFromClient(const Client& client, std::shared_ptr<const Book> book) {
  // Check if client exists
  if (clientList_.find(client.GetId()) == clientList_.end()) {
    return METHOD_FAILED;
  }
  // Check if book exists
  if (bookList_.find(book->GetId()) == bookList_.end()) {
    return METHOD_FAILED;
  }

  // Check if book not rented
  if (rentedBookIdList_.find(book->GetId()) == rentedBookIdList_.end()) {
    return METHOD_FAILED;
  }

  // Check if this client not having this book
  if (!client.IsRentingThisBook(*book)) {
    return METHOD_FAILED;
  }

  clientList_[client.GetId()]->RemoveRentedBook(*book);
  rentedBookIdList_.erase(book->GetId());
  return METHOD_SUCCESS;
}

nlohmann::json LibrarySerializer::ToJson(const Library& library) {
    nlohmann::json j;
    
    for (const auto& [bookId, book] : library.bookList_) {
      j[LIBRARY_BOOK_LIST_JSON_FIELD_NAME].push_back(BookSerializer::ToJson(*book));
    }
    j[LIBRARY_RENTED_BOOK_LIST_JSON_FIELD_NAME] = library.rentedBookIdList_;

    for (const auto& [clientId, client] : library.clientList_) {
      j[LIBRARY_CLIENT_LIST_JSON_FIELD_NAME].push_back(ClientSerializer::ToJson(*client));
    }

    j[LIBRARY_LARGEST_BOOK_ID_JSON_FIELD_NAME] = library.largestBookId_;
    j[LIBRARY_LARGEST_CLIENT_ID_JSON_FIELD_NAME] = library.largestClientId_;

    std::stack<int> tmp_releasedBookIds;
    while (!library.releasedBookIds_.empty()) {
      j[LIBRARY_RELEASED_BOOK_IDS_JSON_FIELD_NAME].push_back(library.releasedBookIds_.top());
      tmp_releasedBookIds.push(library.releasedBookIds_.top());
      library.releasedBookIds_.pop();
    }
    library.releasedBookIds_ = std::move(tmp_releasedBookIds);

    std::stack<int> tmp_releasedClientIds;
    while (!library.releasedClientIds_.empty()) {
      j[LIBRARY_RELEASED_CLIENT_IDS_JSON_FIELD_NAME].push_back(library.releasedClientIds_.top());
      tmp_releasedClientIds.push(library.releasedClientIds_.top());
      library.releasedClientIds_.pop();
    }
    library.releasedClientIds_ = std::move(tmp_releasedClientIds);

    return j;
}

Library LibrarySerializer::FromJson(const nlohmann::json& j) {
  Library library;

  if (j.contains(LIBRARY_BOOK_LIST_JSON_FIELD_NAME)) {
    for (auto& j_book : j[LIBRARY_BOOK_LIST_JSON_FIELD_NAME]) {
      std::shared_ptr<Book> book = std::make_shared<Book>(BookSerializer::FromJson(j_book));
      library.bookList_[book->GetId()] = book;
    }
  }
  library.rentedBookIdList_ = j[LIBRARY_RENTED_BOOK_LIST_JSON_FIELD_NAME].get<std::unordered_set<int>>();

  if (j.contains(LIBRARY_CLIENT_LIST_JSON_FIELD_NAME)) {
    for (const auto& j_client : j[LIBRARY_CLIENT_LIST_JSON_FIELD_NAME]) {
        std::shared_ptr<Client> client = std::make_shared<Client>(ClientSerializer::FromJson(j_client, library.bookList_));
        library.clientList_[client->GetId()] = client;
    }
  }

  library.largestBookId_ = j[LIBRARY_LARGEST_BOOK_ID_JSON_FIELD_NAME].get<int>();
  library.largestClientId_ = j[LIBRARY_LARGEST_CLIENT_ID_JSON_FIELD_NAME].get<int>();

  if (j.contains(LIBRARY_RELEASED_BOOK_IDS_JSON_FIELD_NAME)) {
    for (const auto& j_book_id : j[LIBRARY_RELEASED_BOOK_IDS_JSON_FIELD_NAME]) {
      library.releasedBookIds_.push(j_book_id.get<int>());
    }
  }
  if (j.contains(LIBRARY_RELEASED_CLIENT_IDS_JSON_FIELD_NAME)) {
    for (const auto& j_client_id : j[LIBRARY_RELEASED_CLIENT_IDS_JSON_FIELD_NAME]) {
      library.releasedClientIds_.push(j_client_id.get<int>());
    }
  }

  return library;
}
