#ifndef INCLUDE_AGRADE_HPP
#define INCLUDE_AGRADE_HPP

#include <string>
#include <vector>
#include "agrade-exceptions.hpp"

namespace agrade
{ // namespace for all things agrade

    // forward declarations first because yeah
    class Component;
    class ComponentGroup;

    class Component{
        /* each Component object is a graded portion of a parent Component's grade. */
        std::string name;           // name of the component
        double grade;               // grade assigned to that component
        double weight;              // weight of that component towards the ComponentGroup

        /* If a Component's mark is based on the (possibly weighted) average of subcomponents,
         it is said to have children, in which case hasChildren = true and children is not empty */
        bool hasChildren;
        std::vector<Component*> children;   // if hasChildren = false, this is empty

        // Helper functions ------------------------------------------------------------------
        double calculateGrade();

    public:
        // Constructors -----------------------------------------------------------------
        Component();                                // default component name and weight
        Component(std::string n);                  // component name with default weight
        Component(std::string n, double w);       // component name with set weight
        // "Big 5" funcs ----------------------------------------------------------------
        ~Component();                               // destructor

        // Getters and setters ----------------------------------------------------------
        const std::string &getName();               // name
        void setName(std::string n);
        const double &getGrade();                   // grade
        void setGrade(double g);
        const double &getWeight();                  // weight
        void setWeight(double w);

        // Adding child components ------------------------------------------------------
        void addChild();                            // each corresponds to a constructor
        void addChild(std::string n);
        void addChild(std::string n, double w);

        // Accessing child components ---------------------------------------------------
        Component* operator[](int i);               // by index (operator overload)
        Component* getChild(int i);                // by index
        Component* getChild(std::string n);       // by component name

        // Removing child components ----------------------------------------------------
        void removeChild(int i);                    // by index
        void removeChild(std::string n);           // by component name
    };
}
#endif
