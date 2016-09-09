#ifndef _COMMON_
#define _COMMON_

#include <string>

//*******
// Object
//*******
class Object {
public:
    virtual ~Object(){}
    virtual std::string toString(){ return "Object"; }
    virtual void* getSelf() = 0;
};

//**************
// ObjectAdapter
//**************
template<typename T>
class ObjectAdapter: public Object {
private:
    T* m_object;

public:
    ObjectAdapter(T* l_object):
    m_object(l_object)
    {}

    virtual std::string toString(){ return "ObjectAdapter"; }
    virtual void* getSelf(){ return m_object; }
};

//**********
// TupleInt4
//**********
struct TupleInt4
{
    int m_left;
    int m_right;
    int m_top;
    int m_bottom;
};

#endif // _COMMON_
