#include <gtest/gtest.h>

#include "client.h"

TEST(TestClientClass, Subtest_1) {
    int clientId = 123;
    std::string name = "SomeoneName";

    std::unique_ptr<Client> client = std::make_unique<Client>(clientId, name);

    EXPECT_EQ(client->GetId(), clientId);
    EXPECT_EQ(client->GetName(), name);
    EXPECT_EQ(client->GetRentedBookIdList().empty(), true);

    //

    int bookId1 = 10;
    int bookId2 = 13;
    client->AddRentedBookId(bookId1);
    client->AddRentedBookId(bookId2);
    {
        auto& rentedBookIdList = client->GetRentedBookIdList();
        EXPECT_EQ(rentedBookIdList.size(), 2);
        EXPECT_TRUE(rentedBookIdList.find(bookId1) != rentedBookIdList.end());
        EXPECT_TRUE(rentedBookIdList.find(bookId2) != rentedBookIdList.end());
    }
    
    //

    client->RemoveRentedBookId(bookId1);
    {
        auto& rentedBookIdList = client->GetRentedBookIdList();
        EXPECT_EQ(rentedBookIdList.size(), 1);
        EXPECT_TRUE(rentedBookIdList.find(bookId1) == rentedBookIdList.end());
        EXPECT_TRUE(rentedBookIdList.find(bookId2) != rentedBookIdList.end());
    }
}

TEST(TestClientClass, Subtest_2) {
    int clientId = 123;
    std::string name = "SomeoneName";
    int bookId1 = 10;
    int bookId2 = 13;
    std::unordered_set<int> rentedBookIdList = {bookId1, bookId2};

    std::unique_ptr<Client> client = std::make_unique<Client>(clientId, name, rentedBookIdList);

    EXPECT_EQ(client->GetId(), clientId);
    EXPECT_EQ(client->GetName(), name);
    {
        auto& rentedBookIdList = client->GetRentedBookIdList();
        EXPECT_EQ(rentedBookIdList.size(), 2);
        EXPECT_TRUE(rentedBookIdList.find(bookId1) != rentedBookIdList.end());
        EXPECT_TRUE(rentedBookIdList.find(bookId2) != rentedBookIdList.end());
    }
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
