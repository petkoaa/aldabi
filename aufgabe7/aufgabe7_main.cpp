#include "PDA.hpp"
#include <iostream>



int main(int argc, char* argv[])
{
    if (argc==2)
    {

        std::string rna = argv[1];
        
        PDA:: Language a = PDA::Language::HAIRPIN;

        for(unsigned i=0; i<rna.size(); ++i)
        {
            if(rna[i] == ')' || rna[i] == '(') 
            {
                a = PDA::Language::BRACKETS;

                std::string new_string;
                for(unsigned j=0; j<rna.size(); ++j)
                {
                    if(rna[j]=='(' || rna[j]==')')
                    {
                        new_string += rna[j];
                    }
                } 

                rna = new_string;
                break;
            }
        }
        rna += '$';

        PDA automat(a);

        unsigned i = 0;
        PDA::State state = PDA::State::IN_PROGRESS;
        while(state == PDA::State::IN_PROGRESS && i<rna.size() )
        {
            char ch = rna[i];
            state = automat.next(ch);
            ++i;
        }

        if(state == PDA::State::SUCCESS)
        {
            std::cout<<"SUCCESS";
            return 0;
        }else{
            std::cout<<"FALIL";
            return 1;
        }


    }
}