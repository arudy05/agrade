#include "agrade.hpp"
#include "agrade-exceptions.hpp"
using namespace agrade;

// This file contains function definitions for the classes in the agrade namespace.
// This is done such that agrade.hpp outlines the structure of the namespace
// and agrade.cpp contains actual function definitions.

///////////////////////
// agrade::Component //
///////////////////////

// Constructors
Component::Component() : name{"default"}, grade{0}, weight{1},
hasChildren{false}, children{nullptr} {}

Component::Component(std::string n) : name{n}, grade{0}, weight{1},
hasChildren{false}, children{nullptr} {}

Component::Component(std::string n, double w) : name{n}, grade{0}, weight{w},
hasChildren{false}, children{nullptr} {}

// "Big 5"
Component::~Component() {
    for (int i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}

// Helper functions
double Component::calculateGrade() {
    if (children.size() == 0 || !hasChildren) {
        throw agrade::componentNoChildrenError();
        return 0;
    }
    double numerator = 0;
    double denominator = 0;

    for (int i = 0; i < children.size(); ++i) {
        numerator += children[i]->getGrade()*children[i]->getWeight();
        denominator += children[i]->getWeight();
    }

    return numerator/denominator;
}

// Getter/setter functions
const std::string &Component::getName() {
    return name;
}

void Component::setName(std::string n) {
    name = n;
}

const double &Component::getGrade() {
    // If this component has children, we get this grade from the assicated ComponentGroup
    if (hasChildren) grade = calculateGrade();
    return grade;
}

void Component::setGrade(double g) {
    // If this component has children, then we should not be setting its grade using this function.
    // Additionally, the grade should not be < 0 (a negative number).
    if (hasChildren) throw agrade::componentHasChildren();
    else if (g < 0) throw agrade::componentGradeError();
    else grade = g;
}

const double &Component::getWeight() {
    return weight;
}

void Component::setWeight(double w) {
    // the weight of a component cannot and should not be <= zero
    if (w <= 0) throw agrade::componentWeightError();
    weight = w;
}

// Adding children
void Component::addChild() {
    if (!hasChildren) hasChildren = true;
    children.push_back(new Component());
}
void Component::addChild(std::string n) {
    if (!hasChildren) hasChildren = true;
    children.push_back(new Component(n));
}
void Component::addChild(std::string n, double w) {
    if (!hasChildren) hasChildren = true;
    children.push_back(new Component(n, w));
}


// Accessing children
Component* Component::operator[](int i) {
    // std::vector should handle any out-of-bounds stuff on its own
    return children[i];
}

Component* Component::getChild(int i) {
    // std::vector should handle any out-of-bounds stuff on its own
    return children[i];
}

Component* Component::getChild(std::string n) {
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->getName() == n) return children[i];
    }
    throw agrade::componentNotFoundError();
    return nullptr;
}


// Removing/deleting children
void Component::removeChild(int i) {
    Component *orphan = children[i];
    children.erase(children.begin()+i);
    delete orphan;
    if (children.empty()) hasChildren = false;
}

void Component::removeChild(std::string n) {
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->getName() == n) {
            Component *orphan = children[i];
            children.erase(children.begin()+i);
            delete orphan;
            if (children.empty()) hasChildren = false;
            return;
        }
    }
    throw agrade::componentNotFoundError();
    return;

}
