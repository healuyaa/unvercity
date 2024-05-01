#include <iostream>

class Weapon {
public:
    virtual void Use() = 0;
    void Func() {
        std::cout << "Func()" << std::endl;
    }
};

class Pistol : public Weapon {
public: 
    void Use() override {
        std::cout << "Bang!" << std::endl;
    }
};

class SubmachineGun : public Pistol {
public: 
    void Use() override {
        std::cout << "Bang! Bang! Bang!" << std::endl;
    }
};

class Bazooka : public Weapon {
public: 
    void Use() override {
        std::cout << "Badaboom!" << std::endl;
    }
};

class Knife : public Weapon {
public: 
    void Use() override {
        std::cout << "Vjuh!" << std::endl;
    }
};

class Player {
public:
    void Use(Weapon *weapon) {
        weapon->Use();
    }
};

int main() {
    Player player;

    Pistol pistol;
    SubmachineGun sub;
    Bazooka bazooka;
    Knife knife;
    player.Use(&pistol);
    player.Use(&sub);
    player.Use(&bazooka);
    player.Use(&knife);
}