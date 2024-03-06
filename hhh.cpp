#include "hhh.h"

class hhhData : public QSharedData
{
public:

};

hhh::hhh() : data(new hhhData)
{

}

hhh::hhh(const hhh &rhs) : data(rhs.data)
{

}

hhh &hhh::operator=(const hhh &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

hhh::~hhh()
{

}
