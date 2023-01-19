#include "MemberDatabase.h"
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

MemberDatabase::MemberDatabase()
{
}

MemberDatabase::~MemberDatabase()
{
   
    vector <PersonProfile*>:: iterator it = record.begin();
    for (;it!=record.end(); it++ )
    {
        if (*it != nullptr)
            delete *it;
 
    }
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    std::ifstream newfile (filename);
    ostringstream oss; string temp;
    string nameofperson;
    string emailofperson;
    string countstring;
    string inputpair;
    int countofpairs;
    
    while(newfile)
    {
        getline(newfile,nameofperson);
            if (nameofperson=="") break;
        getline(newfile,emailofperson);
            if (mapEmailsToPerson.search(emailofperson) != nullptr) return false;
        getline(newfile,countstring);
        countofpairs = stoi(countstring);
        
       PersonProfile* p = new PersonProfile(nameofperson,emailofperson);

       record.push_back(p);        //for deletion purposes
        
        for (int i=0; i<countofpairs; i++)
        {
            getline(newfile,inputpair);
            string attr = inputpair.substr(0,inputpair.find_first_of(","));
            string val  = inputpair.substr(inputpair.find_first_of(",")+1, string::npos);
            
            p->AddAttValPair(AttValPair(attr,val));
            
            wantToMapPairToEmails(inputpair, emailofperson);
        }
        
        mapEmailsToPerson.insert(emailofperson, p);
        getline(newfile, inputpair);

    }
    
    return true;
}


const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    PersonProfile* p;
    if (mapEmailsToPerson.search(email) == nullptr) return nullptr;
    p = * (mapEmailsToPerson.search(email));
    return p;
}


void MemberDatabase::wantToMapPairToEmails(string inputpair,string emailofperson)
{
    vector<string>* temp = mapAttPairsToEmails.search(inputpair);
    
    if (temp == nullptr)
    {
        vector<string> tobeadded;
        tobeadded.push_back(emailofperson);
        
        mapAttPairsToEmails.insert(inputpair, tobeadded);
    }
    
    else
    {
        vector<string>::iterator a,b,it;
        
        a = (*temp).begin();
        b = (*temp).end();
        
        it = find(a,b,emailofperson);
        
        if (it == b)
            (*temp).push_back(emailofperson);
        
    }
    
}


vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    string tofind;
    
    vector<string>* b;
    vector<string> emptyvec;
    
    tofind = input.attribute + "," + input.value;
    
    if (mapAttPairsToEmails.search(tofind) == nullptr) return emptyvec;
    
    b = mapAttPairsToEmails.search(tofind);
    return (*b);
}
