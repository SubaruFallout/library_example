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

    std::unique_ptr<Client> client = std::make_unique<Client>(clientId, name);
    client->AddRentedBookId(bookId1);
    client->AddRentedBookId(bookId2);

    json j = client->ToJson();

    std::unique_ptr<Client> sameClient = std::make_unique<Client>(j);  

    EXPECT_EQ(client->GetId(), sameClient->GetId());
    EXPECT_EQ(client->GetName(), sameClient->GetName());
    {
        auto& rentedBookIdList = client->GetRentedBookIdList();
        auto& sameRentedBookIdList = sameClient->GetRentedBookIdList();
        EXPECT_EQ(rentedBookIdList.size(), sameRentedBookIdList.size());
        EXPECT_TRUE(rentedBookIdList.find(bookId1) != rentedBookIdList.end());
        EXPECT_TRUE(rentedBookIdList.find(bookId2) != rentedBookIdList.end());

        EXPECT_TRUE(sameRentedBookIdList.find(bookId1) != sameRentedBookIdList.end());
        EXPECT_TRUE(sameRentedBookIdList.find(bookId2) != sameRentedBookIdList.end());
    }

    // std::cout << std::setw(4) << j << std::endl;
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
