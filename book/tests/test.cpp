#include <gtest/gtest.h>

#include "book.h"

TEST(TestBookClass, Subtest_1) {
    int bookId = 10;
    std::string name = "Yellow";
    std::string authorName = "SomeoneName";

    Book book(bookId, name, authorName);

    EXPECT_EQ(book.GetId(), bookId);
    EXPECT_EQ(book.GetName(), name);
    EXPECT_EQ(book.GetAuthorName(), authorName);
    EXPECT_EQ(book.IsAtClient(), false);

    //

    int clientId = 123;
    book.UpdateOwnership(std::make_optional<int>(clientId));
    EXPECT_EQ(book.IsAtClient(), true);
    EXPECT_EQ(book.GetClientId(), clientId);
    
    //

    book.UpdateOwnership(std::nullopt);
    EXPECT_EQ(book.IsAtClient(), false);
}

TEST(TestGroupName, Subtest_2) {
    int bookId = 10;
    std::string name = "Yellow";
    std::string authorName = "SomeoneName";
    int clientId = 123;

    Book book(bookId, name, authorName, std::make_optional<int>(123));

    EXPECT_EQ(book.GetId(), bookId);
    EXPECT_EQ(book.GetName(), name);
    EXPECT_EQ(book.GetAuthorName(), authorName);
    EXPECT_EQ(book.IsAtClient(), true);
    EXPECT_EQ(book.GetClientId(), clientId);
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}