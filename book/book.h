#include <optional>
#include <string>

class Book {
  public:
    Book (int id, const std::string& name, const std::string& authorName) :
        id_(id), name_(name), authorName_(authorName) {}
    
    Book (int id, const std::string& name, const std::string& authorName, std::optional<int> clientId) :
        id_(id), name_(name), authorName_(authorName), clientId_(clientId) {}

    int GetId();

    const std::string& GetName();

    const std::string& GetAuthorName();

    bool IsAtClient();

    int GetClientId();

    void UpdateOwnership(std::optional<int> clientId);

  private:
    int id_;
    std::string authorName_;
    std::string name_;
    std::optional<int> clientId_;
};
