#include "agrade.hpp"
#include <iostream>
using namespace agrade;

int main() {
    Component course1 {"Course"};
    course1.addChild("Final", 50);
    course1.addChild("Midterm", 30);
    course1.addChild("Assignments", 20);

    Component* mt = course1.getChild(1);
    mt->setGrade(80);

    Component* final = course1.getChild("Final");
    final->setGrade(75);

    std::cout << course1.getGrade() << std::endl;
}
