#include <iostream>
#include <string>

class Cap {
    public:
    std::string get_color() {
        return color;
    }

    private:
    std::string color = "red";
};

class Model {
    public:
        void InspectModel() {
            std::cout << "Color cap " << cap.get_color() << std::endl;
        }

    private:
        Cap cap;
};

class Human {   
    public:
        void Think() {
            brain.Think();
        }

        void InspectTheCap() {
            std::cout << "Color cap " << cap.get_color() << std::endl;
        }

    private:
        class Brain {
            public:
                void Think() {
                    std::cout << "Thinking!" << std::endl;
                }
        };
            
        Brain brain;
        Cap cap; 
};

int main() {
    Human human1;
    human1.Think();
    human1.InspectTheCap();

    Model model1;
    model1.InspectModel();
}