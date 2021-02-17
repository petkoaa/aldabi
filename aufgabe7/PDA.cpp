#include "PDA.hpp"
#include <vector>
#include <utility>


/// Constructor, which specifies which language to check (HAIRPIN by default)
/// and internally builds up the production rules
PDA::PDA(const Language l )
{
    language_ = l;
    

    if (l==Language::HAIRPIN) {
        
        stack_.push('S');

        std::map<std::pair<char, char>, std::pair<std::string, unsigned>> rules = {

              //          INPUT:             OUTPUT:
             //     { stack, string }     { push,  pop }
                { {'S', 'a'}, {"1u", 1} },
                { {'S', 'u'}, {"1a", 1} },
                { {'S', 'g'}, {"1c", 1} },
                { {'S', 'c'}, {"1g", 1} },

                { {'1', 'a'}, {"2u", 1} },
                { {'1', 'u'}, {"2a", 1} },
                { {'1', 'g'}, {"2c", 1} },
                { {'1', 'c'}, {"2g", 1} },

                { {'2', 'a'}, {"3u", 1} },
                { {'2', 'u'}, {"3a", 1} },
                { {'2', 'g'}, {"3c", 1} },
                { {'2', 'c'}, {"3g", 1} },

                { {'3', 'g'}, {"4a", 1} },

                { {'4', 'a'}, {"a", 1} },
                { {'4', 'c'}, {"a", 1} },

                { {'a', 'a'}, {"", 1} },
                { {'g', 'g'}, {"", 1} },
                { {'u', 'u'}, {"", 1} },
                { {'c', 'c'}, {"", 1} }


        };


        rules_ = rules;
    } else {

        std::map<std::pair<char, char>, std::pair<std::string, unsigned>> rules = {
             //          INPUT:             OUTPUT:
            //      { stack, string }     { push,  pop }
                { {')','('}, {")", 0} },
                { {')',')'}, {"", 1} },

                { {'X','('}, {")", 0} },
                { {'X',')'}, {"", 1} }   //fail
                

        };
        rules_ = rules;
    }


}



/// Read the next symbol and internally traverse states
/// If a fail state was reached in the previous call, the fail state will be maintained
/// @param a The symbol to read
/// @return current state of PDA
PDA::State PDA::next(const char a) {
    if(a=='$' && stack_.empty()) return State::SUCCESS;    // success only on empty stack and string
    else if(a=='$' && !stack_.empty()) return State::FAIL;
    else{

        std::pair<char,char> current;
        if (stack_.empty()) current = {'X', a } ; // X means the stack is empty
        else current = {stack_.top(), a};
        std::pair<std::string,State> match;

        // SEARCH A RULE IN THE GRAMMAR
        std::map<std::pair<char,char>, std::pair<std::string,unsigned>>::const_iterator got = rules_.find(current);
        if (got == rules_.end())     // if no rule in grammar -> Fail
            return State::FAIL;
        else{
            // RULE IS FOUND -> Handle popping and pushing

            // POPPING FROM THE STACK
            unsigned pop = got->second.second;
            for(unsigned i=0; i<pop; ++i)
            {
                if(stack_.empty()) return State::FAIL;  //grammar says pop but stack is empty -> Fail
                else stack_.pop();
            }
            
            // PUSHING TO THE STACK
            unsigned push = got->second.first.size();
            for(unsigned i=0; i<push; ++i )
            {
                char m = got->second.first[push-1-i];
                stack_.push(m);
            }


            return State::IN_PROGRESS;
        }
    }
    }

/// Reset the automaton to a state as if newly constructed
/// I.e. init stack and set state to s0 (IN_PROGRESS).
void PDA::reset(){
    while(!stack_.empty())
    {
        stack_.pop();
    }
    
    if (language_==Language::HAIRPIN)
        stack_.push('S');
    
}





