#include <iostream>

class Image {
    public:
    class Pixel
    {
        public:
        Pixel(int r, int g, int b) : r(r), g(g), b(b) {}

        std::string GetInfo() {
            return "Pixel: r = " + std::to_string(r) + " g = " + std::to_string(g) + " b = " + std::to_string(b);
        }
        private:
            int r;
            int g;
            int b;
    };

    Image(int r, int g, int b) {
        Image::Pixel(r, g, b);
    }

    void get_info() {
        std::cout << "1" << std::endl;
    }
    private:    
};

int main() {
    Image::Pixel img1(243, 123, 0);
    std::cout << img1.GetInfo();
    Image img2(255, 91, 34);
    img2.get_info();
}