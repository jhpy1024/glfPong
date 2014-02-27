#include <sstream>

namespace util
{
    template <typename T>
    std::string toString(T var)
    {
        std::stringstream ss;
        ss << var;
        return ss.str();
    }
}
