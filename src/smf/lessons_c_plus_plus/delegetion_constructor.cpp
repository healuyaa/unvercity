#include <iostream>
#include <string>

class Human {
    public:

    Human(std::string name) {
        this->name = name;
        age = 0;
        weight = 0;
    }
    Human(std::string name, int age) : Human(name) {
        this->age = age;
    }
    Human(std::string name, int age, int weight) : Human(name, age) {
        this->weight = weight;
    }

    void Print() {
        std::cout << "name: " << this->name << " age: " << this->age << " weight: " << this->weight << std::endl;
    }

    private: 
    std::string name;
    int age;
    int weight;
};

int main() {
    Human human("Aris", 29, 60);
    human.Print();
}