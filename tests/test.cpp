#include <gtest/gtest.h>

#include "book/book.h"
#include "client/client.h"
#include "library.h"

TEST(TestLibraryClass, Subtest_1) {
    std::unique_ptr<Library> library = std::make_unique<Library>();

    EXPECT_TRUE(library->GetBookList().empty());   
    EXPECT_TRUE(library->GetClientList().empty()); 

    std::string bookName = "Yellow";
    std::string authorName = "SomeoneName";
    
    library->AddNewBook(bookName, authorName);
    
    {
        auto& book = library->GetBookByName(bookName);

        EXPECT_EQ(book.GetId(), 0);
        EXPECT_EQ(book.GetName(), bookName);
        EXPECT_EQ(book.GetAuthorName(), authorName);
        EXPECT_EQ(book.IsAtClient(), false);
    }

    //

    {
        auto& book = library->GetBookById(0);

        EXPECT_EQ(book.GetId(), 0);
        EXPECT_EQ(book.GetName(), bookName);
        EXPECT_EQ(book.GetAuthorName(), authorName);
        EXPECT_EQ(book.IsAtClient(), false);
    }

    std::string clientName = "ClientName";

    library->AddNewClient(clientName);

    {
        auto& client = library->GetClientById(0);

        EXPECT_EQ(client.GetId(), 0);
        EXPECT_EQ(client.GetName(), clientName);
        EXPECT_EQ(client.GetRentedBookIdList().empty(), true);
    }
}

TEST(TestLibraryClass, Subtest_2) {
    std::unique_ptr<Library> library = std::make_unique<Library>();

    std::string bookName1 = "Yellow";
    std::string bookName2 = "Red";
    std::string bookName3 = "Blue";
    std::string authorName = "SomeoneName";

    library->AddNewBook(bookName1, authorName);
    library->AddNewBook(bookName2, authorName);
    library->AddNewBook(bookName3, authorName);

    std::string clientName1 = "John";
    std::string clientName2 = "Dave";

    library->AddNewClient(clientName1);
    library->AddNewClient(clientName2);


    library->RentBookToClient(0, 2); // John <- Blue
    library->RentBookToClient(1, 1); // Dave <- Red
    library->RentBookToClient(1, 0); // Dave <- Yellow

    // Check book status
    {
        auto& book = library->GetBookById(0);
        EXPECT_EQ(book.GetName(), bookName1);
        EXPECT_EQ(book.GetAuthorName(), authorName);
        EXPECT_EQ(book.IsAtClient(), true);
        EXPECT_EQ(book.GetClientId(), 1); // Dave
    }

    {
        auto& book = library->GetBookById(1);
        EXPECT_EQ(book.GetName(), bookName2);
        EXPECT_EQ(book.GetAuthorName(), authorName);
        EXPECT_EQ(book.IsAtClient(), true);
        EXPECT_EQ(book.GetClientId(), 1); // Dave
    }

    {
        auto& book = library->GetBookById(2);
        EXPECT_EQ(book.GetName(), bookName3);
        EXPECT_EQ(book.GetAuthorName(), authorName);
        EXPECT_EQ(book.IsAtClient(), true);
        EXPECT_EQ(book.GetClientId(), 0); // John
    }

    // Check Client status
    {
        auto& client = library->GetClientById(1);
        EXPECT_EQ(client.GetId(), 1);
        EXPECT_EQ(client.GetName(), clientName2);
        {
            auto& rentedBookIdList = client.GetRentedBookIdList();
            EXPECT_EQ(rentedBookIdList.size(), 2);
            EXPECT_TRUE(rentedBookIdList.find(0) != rentedBookIdList.end());
            EXPECT_TRUE(rentedBookIdList.find(1) != rentedBookIdList.end());
        }
    }

    {
        auto& client = library->GetClientById(0);
        EXPECT_EQ(client.GetId(), 0);
        EXPECT_EQ(client.GetName(), clientName1);
        {
            auto& rentedBookIdList = client.GetRentedBookIdList();
            EXPECT_EQ(rentedBookIdList.size(), 1);
            EXPECT_TRUE(rentedBookIdList.find(2) != rentedBookIdList.end());
        }
    }

    // return books and rerent

    library->ReturnBookFromClient(0, 2);
    library->ReturnBookFromClient(1, 0);
    library->RentBookToClient(0, 0);

    // Check book status
    {
        auto& book = library->GetBookById(0);
        EXPECT_EQ(book.IsAtClient(), true);
        EXPECT_EQ(book.GetClientId(), 0); // John
    }

    {
        auto& book = library->GetBookById(2);
        EXPECT_EQ(book.IsAtClient(), false);
    }

    // Check Client status
    {
        auto& client = library->GetClientById(1);
        {
            auto& rentedBookIdList = client.GetRentedBookIdList();
            EXPECT_EQ(rentedBookIdList.size(), 1);
            EXPECT_TRUE(rentedBookIdList.find(1) != rentedBookIdList.end());
        }
    }

    {
        auto& client = library->GetClientById(0);
        {
            auto& rentedBookIdList = client.GetRentedBookIdList();
            EXPECT_EQ(rentedBookIdList.size(), 1);
            EXPECT_TRUE(rentedBookIdList.find(0) != rentedBookIdList.end());
        }
    }
}

TEST(TestLibraryClass, Subtest_3) {
    std::unique_ptr<Library> library = std::make_unique<Library>();

    std::string bookName1 = "Yellow";
    std::string bookName2 = "Red";
    std::string bookName3 = "Blue";
    std::string authorName = "SomeoneName";

    library->AddNewBook(bookName1, authorName);
    library->AddNewBook(bookName2, authorName);
    library->AddNewBook(bookName3, authorName);

    std::string clientName1 = "John";
    std::string clientName2 = "Dave";

    library->AddNewClient(clientName1);
    library->AddNewClient(clientName2);


    library->RentBookToClient(0, 2); // John <- Blue
    library->RentBookToClient(1, 1); // Dave <- Red
    library->RentBookToClient(1, 0); // Dave <- Yellow

    json j = library->ToJson();

    std::unique_ptr<Library> sameLibrary = std::make_unique<Library>(j);

    {
        auto& bookList = library->GetBookList();
        auto& sameBookList = sameLibrary->GetBookList();
        EXPECT_EQ(bookList.size(), sameBookList.size());
        // TO DO
    }

    json j2 = sameLibrary->ToJson();
    std::cout << std::setw(4) << j2 << std::endl;
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
