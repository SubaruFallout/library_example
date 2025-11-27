#include <gtest/gtest.h>

#include "book/book.h"
#include "client/client.h"
#include "library.h"

TEST(TestLibraryClass, Subtest_1) {
    std::unique_ptr<Library> library = std::make_unique<Library>();

    std::string bookName = "Yellow";
    std::string authorName = "SomeoneName";
    
    auto book = library->AddNewBook(bookName, authorName);

    {
        auto sameBook = library->FindBookByName(bookName);

        EXPECT_EQ(sameBook.size(), 1);
        EXPECT_EQ(book, sameBook[0]);
    }

    std::string clientName = "ClientName";

    auto client = library->AddNewClient(clientName);

    {
        auto sameClient = library->GetClientById(client->GetId());

        EXPECT_EQ(client, sameClient);
    }
}

TEST(TestLibraryClass, Subtest_2) {
    std::unique_ptr<Library> library = std::make_unique<Library>();

    std::string bookName1 = "Yellow";
    std::string bookName2 = "Red";
    std::string bookName3 = "Blue";
    std::string authorName = "SomeoneName";

    auto book1 = library->AddNewBook(bookName1, authorName);
    auto book2 = library->AddNewBook(bookName2, authorName);
    auto book3 = library->AddNewBook(bookName3, authorName);

    std::string clientName1 = "John";
    std::string clientName2 = "Dave";

    auto client1 = library->AddNewClient(clientName1);
    auto client2 = library->AddNewClient(clientName2);


    EXPECT_TRUE(library->RentBookToClient(*client1, book3)); // John <- Blue
    EXPECT_FALSE(library->RentBookToClient(*client2, book3)); // Dave <- Blue
    EXPECT_TRUE(library->RentBookToClient(*client2, book2)); // Dave <- Red
    EXPECT_TRUE(library->RentBookToClient(*client2, book1)); // Dave <- Yellow

    // Check Client status
    EXPECT_TRUE(client1->IsRentingThisBook(*book3));
    EXPECT_TRUE(client2->IsRentingThisBook(*book2));
    EXPECT_TRUE(client2->IsRentingThisBook(*book1));

    // return books and rerent

    EXPECT_TRUE(library->ReturnBookFromClient(*client1, book3));
    EXPECT_TRUE(library->ReturnBookFromClient(*client2, book1));
    EXPECT_TRUE(library->RentBookToClient(*client1, book1));

    // Check Client status
    // Check Client status
    EXPECT_TRUE(client1->IsRentingThisBook(*book1));
    EXPECT_TRUE(client2->IsRentingThisBook(*book2));
}

TEST(TestLibraryClass, Subtest_3) {
    std::unique_ptr<Library> library = std::make_unique<Library>();

    std::string bookName1 = "Yellow";
    std::string bookName2 = "Red";
    std::string bookName3 = "Blue";
    std::string authorName = "SomeoneName";

    auto book1 = library->AddNewBook(bookName1, authorName);
    auto book2 = library->AddNewBook(bookName2, authorName);
    auto book3 = library->AddNewBook(bookName3, authorName);

    std::string clientName1 = "John";
    std::string clientName2 = "Dave";

    auto client1 = library->AddNewClient(clientName1);
    auto client2 = library->AddNewClient(clientName2);


    EXPECT_TRUE(library->RentBookToClient(*client1, book3)); // John <- Blue
    EXPECT_TRUE(library->RentBookToClient(*client2, book2)); // Dave <- Red
    EXPECT_TRUE(library->RentBookToClient(*client2, book1)); // Dave <- Yellow

    nlohmann::json j = LibrarySerializer::ToJson(*library);

    std::unique_ptr<Library> sameLibrary = std::make_unique<Library>(LibrarySerializer::FromJson(j));

    // // Check books
    // EXPECT_EQ(sameLibrary->FindBookByName(book1->GetName()).size(), 1);
    // EXPECT_EQ(sameLibrary->FindBookByName(book2->GetName()).size(), 1);
    // EXPECT_EQ(sameLibrary->FindBookByName(book3->GetName()).size(), 1);

    // // Check Client status
    // EXPECT_TRUE(sameLibrary->GetClientById(client1->GetId())->IsRentingThisBook(*book3));
    // EXPECT_TRUE(sameLibrary->GetClientById(client2->GetId())->IsRentingThisBook(*book2));
    // EXPECT_TRUE(sameLibrary->GetClientById(client2->GetId())->IsRentingThisBook(*book1));
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
