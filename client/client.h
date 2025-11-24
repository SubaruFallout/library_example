#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <unordered_set>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Client {
  public:
    Client() = default;

    Client(int id, const std::string& name) :
        id_(id), name_(name) {}

    Client(const json& j);

    int GetId() const;

    const std::string& GetName() const;

    const std::unordered_set<int>& GetRentedBookIdList() const;

    void AddRentedBookId (int bookId);

    void RemoveRentedBookId (int bookId);

    json ToJson() const;

  private:
    int id_;
    std::string name_;
    std::unordered_set<int> rentedBookIdList_;
};

#endif  // CLIENT_H_
