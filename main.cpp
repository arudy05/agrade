#include "agrade.hpp"
#include <iostream>
using namespace agrade;

int main() {
    Component course1 {"Course"};
    course1.addChild("Final", 50);
    course1.addChild("Midterm", 30);
    course1.addChild("Assignments", 20);

    course1.getChild("Midterm")->setGrade(60);
    std::cout << course1.getGrade() << std::endl;
}
