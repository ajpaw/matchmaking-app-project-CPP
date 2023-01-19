#ifndef MatchMaker_h
#define MatchMaker_h
#include "PersonProfile.h"
#include <stdio.h>
#include "provided.h"
#include  <map>
#include <vector>
#include <algorithm>
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "utility.h"

class MatchMaker
{
    public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
    
    private:
    const MemberDatabase* mydatabase;
    const AttributeTranslator* mytranslator;
    void tallycount (vector<string> vec, int threshold) const;
    map<string, int> tallymap;
   
    
};

#endif /* MatchMaker_hpp */
