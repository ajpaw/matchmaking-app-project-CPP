#ifndef MemberDatabase_h
#define MemberDatabase_h
#include <stdio.h>
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"
#include <vector>
#include <string>
#include <algorithm>
 

class MemberDatabase
{
  public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    //which emails have this particular input pair?
    
    const PersonProfile* GetMemberByEmail(std::string email) const; //who has this email?

    
  private:
        
        //RadixTree <PersonProfile> mapEmailsToPerson;
        RadixTree <PersonProfile*> mapEmailsToPerson;
    
        RadixTree <vector<string>> mapAttPairsToEmails;
    
        void wantToMapPairToEmails(string inputpair,string emailofperson);
        vector <PersonProfile*> record;
};

#endif /* MemberDatabase_hpp */
