#include <iostream>
#include <vector>
#include <array>
#include <random>

class SmokeDetector {
public:
    void InitStatus() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);

        auto GenStatus = [&gen, &dis]() {
            std::array<bool, 4> status_arr;
            for (bool& status : status_arr) {
                status = dis(gen);
            }
            return status_arr;
        };

        auto status_array = GenStatus();

        this->smoke = status_array[0];
        this->fire = status_array[1];
        this->noise = status_array[2];
        this->heap = status_array[3];
    }

    std::vector<bool> GetStatus() {
        std::vector<bool> status_returned = {this->smoke, this->fire, this->noise, this->heap};
        return status_returned;
    }

private:
    bool smoke;
    bool fire;
    bool noise;
    bool heap;
};

class SystemControl {
public:
    struct FireLocation {
        int floor;
        int detector;
    };

    static int StatusSimpleDetector(SmokeDetector& detector) {
        auto status = detector.GetStatus();
        int fireCount = 0;
        for (bool value : status) {
            if (value) {
                ++fireCount;
            }
        }
        return fireCount;
    }

    static FireLocation IsFireDetected(std::vector<std::vector<SmokeDetector>>& building) {
        const int rows = building.size();
        const int cols = building.empty() ? 0 : building[0].size();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int fireCount = StatusSimpleDetector(building[i][j]);

                if (fireCount >= 2) {
                    return {i + 1, j + 1};
                }
            }
        }
        return {-1, -1};
    }

    static std::vector<int> CheckFirePerFloor(std::vector<std::vector<SmokeDetector>>& building) {
        const int rows = building.size();
        const int cols = building.empty() ? 0 : building[0].size();
        std::vector<int> firePerFloor(rows, 0);

        for (int i = 0; i < rows; ++i) {
            bool confirmedFire = false;

            for (int j = 0; j < cols - 1; ++j) {
                auto status1 = building[i][j].GetStatus();
                auto status2 = building[i][j + 1].GetStatus();

                // Checking if two adjacent detectors have two characteristics equal to 1
                int count1 = status1[1] + status1[2]; // Counting 'fire' and 'noise' characteristics of detector 1
                int count2 = status2[1] + status2[2]; // Counting 'fire' and 'noise' characteristics of detector 2

                if (count1 >= 1 && count2 >= 1) { // At least one characteristic should be 1 in each detector
                    firePerFloor[i] = 1;
                    confirmedFire = true;
                    break;
                }
            }

            if (!confirmedFire) {
                std::cout << "No fire detected on Floor " << i + 1 << std::endl;
            }
        }

        return firePerFloor;
    }
};

int main() {
    std::vector<std::vector<SmokeDetector>> building = {
        std::vector<SmokeDetector>(7),
        std::vector<SmokeDetector>(5),
        std::vector<SmokeDetector>(6)
    };

    for (auto& floor : building) {
        for (auto& detector : floor) {
            detector.InitStatus();
        }
    }

    for (std::size_t i = 0; i < building.size(); ++i) {
        std::cout << "Floor " << i + 1 << ":" << std::endl;
        for (std::size_t j = 0; j < building[i].size(); ++j) {
            std::cout << "  Detector " << j + 1 << ": ";
            auto status = building[i][j].GetStatus();
            for (bool value : status) {
                std::cout << (value ? "1" : "0") << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<int> firePerFloor = SystemControl::CheckFirePerFloor(building);
    for (size_t i = 0; i < firePerFloor.size(); ++i) {
        if (firePerFloor[i] == 1) {
            std::cout << "Fire detected on Floor " << i + 1 << std::endl;
        } else {
            std::cout << "No fire detected on Floor " << i + 1 << std::endl;
        }
    }

    if(firePerFloor[0] == firePerFloor[1] == firePerFloor[2]) {
        std::cout << "Building on fire" << std::endl;
    } else {
        std::cout << "All fine" << std::endl;
    }

    return 0;
}
