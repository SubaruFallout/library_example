#include "book.h"

#define BOOK_AUTHOR_NAME_JSON_FIELD_NAME "authorName"
#define BOOK_NAME_JSON_FIELD_NAME "name"
#define BOOK_ID_JSON_FIELD_NAME "id"

int Book::GetId() const {
  return id_;
}

const std::string& Book::GetName() const {
  return name_;
}

const std::string& Book::GetAuthorName() const {
  return authorName_;
}

nlohmann::json BookSerializer::ToJson(const Book& book) {
  nlohmann::json j;
  j[BOOK_ID_JSON_FIELD_NAME] = book.id_;
  j[BOOK_AUTHOR_NAME_JSON_FIELD_NAME] = book.authorName_;
  j[BOOK_NAME_JSON_FIELD_NAME] = book.name_;
  return j;
}

Book BookSerializer::FromJson(const nlohmann::json& j) {
  Book book;
  book.id_ = j[BOOK_ID_JSON_FIELD_NAME].get<int>();
  book.authorName_ = j[BOOK_AUTHOR_NAME_JSON_FIELD_NAME].get<std::string>();
  book.name_ = j[BOOK_NAME_JSON_FIELD_NAME].get<std::string>();
  return book;
}
