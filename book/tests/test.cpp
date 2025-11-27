#include <gtest/gtest.h>

#include "book.h"

TEST(TestBookClass, Subtest_1) {
    int bookId = 10;
    std::string name = "Yellow";
    std::string authorName = "SomeoneName";

    std::unique_ptr<Book> book = std::make_unique<Book>(bookId, name, authorName);

    EXPECT_EQ(book->GetId(), bookId);
    EXPECT_EQ(book->GetName(), name);
    EXPECT_EQ(book->GetAuthorName(), authorName);
}

TEST(TestBookClass, Subtest_2) {
    int bookId = 10;
    std::string name = "Yellow";
    std::string authorName = "SomeoneName";

    std::unique_ptr<Book> book = std::make_unique<Book>(bookId, name, authorName);

    nlohmann::json j = BookSerializer::ToJson(*book);

    std::unique_ptr<Book> sameBook = std::make_unique<Book>(BookSerializer::FromJson(j));

    EXPECT_EQ(book->GetId(), sameBook->GetId());
    EXPECT_EQ(book->GetName(), sameBook->GetName());
    EXPECT_EQ(book->GetAuthorName(), sameBook->GetAuthorName());
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
