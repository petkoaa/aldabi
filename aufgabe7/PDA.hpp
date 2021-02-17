#pragma once
#include <vector>
#include <stack>
#include <map>
#include <utility>
#include <string>


class PDA
{
public:
    // as always: do NOT change the public interface
        
    
    enum class Language {
      HAIRPIN, ///< accepts RNA Hairpins
      BRACKETS ///< Zusatzaufgabe
    };

    enum class State {
      IN_PROGRESS = 0, ///< sequence is valid so far, but not complete
      SUCCESS = 1,     ///< currently in accepting state, i.e. stack is empty after reading final $ symbol
      FAIL = 2         ///< sequence is not in language
    };

    /// Constructor, which specifies which language to check (HAIRPIN by default)
    /// and internally builds up the production rules
    PDA(const Language l = Language::HAIRPIN);
    
    /// Read the next symbol and internally traverse states
    /// If a fail state was reached in the previous call, the fail state will be maintained
    /// @param a The symbol to read
    /// @return current state of PDA
    State next(const char a);
    
    /// Reset the automaton to a state as if newly constructed
    /// I.e. init stack and set state to s0 (IN_PROGRESS).
    void reset();

    
protected:
    Language language_ = Language::HAIRPIN;         // save language

    std::map<std::pair<char,char>, std::pair<std::string,unsigned >> rules_;   // Grammar rules

    std::stack<char> stack_;   // Stack

};

