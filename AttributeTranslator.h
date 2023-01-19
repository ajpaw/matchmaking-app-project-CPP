#ifndef AttributeTranslator_h
#define AttributeTranslator_h
#include "provided.h"
#include "RadixTree.h"
#include <stdio.h>
#include <vector>
#include <algorithm>

class AttributeTranslator
{
    public:
     AttributeTranslator();
     ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs( const AttValPair& source) const;
                    //which pairs are compatible with this pair?
    
     private:
     RadixTree <std::vector<AttValPair>> mapPairToCompatible;
     void parse (string inputpair);
};

#endif /* AttributeTranslator_hpp */
