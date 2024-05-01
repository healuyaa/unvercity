#include <iostream>

class Ibicycle {
    public: 
    void virtual TwistTheWheel() = 0;
    void virtual Ride() = 0;
};

class SimpleBicycle : public Ibicycle {
    public: 
    void Ride() override {
        std::cout << "Simple Ride";
    }
    void TwistTheWheel() override {
        std::cout << "Simple Twist";
    }
};

class SportBicycle : public Ibicycle {
    public: 
    void Ride() override {
        std::cout << "Sport Ride";
    }
    void TwistTheWheel() override {
        std::cout << "Sport Twist";
    }
};

class Human {
    public:
    void RideOn(Ibicycle& bicycle) {
        std::cout << "start" << std::endl;
        bicycle.TwistTheWheel();
        std::cout << "end" << std::endl;
        bicycle.Ride();
    }
};

int main() {

    SimpleBicycle sb;
    SportBicycle sp;

    Human h;
    h.RideOn(sp);
}