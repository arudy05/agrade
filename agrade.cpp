#include "agrade.hpp"
#include "agrade-exceptions.hpp"
using namespace agrade;

// This file contains function definitions for the classes in the agrade namespace.
// This is done such that agrade.hpp outlines the structure of the namespace
// and agrade.cpp contains actual function definitions. This is mainly because
// public functions in the Component and ComponentGroup classes are used in the
// other so I'm effectively forward declaring everything to avoid future headaches.

///////////////////////
// agrade::Component //
///////////////////////

// Constructors
Component::Component() : name{"default"}, grade{0}, weight{1},
hasChildren{false}, children{nullptr} {}

Component::Component(std::string &n) : name{n}, grade{0}, weight{1},
hasChildren{false}, children{nullptr} {}

Component::Component(std::string &n, double &w) : name{n}, grade{0}, weight{w},
hasChildren{false}, children{nullptr} {}

const std::string &Component::getName() {
    return name;
}

// Getter/setter functions
void Component::setName(std::string &n) {
    name = n;
}

const double &Component::getGrade() {
    // If this component has children, we get this grade from the assicated ComponentGroup
    if (hasChildren) grade = children->calculateGrade();
    return grade;
}

void Component::setGrade(double &g) {
    // If this component has children, then we should not be setting its grade using this function.
    // Additionally, the grade should not be < 0 (a negative number).
    if (hasChildren) throw agrade::componentHasChildren();
    else if (g < 0) throw agrade::componentGradeError();
    else grade = g;
}

const double &Component::getWeight() {
    return weight;
}

void Component::setWeight(double &w) {
    // the weight of a component cannot and should not be <= zero
    if (w <= 0) throw agrade::componentWeightError();
    weight = w;
}


////////////////////////////
// agrade::ComponentGroup //
///////////////////////////

// Getting members
Component* ComponentGroup::getMember(std::string &n) {
    for (int i = 0; i < members.size(); ++i) {
        if (members[i]->getName() == n) return members[i];
    }
    throw agrade::componentNotFoundError();
    return nullptr;
}

// Adding members
void ComponentGroup::addMember() {
    members.push_back(new Component());
}
void ComponentGroup::addMember(std::string &n) {
    members.push_back(new Component(n));
}
void ComponentGroup::addMember(std::string &n, double &w) {
    members.push_back(new Component(n, w));
}

// Calculating grade
double ComponentGroup::calculateGrade() {
    if (members.size() == 0) {
        throw agrade::componentGroupNoChildrenError();
        return 0;
    }
    double numerator = 0;
    double denominator = 0;

    for (int i = 0; i < members.size(); ++i) {
        numerator += members[i]->getGrade()*members[i]->getWeight();
        denominator += members[i]->getWeight();
    }

    return numerator/denominator;
}
