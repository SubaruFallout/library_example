#include <string>
#include <unordered_set>

class Client {
  public:
    Client(int id, const std::string& name) :
        id_(id), name_(name) {}

    Client(int id, const std::string& name, const std::unordered_set<int>& rentedBookIdList):
        // id_(id), name_(name), rentedBookIdList_(rentedBookIdList_) {
        id_(id), name_(name) {
          rentedBookIdList_ = rentedBookIdList;
        }

    int GetId();

    const std::string& GetName();

    const std::unordered_set<int>& GetRentedBookIdList();

    void AddRentedBookId (int bookId);

    void RemoveRentedBookId (int bookId);

  private:
    int id_;
    std::string name_;
    std::unordered_set<int> rentedBookIdList_;
};
