#include <iostream>
#include <string>

class Msg {
public: 
    Msg(std::string msg) : msg(msg) {}

    virtual std::string Get_msg() {
        return msg;
    }
private:
    std::string msg;
};

class BraketMsg : public Msg {
public: 
    BraketMsg(std::string msg) : Msg(msg) {}
    std::string Get_msg() override {
        return "(" + ::Msg::Get_msg() + ")";
    }
};

class Printer {
public:
    void Print(Msg *msg) {
        std::cout << msg->Get_msg() << std::endl;
    }
};

int main() {
    BraketMsg msg("what's up!");
    Printer print;
    print.Print(&msg);
}