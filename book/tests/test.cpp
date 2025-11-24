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
    EXPECT_EQ(book->IsAtClient(), false);

    //

    int clientId = 123;
    book->UpdateOwnership(std::make_optional<int>(clientId));
    EXPECT_EQ(book->IsAtClient(), true);
    EXPECT_EQ(book->GetClientId(), clientId);
    
    //

    book->UpdateOwnership(std::nullopt);
    EXPECT_EQ(book->IsAtClient(), false);
}

TEST(TestBookClass, Subtest_2) {
    int bookId = 10;
    std::string name = "Yellow";
    std::string authorName = "SomeoneName";
    int clientId = 123;

    std::unique_ptr<Book> book = std::make_unique<Book>(bookId, name, authorName);
    book->UpdateOwnership(clientId);

    json j = book->ToJson();

    std::unique_ptr<Book> sameBook = std::make_unique<Book>(j); 

    EXPECT_EQ(book->GetId(), sameBook->GetId());
    EXPECT_EQ(book->GetName(), sameBook->GetName());
    EXPECT_EQ(book->GetAuthorName(), sameBook->GetAuthorName());
    EXPECT_EQ(book->IsAtClient(), sameBook->IsAtClient());
    EXPECT_EQ(book->GetClientId(), sameBook->GetClientId());
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
