#ifndef RadixTree_h
#define RadixTree_h
#include <iostream>
#include <stdio.h>
#include<string>
#include<cctype>
using namespace std;

template <typename ValueType>
class RadixTree
{
    private:    
        
        struct Node
        {
            bool marksEnd;
            string collap;
            Node* edges[128];
            ValueType v;
            Node* parent;
       
            Node(string init, ValueType value, bool end, Node* par)
            {
                collap = init;
                marksEnd = end;
                v = value;
                parent = par;
                
                for (int i=0; i<128; i++)
                    edges[i] = nullptr;
            }
            
            ~Node()
            {
                 
                for (int i=0; i<128; i++)
                    if (edges[i] != nullptr)  delete edges[i];
            }
   
        };
         
        Node* root;
       
        
        int translate (char c) const
        {
             
            return (int) c;
        };
    
    
          public:
            RadixTree()
            { 
                  root = new Node("", ValueType(),false,nullptr);
            };
        
            ~RadixTree()
            {
                 
                 if (root!= nullptr ) delete root;
                
            };
            
            
            ValueType* search(std::string key) const
            {
                Node* current = root;
                ValueType* ptrreturn = nullptr;
                string prog="";
                
                for (int i=0; i<key.length(); i++)
                {
                    prog += current->collap;
                     
                    if (prog == key) break;
                    
                    if (prog!="" && key.find(prog) != 0 ) return nullptr;
                    if (current->collap.length()>1)
                        i += current->collap.length()-1;
                       
                    
                    if (current->edges[translate(key[i])] == nullptr)
                    return nullptr;         //terminate if the letter sequence does not exist
                    
                    current = current->edges[translate(key[i])];
                   
                }
                
                if (current->marksEnd)
                {
                    ptrreturn =  &(current->v);
                    return ptrreturn;
                }
                
                return nullptr;         //no word ended there so we return null
        
            };
    
            void insert(std::string key, const ValueType& value)
            {
                Node* current = root;
                string s = key;
                string prog ="";    //prog is the string for storing 'progress' as we travel down edges
                
                
                ValueType tobeput = ValueType(value);           //dynamic (shallow) copying
                
                for (int i=0; i<key.length(); i++)  //this is the only ITERATIVE loop so we maintain O(k)
                {
                                
                    if (current == root && current->edges[translate(key[i])] == nullptr)
                    {
                        current->edges[translate(key[i])] = new Node(s, tobeput, true, root);
                        return;
                    }
                                
                    else if (current->edges[translate(key[i])] != nullptr)
                    {
                            if (prog.length() >= key.length()) continue;
            
                            if (key.find(prog) == 0)
                            {
                                current = current->edges[translate(key[i])];
                                prog += current->collap;
                
                                i += current->collap.length()-1;
                             
                              
                                if (key.find(prog) != 0)    //this indicates a split-off point
                                {
                                    int ctr=0; size_t i = 0;
                                 
                                    for ( ; i<key.length() && i<prog.length();i++)
                                    {
                                        if (key[i] == prog[i]) ctr++;
                                        else break;
                                    }
                                 
                                     int adj = (int)prog.size()-(int)current->collap.size();
                      
                                     string earlier    = current->collap;
                                      
                                        
                                    current->collap   = current->collap.substr(ctr-adj);
                   
                                     
                                    Node* branch = new Node (earlier.substr(0,ctr-adj),ValueType(), false, current->parent);
                                    
                                    current->parent->edges[translate(earlier.substr(0,ctr-adj)[0])]  = branch;
                                    
                                    branch->edges[translate(current->collap[0])] = current;
                                    
                                    current->parent = branch;
                                        
                                    current = current->parent;
                    
                         
                                    current->edges[translate(key[ctr])] = new Node(key.substr(ctr), tobeput, true, current);
                                    
                                    if (key.find(prog)== 0) current->marksEnd = true;
                                    else current->marksEnd = false;
                                    
                                    return;
                
                             }
                          }
                                    
                        continue;
                      }
                                
                      else  //there was an interruption in the letter sequence so we split-off here too
                      {
                                    
                       int ctr=0; size_t i = 0;
                        
                        
                       for ( ; i<key.length() && i<prog.length();i++)
                       {
                           if (key[i] == prog[i]) ctr++;
                           else break;
                       }
                                    
                       if (ctr == key.length() && ctr <= prog.length() ) //prefix case: we are putting a prefix
                       {
                           current->marksEnd = true;
                           string earlier    = current->collap;
                          
                           ValueType  earliervalue = current->v;
                           current->v = tobeput;
                           current->collap = prog.substr(prog.find(earlier), ctr-prog.find(earlier));
                           
                           if (prog.substr(ctr)!="")
                           current->edges[translate(prog[ctr])] = new Node (prog.substr(ctr),earliervalue,true, current);
                           
                           return;
                       }
                                   
                                            //case when prog is a prefix of the key
                        if (key.find(prog) == 0 && current->edges[translate(key[ctr])] == nullptr)
                        {
                           current->edges[translate(key[ctr])] = new Node(key.substr(ctr), tobeput, true, current);
                           return;
                        }
                                    
                                    
                       int adj = (int)prog.size()-(int)current->collap.size();
      
                       string earlier    = current->collap;
                     
                        
                        current->collap   = current->collap.substr(ctr-adj);
       
                        Node* branch = new Node (earlier.substr(0,ctr-adj),ValueType(), false, current->parent);
                        
                        current->parent->edges[translate(earlier.substr(0,ctr-adj)[0])]  = branch;
                        
                        branch->edges[translate(current->collap[0])] = current;
                        
                        current->parent = branch;
                        
                        current = current->parent;
                
                                   
                        current->edges[translate(key[ctr])] = new Node(key.substr(ctr), tobeput, true, current);
                        
                        if (key.find(prog)== 0) current->marksEnd = true;
                        else current->marksEnd = false;
                        
                        return;
                                            
                                    
                       } //end of else block
                                    
                                   
                    }   //end of for loop
                            
                    current->marksEnd = true;
        
                    current->v = tobeput;
                
            }; //end of function
    
  
};
#endif /* TrialRad_hpp */
