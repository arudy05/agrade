#ifndef INCLUDE_AGRADE_EXCEPTIONS_HPP
#define INCLUDE_AGRADE_EXCEPTIONS_HPP

#include <string>
using string = std::string;

namespace agrade {

    class BaseException {
        /* Base class for all exceptions defined by this library,
        can be used to define custom errors but usually shouldn't*/
    protected:
        string errorDesc; // error description

    public:
        BaseException(string error) : // for defining custom errors
        errorDesc{error} {}

        const string& what() const { return errorDesc; }
        const string& getError() const { return what(); }
    };

    class componentHasChildren : public BaseException {
    public:
        componentHasChildren() :
        BaseException("Trying to set grade for component with children") {}
    };
    class componentGradeError : public BaseException {
    public:
        componentGradeError() :
        BaseException("Trying to set component grade to a negative number") {}
    };

    class componentWeightError : public BaseException {
    public:
        componentWeightError() :
        BaseException("Trying to set component weight to zero or a negative value") {}
    };

    class componentNotFoundError : public BaseException {
    public:
        componentNotFoundError() :
        BaseException("Specified component does not exist") {}
    };

    class componentGroupNoChildrenError : public BaseException {
    public:
        componentGroupNoChildrenError() :
        BaseException("Component group does not have children; cannot calculate grade") {}
    };
}

#endif
