#ifndef PersonProfile_h
#define PersonProfile_h
#include <stdio.h>
#include "provided.h"
#include "RadixTree.h"
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
 
class PersonProfile
{
  public:
     PersonProfile(std::string name, std::string email);
     ~PersonProfile();
     std::string GetName() const;
     std::string GetEmail() const;
     void AddAttValPair(const AttValPair& attval);
     int GetNumAttValPairs() const;
     bool GetAttVal(int attribute_num, AttValPair& attval) const;
                                            //which pairs do you have, Person?
  
private:
     std::string myname;
     std::string myemail;
     std::vector <AttValPair>  myvector;
     RadixTree <vector<string>> mapAttrToValues;

};

#endif /* PersonProfile_hpp */
