#include <iostream>

class Gun {
public:
    virtual void Shoot() {
        std::cout << "Bang!" << std::endl;
    }
};

class SubmuchineGun : public Gun{
public: 
    void Shoot() override {
        std::cout << "Bang! Bang! Bang!" << std::endl;
    }
};

class Bazooka : public Gun{
public: 
    void Shoot() override {
        std::cout << "Badaboom!" << std::endl;
    }
};

class Player {
public:
    void Shoot(Gun *gun) {
        gun->Shoot();
    }
};

int main() {
    Gun gun;
    SubmuchineGun muchinegun;
    Bazooka bazooka;

    Gun *weapon = &gun;
    Gun *weapon_ = &muchinegun;
    Gun *weapon__ = &bazooka;

    Player player;
    player.Shoot(weapon);
    player.Shoot(weapon_);
    player.Shoot(weapon__);

}