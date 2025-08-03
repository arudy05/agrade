#ifndef INCLUDE_AGRADE_HPP
#define INCLUDE_AGRADE_HPP

#include <string>
#include <vector>
#include <map>
#include "agrade-exceptions.hpp"

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
        Component() :                               // default component name and weight
        name{"default"}, grade{0}, weight{1},
        hasChildren{false}, children{nullptr} {}

        Component(std::string &n) :                  // component name with default weight
        name{n}, grade{0}, weight{1},
        hasChildren{false}, children{nullptr} {}

        Component(std::string &n, double &w) :        // component name with set weight
        name{n}, grade{0}, weight{w},
        hasChildren{false}, children{nullptr} {}

        // Getters and setters ----------------------------------------------------------

        const std::string &getName() {
            // Returns name as a const
            return name;
        }

        void setName(std::string &n) {
            // Sets name
            name = n;
        }

        const double &getGrade() {
            // Returns the grade of a component.
            // If this component has children, we get this grade from the assicated ComponentGroup
            if (hasChildren) grade = children->calculateGrade();
            return grade;
        }

        void setGrade(double &g) {
            // Sets the grade of a component.
            // If this component has children, then we should not be setting its grade using this function.
            // Additionally, the grade should not be < 0 (a negative number).
            if (hasChildren) throw agrade::componentHasChildren();
            else if (g < 0) throw agrade::componentGradeError();
            else grade = g;
        }

        const double &getWeight() {
            // returns weight of the component
            return weight;
        }

        void setWeight(double &w) {
            // sets the weight of a component.
            // the weight of a component cannot and should not be <= zero
            if (w <= 0) throw agrade::componentWeightError();
            weight = w;
        }
    };

    class ComponentGroup {
        /* Each ComponentGroup object represents a group of components from which
        we can calculate an average or weighted total mark for this group. */
        std::vector<Component*> members; // Vector of pointers to the ComponentGroup's members.
    public:
        // Constructors -----------------------------------------------------------------
        ComponentGroup() {}         // default constructor, no need to do anything
        // Getting members --------------------------------------------------------------
        Component* getMember(std::string &n) {
            for (int i = 0; i < members.size(); ++i) {
                if (members[i]->getName() == n) return members[i];
            }
            throw agrade::componentNotFoundError();
            return nullptr;
        }
        // Adding members ---------------------------------------------------------------
        // Each function corresponds to a constructor of Component
        void addMember() {
            members.push_back(new Component());
        }
        void addMember(std::string &n) {
            members.push_back(new Component(n));
        }
        void addMember(std::string &n, double &w) {
            members.push_back(new Component(n, w));
        }
        // Calculating total grade ------------------------------------------------------
        double calculateGrade() {
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
    };

    class Course : public ComponentGroup {
        std::map<std::string, double> gradeDist;
        std::string mark;
    };
}
#endif
