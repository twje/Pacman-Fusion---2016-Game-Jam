#ifndef _COMMON_
#define _COMMON_

#include <iostream>
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

//*********
// PacmanID
//*********
const std::string RED_PACMAN = "red_pacman";
const std::string BLUE_PACMAN = "blue_pacman";
const std::string GREEN_PACMAN = "green_pacman";

inline bool isPacman(std::string l_characterId)
{
    bool result = false;
    result |= (l_characterId == RED_PACMAN);
    result |= (l_characterId == BLUE_PACMAN);
    result |= (l_characterId == GREEN_PACMAN);

    return result;
}

#endif // _COMMON_
