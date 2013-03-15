
#ifndef __EXENG_SYSTEM_LIBRARYPRIVATE_HPP__
#define __EXENG_SYSTEM_LIBRARYPRIVATE_HPP__

#include "Library.hpp"

namespace exeng
{
    namespace system
    {
        struct Library::Private
        {
            std::string name;
            void* handle;

            Private();

            FunctionPtr getFunctionPtr(const std::string &name);
            void load(const std::string &name);
            void unload();
        };
    }
}

#endif	//__EXENG_SYSTEM_LIBRARYPRIVATE_HPP__