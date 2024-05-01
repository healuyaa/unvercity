#include <iostream>

class ParkingSystem {
public:
    ParkingSystem(int big, int medium, int small) {
        this->big = big;
        this->medium = medium;
        this->small = small;
    }
    
    bool addCar(int carType) {
        if (carType == 1 && this->big != 0)
        {
            this->big--;;
            return true;
        }
        if (carType == 2 && this->medium != 0)
        {
            this->medium--;
            return true;
        }
        if (carType == 3 && this->small != 0)
        {
            this->small--;
            return true;
        }
        return false;                
    }
    private: 
    int big, small, medium;
};

int main() {
    ParkingSystem* parkingSystem = new ParkingSystem(1, 1, 0);
    std::cout << parkingSystem->addCar(1) << "\n";
    std::cout << parkingSystem->addCar(2) << "\n";
    std::cout << parkingSystem->addCar(3) << "\n";
    std::cout << parkingSystem->addCar(1) << "\n";

}