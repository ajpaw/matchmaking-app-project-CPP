
#ifndef utility_h
#define utility_h
#include "provided.h"

inline
bool sortcompare (const EmailCount ec1, const EmailCount ec2)
{
    if (ec1.count > ec2.count) return true;

    if (ec1.count == ec2.count)
    {
        if (ec1.email < ec2.email) return true;
    }
    
    return false;
};

#endif /* utility_h */
