#include "MatchMaker.h"

#include "provided.h"
#include <set>
#include <unordered_set>
#include <algorithm>
#include "utility.h"

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    mydatabase = &mdb;
    mytranslator = &at; 
    
}

MatchMaker::~MatchMaker()
{}



std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email,
int threshold) const
{
    const PersonProfile* p = mydatabase->GetMemberByEmail(email);
    set <string> whatINeedToLookFor;    //set of all the ideal target pairs
    vector <EmailCount> resultsOfAlgorithm;
    vector<AttValPair> appending;
 
    if (p==nullptr) return resultsOfAlgorithm;
    
    for (int i=0; i<p->GetNumAttValPairs(); i++)
    {
        AttValPair av;
        p->GetAttVal(i, av);
        appending = mytranslator->FindCompatibleAttValPairs(av);
   
        for (int i = 0; i<appending.size(); i++)
        {
            whatINeedToLookFor.insert(appending[i].attribute + "," + appending[i].value);
        }
    }
    
    //now the set has everything that we are looking for in candidates
    
    vector<std::string> subMatches;
    
    set <string>::iterator it = whatINeedToLookFor.begin();
    
    map<string, int> tallymap;
    
    while (it!=whatINeedToLookFor.end())
    {
        string fullpair = *it; size_t temp = fullpair.find_first_of(',');
        string attr = fullpair.substr(0,temp);
        string val = fullpair.substr(temp+1);
        
        subMatches = mydatabase->FindMatchingMembers(AttValPair(attr,val));
        
        for (int i=0; i<subMatches.size(); i++)
        {
             map<string, int>::iterator itr = tallymap.find(subMatches[i]);
             
             if (itr == tallymap.end())
                tallymap [subMatches[i]] = 1;
            
             else
                itr->second = itr->second +1;
        }
         
        it++;
    }
    
    
                                //this map helps to keep track of count
    map<string, int>::iterator itr = tallymap.begin();
    
    if (threshold<=0)  threshold = 1;
    
    while (itr!=tallymap.end())
    {
        if (itr->second >= threshold && itr->first!=email)
            resultsOfAlgorithm.push_back(EmailCount(itr->first, itr->second));
        itr++;
    }
    
    sort(resultsOfAlgorithm.begin(), resultsOfAlgorithm.end(), sortcompare);
    return resultsOfAlgorithm;
}

 



 


 
