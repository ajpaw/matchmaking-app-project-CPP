#include "AttributeTranslator.h"
#include "RadixTree.h"
#include "provided.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

AttributeTranslator::AttributeTranslator()
{}

AttributeTranslator::~AttributeTranslator()
{}

void AttributeTranslator::parse (string inputpair)      //a private, utility function
{
    size_t firstcomma =   inputpair.find_first_of(',', 0);
    size_t secondcomma =  inputpair.find_first_of(',', firstcomma+1);
    size_t thirdcomma =   inputpair.find_first_of(',', secondcomma+1);
    
    string keypair = inputpair.substr(0,secondcomma);
    string targetattr = inputpair.substr(secondcomma+1, thirdcomma-secondcomma-1);
    string targetvalue = inputpair.substr(thirdcomma+1);
    
    vector<AttValPair>* temp = mapPairToCompatible.search(keypair);
    
    if (temp == nullptr)
    {
        vector<AttValPair> tobeadded;
        tobeadded.push_back(AttValPair(targetattr,targetvalue));
        mapPairToCompatible.insert(keypair, tobeadded);  
    }
    
    else
        temp->push_back(AttValPair(targetattr,targetvalue));
}
 
 
bool AttributeTranslator::Load(string filename)
{
    std::ifstream newfil (filename);
    string input;
    
    while(newfil)
    {
        getline(newfil,input);
        if (input == "") continue;
        if (input.length()>0) parse(input);
    }
    
    
    return true;
}


std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    vector<AttValPair> result;
    
    string tofind = source.attribute+","+source.value;      //creating a searchable key by concatention
    
    vector<AttValPair>* output = mapPairToCompatible.search(tofind);
    
    if (output == nullptr) return result;
    
    return *output;
}


