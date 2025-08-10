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
        ComponentGroup *children;   // if hasChildren = false, this is a nullptr

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
    };

    class ComponentGroup {
        /* Each ComponentGroup object represents a group of components from which
        we can calculate an average or weighted total mark for this group. */
        std::vector<Component*> members; // Vector of pointers to the ComponentGroup's members.
    public:
        // Constructors -----------------------------------------------------------------
        ComponentGroup() {}         // default constructor, no need to do anything
        // Getting members --------------------------------------------------------------
        Component* getMember(std::string &n);
        // Adding members ---------------------------------------------------------------
        // Each function corresponds to a constructor of Component
        void addMember();
        void addMember(std::string &n);
        void addMember(std::string &n, double &w);
        // Calculating total grade ------------------------------------------------------
        double calculateGrade();
    };

    class Course : public ComponentGroup {
        std::map<std::string, double> gradeDist;
        std::string mark;
    };
}
#endif
