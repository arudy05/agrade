#ifndef INCLUDE_AGRADE_HPP
#define INCLUDE_AGRADE_HPP

#include <string>
#include <vector>
#include <map>

namespace agrade
{ // namespace for all things agrade

    // forward declarations first because yeah
    class Component;
    class ComponentGroup;

    class Component{
        /* each Component object is a graded portion of a ComponentGroup worth a certain amount
        of that ComponentGroup's final mark. */
        std::string name;           // name of the component
        double grade;               // grade assigned to that component
        double weight;              // weight of that component towards the ComponentGroup

        /* If a Component's mark is based on the (possibly weighted) average of subcomponents,
         it is said to have children, in which case hasChildren = true and children is a pointer
         to a ComponentGroup*/
        bool hasChildren;
        std::vector<Component*> children;   // if hasChildren = false, this is empty

        // Helper functions ------------------------------------------------------------------
        double calculateGrade();

    public:
        // Constructors -----------------------------------------------------------------
        Component();                                 // default component name and weight
        Component(std::string &n);                   // component name with default weight
        Component(std::string &n, double &w);        // component name with set weight

        // Getters and setters ----------------------------------------------------------
        const std::string &getName();               // name
        void setName(std::string &n);
        const double &getGrade();                   // grade
        void setGrade(double &g);
        const double &getWeight();                  // weight
        void setWeight(double &w);

        // Adding child components ------------------------------------------------------
        void addChild();                            // each corresponds to a constructor
        void addChild(std::string &n);
        void addChild(std::string &n, double &w);

        // Accessing child components ---------------------------------------------------
        Component* operator[](int i);               // by index (operator overload)
        Component* getMember(std::string &n);       // by component name
    };

}
#endif
