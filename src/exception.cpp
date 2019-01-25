#include <stuff/exception.h>

namespace stuff {

    void format_exception(std::string& str, const std::exception& e, int level)
    {
        // format the current exception
        if (level != 0) {
            str += "\n";
        }
        str += std::string(level * 2, ' ');
        str += e.what();

        // unwind any nested exceptions
        try {
            std::rethrow_if_nested(e);
        }
        catch (std::exception& e) {
            format_exception(str, e, ++level);
        }
    }

    std::string to_string(const std::exception& e)
    {
        std::string msg;
        format_exception(msg, e, 0);
        return msg;
    }

} // namespace stuff
