//#include "src/controller/body/DemoCross.cpp"
#include <iostream>
#include <vector>

int main() {
//    DemoCross *demoCross = new DemoCross;
//    demoCross->input();
//    demoCross->output();
    std::vector<int> vectorContainer;
    for (int intIndex = 0; intIndex < 10; ++intIndex) {
        vectorContainer.push_back(intIndex);
    }

    for (auto iterator:vectorContainer) {
        std::cout << iterator << std::endl;
    }
    for (auto intPointer = vectorContainer.begin(); intPointer != vectorContainer.end(); ++intPointer) {
        std::cout << *intPointer << std::endl;
    }
    return 0;
}