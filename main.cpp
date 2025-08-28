#include "agrade.hpp"
#include <iostream>
using namespace agrade;

int main() {
    try {
        Component course1 {"Course"};
        course1.addChild("Final", 50);
        course1.addChild("Midterm", 30);
        course1.addChild("Assignments", 20);

        Component* mt = course1.getChild(1);
        mt->setGrade(80);

        Component* final = course1.getChild("Final");
        final->setGrade(40);

        course1.getChild(2)->setWeight(0); // this should throw an error

        std::cout << course1.getGrade() << std::endl;
    }
    catch(agrade::BaseException except) {
        std::cout << "Error: " << except.what() << std::endl;
    }
}
