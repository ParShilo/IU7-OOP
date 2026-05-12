#ifndef BASE_LIST_H
#define BASE_LIST_H

#include <stddef.h>

class baseList
{
public:
    virtual bool empty() const noexcept = 0;
    virtual size_t size() const noexcept = 0;
    virtual ~baseList() = default;

protected:
    size_t len = 0;
};

#endif