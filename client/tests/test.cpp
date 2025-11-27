#include <gtest/gtest.h>

#include "client.h"

TEST(TestClientClass, Subtest_1) {
    int clientId = 123;
    std::string name = "Arthur";

    std::unique_ptr<Client> client = std::make_unique<Client>(clientId, name);

    EXPECT_EQ(client->GetId(), clientId);
    EXPECT_EQ(client->GetName(), name);
    EXPECT_EQ(client->GetRentedBookList().empty(), true);

    //

    int bookId1 = 10;
    std::string bookName1 = "Yellow1";
    std::string authorName1 = "SomeoneName1";
    int bookId2 = 13;
    std::string bookName2 = "Yellow2";
    std::string authorName2 = "SomeoneName2";
    std::shared_ptr<Book> book1 = std::make_shared<Book>(bookId1, bookName1, authorName1);
    std::shared_ptr<Book> book2 = std::make_shared<Book>(bookId2, bookName2, authorName2);

    client->AddRentedBook(book1);
    client->AddRentedBook(book2);
    
    EXPECT_TRUE(client->IsRentingThisBook(*book1));
    EXPECT_TRUE(client->IsRentingThisBook(*book2));
    
    //

    client->RemoveRentedBook(*book1);
    EXPECT_FALSE(client->IsRentingThisBook(*book1));
    EXPECT_TRUE(client->IsRentingThisBook(*book2));
}

TEST(TestClientClass, Subtest_2) {
    int clientId = 123;
    std::string name = "SomeoneName";
    
    std::unique_ptr<Client> client = std::make_unique<Client>(clientId, name);
    
    int bookId1 = 10;
    std::string bookName1 = "Yellow1";
    std::string authorName1 = "SomeoneName1";
    int bookId2 = 13;
    std::string bookName2 = "Yellow2";
    std::string authorName2 = "SomeoneName2";
    std::shared_ptr<Book> book1 = std::make_shared<Book>(bookId1, bookName1, authorName1);
    std::shared_ptr<Book> book2 = std::make_shared<Book>(bookId2, bookName2, authorName2);

    std::unordered_map<int, std::shared_ptr<const Book>> bookList;
    bookList[bookId1] = book1;
    bookList[bookId2] = book2;

    client->AddRentedBook(book1);
    client->AddRentedBook(book2);

    nlohmann::json j = ClientSerializer::ToJson(*client);

    std::unique_ptr<Client> sameClient = std::make_unique<Client>(ClientSerializer::FromJson(j, bookList));  

    EXPECT_EQ(client->GetId(), sameClient->GetId());
    EXPECT_EQ(client->GetName(), sameClient->GetName());
    EXPECT_TRUE(client->IsRentingThisBook(*book1));
    EXPECT_TRUE(client->IsRentingThisBook(*book2));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
