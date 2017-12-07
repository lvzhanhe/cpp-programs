#ifndef _PACKAGE
#define _PACKAGE

#include <iostream>
using std::ostream;

struct Package{
public:
    long weight_;
    long priority_;
    Package(long w=0, long p=0): weight_(w), priority_(p){};
};

ostream& operator<<(ostream& out, Package& p);

bool package_compare(const Package &p1, const Package &p2);

#endif