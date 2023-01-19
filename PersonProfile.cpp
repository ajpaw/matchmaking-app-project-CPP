#include "PersonProfile.h"
using namespace std;

PersonProfile::PersonProfile(std::string name,  std::string email)
{
    myname = name;
    myemail = email;
}

PersonProfile::~PersonProfile()
{
}

std::string PersonProfile::GetName() const
{
 return myname;
}


std::string PersonProfile::GetEmail() const
{
    return myemail;
}

int PersonProfile::GetNumAttValPairs() const
{
    return (int)myvector.size();
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
    vector<string>* temp = mapAttrToValues.search(attval.attribute);
 
    
    if (temp == nullptr)
    {
        vector<string> tobeadded;
        tobeadded.push_back(attval.value);
        mapAttrToValues.insert(attval.attribute, tobeadded);
        myvector.push_back(attval);
    }
    
    else
    {
        vector<string> now = *temp;
        now.resize(now.size()+1);
        now.push_back(attval.value);
        mapAttrToValues.insert(attval.attribute, now);
        myvector.push_back(attval);
 
    }
    
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num<0 || attribute_num>=GetNumAttValPairs()) return false;
    
    attval = (myvector)[attribute_num];
    
    return true;
}

 
