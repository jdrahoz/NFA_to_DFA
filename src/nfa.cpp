
// --------------------------------------------------- //
// julia drahozal 2441134
// eecs 665
// assignment 1: nfa2dfa
//
// nfa.cpp
// implementation file for nfa class
// --------------------------------------------------- //


// includes
#include "nfa.h"


// --------------------------------------------------- //
// constructor & destructor
// --------------------------------------------------- //


NFA :: NFA ()
{
	m_initial_state = parseInitialState ();
	m_final_states = parseFinalStates ();
	m_num_states = parseNumStates ();
	m_input_symbols = parseInputSymbols ();
	m_num_input_symbols = m_input_symbols.size ();
	m_transition_table = parseTransitionTable ();
}

NFA :: ~NFA () {}


// --------------------------------------------------- //
// getters & setters
// --------------------------------------------------- //


int NFA :: getInitialState ()
{
	return m_initial_state;
}

vector <int> NFA :: getFinalStates ()
{
	return m_final_states;
}

vector <char> NFA :: getInputSymbols ()
{
	return m_input_symbols;
}

int NFA :: getNumInputSymbols ()
{
	return m_num_input_symbols;
}

vector <vector <vector <int> > > NFA :: getTransitionTable ()
{
	return m_transition_table;
}


// --------------------------------------------------- //
// parsing methods
// --------------------------------------------------- //


int NFA :: parseInitialState ()
{
	// Initial State: {X}

	// get input
	string input;
	getline (cin, input);

	// pull out initial state
	string word;
	int word_count = 1;
	istringstream iss (input, istringstream::in);
	while (iss >> word)
	{
		if (word_count == 3)
		{
			// remove brackets
			word.erase (remove (word.begin (), word.end (), '{'), word.end ());
			word.erase (remove (word.begin (), word.end (), '}'), word.end ());
			return stoi (word);
		}
		word_count++;
	}
	return 0;
}

vector <int> NFA :: parseFinalStates ()
{
	// Final States: {X,X,X}

	vector <int> final_states;

	// get input
	string input;
	getline (cin, input);

	// pull out final states
	string word;
	int word_count = 1;
	istringstream iss (input, istringstream::in);
	while (iss >> word)
	{
		if (word_count == 3)
		{
			// remove brackets
			word.erase (remove (word.begin (), word.end (), '{'), word.end ());
			word.erase (remove (word.begin (), word.end (), '}'), word.end ());

			// add to vector
			int state;
			stringstream ss (word);
			while (ss >> state)
			{
				final_states.push_back (state);
				if (ss.peek () == ',')
				{
					ss.ignore ();
				}
			}
		}
		word_count++;
	}
	return final_states;
}

int NFA :: parseNumStates ()
{
	// Total States: X

	// get input
	string input;
	getline (cin, input);

	// pull out total num states
	string word;
	int word_count = 1;
	istringstream iss (input, istringstream::in);
	while (iss >> word)
	{
		if (word_count == 3)
		{
			return stoi (word);
		}
		word_count++;
	}
	return 0;
}

vector <char> NFA :: parseInputSymbols ()
{
	// State \t X \t X \t E

	vector <char> input_symbols;

	// get input
	string input;
	getline (cin, input);

	// pull out input symbols
	string word;
	int word_count = 1;
	istringstream iss (input, istringstream::in);
	while (iss >> word)
	{
		// add to vector
		if (word_count > 1)
		{
			input_symbols.push_back (word[0]);
		}
		word_count++;
	}
	return input_symbols;
}

vector <vector <vector <int> > > NFA :: parseTransitionTable ()
{
	// I1 \t {X} \t {X} \t {X}

	vector <vector <vector <int> > > transition_table;

	// get input
	string input;
	while (getline (cin, input))
	{
		// pull out transitions
		string word;
		vector <vector <int> > state;
		int word_count = 1;
		istringstream iss (input, istringstream::in);
		while (iss >> word)
		{
			if (word_count > 1)
			{
				vector <int> transitions;

				// remove brackets
				word.erase (remove (word.begin (), word.end (), '{'), word.end ());
				word.erase (remove (word.begin (), word.end (), '}'), word.end ());

				// add to vector
				int t;
				stringstream ss (word);
				while (ss >> t)
				{
					transitions.push_back (t);
					if (ss.peek () == ',')
					{
						ss.ignore ();
					}
				}
				state.push_back (transitions);
			}
			word_count++;
		}
		transition_table.push_back (state);
	}
	return transition_table;
}
