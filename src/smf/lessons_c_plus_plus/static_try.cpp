#include <iostream>
#include <vector>
#include <string>

class Stranger {
    public: 
    Stranger(std::string name, std::string model, std::string color, int number) : name(name), model(model), color(color), number(number) {
        count++;
        id = count;
        std::cout << "Stranger car: " << count << std::endl;
    }
    Stranger() {}

    void initStr(std::string name, std::string model, std::string color, int number) {
        this->name = name;
        this->model = model;
        this->color = color;
        this->number = number;
        count++;
        id = count;
        std::cout << "Stranger car: " << count << std::endl;
    }

    static void count_quantity() {
        std::cout << count;
    }

    int get_id() {
        return id;
    }

    private:
    std::string name;
    std::string model;
    std::string color;
    int number;
    static int count;
    int id;
};
int Stranger::count = 0;

class Iniciator {
    public:
    Iniciator(std::string name, std::string model, std::string color, int number) : name(name), model(model), color(color), number(number){
        count++;
        id = count;
        std::cout << "Iniciator car: " << count << std::endl;
    }
    Iniciator() {}

    void initIni(std::string name, std::string model, std::string color, int number) {
        this->name = name;
        this->model = model;
        this->color = color;
        this->number = number;
        count++;
        id = count;
        std::cout << "Iniciator car: " << count << std::endl;
    }

    static void count_quantity() {
        std::cout << count;
    }

    int get_id() {
        return id;
    }

    private:
    std::string name;
    std::string model;
    std::string color;
    int number;
    static int count;
    int id;
};
int Iniciator::count = 0;

class Cars : public Stranger, public Iniciator {
    // Cars(std::string nameW, std::string model, std::string color, int number) : Stranger{nameW, model, color, number}, Iniciator{} {} 
    // Cars(std::string nameA, std::string model,std::string color, int number) : Stranger{}, Iniciator{nameA, model, color, number} {} 

    public:    
    Cars(std::string name, std::string model, std::string color, int number) : nameUndef(name), model(model), color(color), number(number) { 
        this->nameUndef = name;
        count++;
        id = count;
        std::cout << "Undefined car: " << count << std::endl;
    }
    Cars() {}

    static void count_quantity() {
        std::cout << count;
    }

    int get_id() {
        return id;
    }

    void is_car(std::string name, std::string model, std::string color, int number) {
        if (name == "Stranger")
        {
            Stranger::initStr(name, model, color, number);
        } else if (name == "Iniciator") {
            Iniciator::initIni(name, model, color, number);
        } else {
            Cars(name, model, color, number);
        }        
    }

    private: 
    std::string nameUndef;
    std::string model;
    std::string color;
    int number;
    static int count;
    int id;
};
int Cars::count = 0;

int main() {
    std::vector<Cars> cars(9);
    cars[0].is_car("Stranger", "11h3GG2G3ti", "black", 2367799);
    cars[1].is_car("Stranger", "12h3GG2G3ti", "yellow", 2990019);
    cars[2].is_car("never", "14h3GG2G3ti", "pink", 1235632);
    cars[3].is_car("Iniciator", "25s5HY8P8pe", "white", 1000231);
    cars[4].is_car("Stranger", "13h3GG2G3ti", "red", 2887733);
    cars[5].is_car("neverUndef", "23s5HY8P8pe", "gray", 8836501);
    cars[6].is_car("Iniciator", "23s5HY8P8pe", "gray", 8836501);
    cars[7].is_car("ybgs", "24s5HY8P8pe", "military", 1090023);
    cars[8].is_car("Iniciator", "21s5HY8P8pe", "aquamarine", 5599231);
    cars[9].is_car("hshshs", "21s5HY8P8pe", "aquamarine", 5599231);
}