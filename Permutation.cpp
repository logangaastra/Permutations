#include <cmath>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;



/** Permutation of the first n integers (starting with zero)
  * Example 0->1 1->2 2->0 3->3
  * Stores in an unordered_map
  * If integer maps onto itself, then it is not added to the map
  * This allows variable sized permutations, as any integer not
  *   included is assumed to be mapped to itself
  * The size is included to indicate the largest key in perm, or
  *   the largest integer not mapping to itself. If there are no such
  *   integers, then size = 0
*/
class Permutation {
    //PRIVATE MEMBER VARIABLES==================================================
    unordered_map<int, int> perm;
    int size;
    
public:
    const int DEFAULT_SIZE = 0;
    const int MINIMUM_ELEMENT = 0;
    //CONSTRUCTORS==============================================================
    /** Default Constructor constructs identity permutation
      */
    Permutation() {
        size = DEFAULT_SIZE;
    }
    /** Constructor taking in vector of ints
      * These ints represent the values that the index they are at
      *   maps to in the desired permuatation.
      * Example: if you want 0->0, 1->2, 2->3, 3->1, 4->4, 5->6, 6->5, 
      *  your vector should be {2, 3, 1, 4, 6, 5}
      * Sets size to the size of integerMap
      */
    Permutation(vector<int> integerMap) {
        if(!isIntegerMap(integerMap)) {
            cerr << "Error: invalid vector passed to Permutation " <<
                "constructor" << endl;
            size = DEFAULT_SIZE;
            return;
        }
        size = 0;
        for(int i = 0; i < integerMap.size(); ++i) {
            perm.emplace(i, integerMap.at(i));
            if(i != integerMap.at(i))
                size = i + 1;
        }
    }
    /** The above constructor, but takes in arrays of ints instead of vectors of
      *   ints
      */
    Permutation(int * integerMap, int sz) 
        : Permutation(vector<int>(integerMap, integerMap + sz)){}
    /** Constructor taking in vectors of vectors of ints representing
      *   cycles for a permutation
      * Example: {{1,3,2}{4}{5,6}} gives the integerMap
      *   1->3 2->1 3->2 4->4 5->6 6->5
      */
    Permutation(vector<vector<int>> cycles) {
        size = DEFAULT_SIZE;
        if(!areDisjointCycles(cycles)) {
            cerr << "Error: invalid cycles passed to Permutation " <<
                "constructor" << endl;
            return;
        }
        for(int i = 0; i < cycles.size(); ++i) {
            if(cycles[i].size() <= 1)
                continue;
            for(int j = 0; j < cycles[i].size(); ++j) {
                perm.emplace(cycles[i][j], cycles[i]
                    [(j + 1) % cycles[i].size()]);
                size = max(size, cycles[i][j] + 1);
            }
        }
    }
    //OPERATORS=================================================================
    /** Overloads operator[] to return the number mapped to by i
      */
    int operator[](int i) const {
        return (perm.count(i) == 1 ? perm.at(i) : i);
    }
    /** Overloaded operator* to return a Permutation which is
      *  the composition of this and rhs
      * Example this = 1->2 2->3 3->4 4->1
      *  rhs = 1->2 2->3 3->1
      * this * rhs = 1->3 2->4 3->1 4->2
      */
    Permutation operator*(const Permutation& rhs) {
        int newSize = max(size, rhs.size);
        vector<int> composition;
        for(int i = 0; i < newSize; ++i) {
            int temp = rhs[i];
            temp = (*this)[temp];
            composition.push_back(temp);
            
        }
        return Permutation(composition);
    }
    /* Overloaded operator<< to return output as specified in printOneLine
     */
    friend ostream& operator<<(ostream& os, const Permutation& rhs) {
        rhs.printOneLine(os);
        return os;
    }
    //GETTERS===================================================================
    int getSize() const {
        return size;
    }
    /* Returns a vector of vector of ints with each vector representing a cycle
     * This is the unique cyclical form of Permutation, with the least integer
     *   in a cycle being the first listed and the cycles listed in order of
     *   least first entry
     * Does not include singletons i.e. 1-cycles if includeSingletons is false
     * Example: given 1->3 2->1 3->2 4->4 5->6 6->5 and false
     *   will return {1,3,2},{5,6}
         given 1->3 2->1 3->2 4->4 5->6 6->5 and true
         will return {1,3,2},{4},{5,6}
     */
     vector<vector<int>> getCycles(bool includeSingletons) const {
        //Keeps track of which numbers have been used already
        unordered_map<int, bool> alreadyUsed;
        vector<vector<int>> cycles;
        for(int i = 0; i < size; ++i) {
            //Check for singletons
            if(i == (*this)[i] && !includeSingletons)
                continue;
            if(alreadyUsed.count(i) == 1)
                continue;
            vector<int> newCycle;
            newCycle.push_back(i);
            alreadyUsed.emplace(i, true);
            int nextNumber = (*this)[i];
            while(nextNumber != i) {
                newCycle.push_back(nextNumber);
                alreadyUsed.emplace(nextNumber, true);
                nextNumber = (*this)[nextNumber];
                
            }
            cycles.push_back(newCycle);
        }
        return cycles;
    }
    /* Returns the Permutation that when composed with this permutation
     *   returns the identity, i.e. the permutation that maps every integer
     *   onto itself.
     * Example: (2, 3, 1) returns (3, 1, 2)
     */
    Permutation getInverse() const {
        vector<int> inverseMap = vector<int>(size, -1);
        for(int i = 0; i < size; ++i)
            inverseMap[(*this)[i]] = i;
    }
    /* Returns true iff Permutation is a derangement, e.g. there are no 1 cycles
     * Example: (2, 3, 1) is a derangement, (3, 2, 1) is not
     */
    bool isDerangement() const {
        for(int i = 0; i < size; ++i) {
            if((*this)[i] == i)
                return false;
        }
        return true;
    }
    int getNumberOfCycles() {
        return getCycles(true).size();
    }
    /* returns number of n-cycles in Permutation
     */
    int getNumberOfCycles(int n) {
        vector<vector<int>> cycles = getCycles(true);
        int count = 0;
        for(int i = 0; i < cycles.size(); ++i)
            count += (cycles.size() == n ? 1 : 0);
        return count;
    }
    //PRINT FUNCTIONS===========================================================
    /* Prints the Permutation in one line notation
     * Does not include newLine at the end
     */
    void printOneLine(ostream& os) const {
        if(size == 0) {
            os << "()";
            return;
        }
        os << "(" << (*this)[0];
        for(int i = 1; i < size; ++i) 
            os << ", " << (*this)[i];
        os << ")";
    }
    /* prints the Permutation in Two line notation 
     * Takes up 2 lines(obviously) and includes a newLine at the end
     */
    void printTwoLine(ostream &os) {
        if(size == 0) {
            os << "[]\n[]\n";
            return;
        }
        os << "[";
        for(int i = 0; i < size; ++i) 
            os << setw(maximumNumberOfSpaces()) << i;
        os << "]\n[";
        for(int i = 0; i < size; ++i) 
            os << setw(maximumNumberOfSpaces()) << (*this)[i];
        os << "]" << endl;
    }
    /* Prints to os the cycles as specified in getCycles
     * Does not print newLine afterwards
     */
    void printCycles(ostream &os, bool includeSingletons) {
        vector<vector<int>> cycles = getCycles(includeSingletons);
        for(int i = 0; i < cycles.size(); ++i) {
            os << "(" << cycles[i][0];
            for(int j = 1; j < cycles[i].size(); ++j)
                os << " " << cycles[i][j];
            os << ")";
        }
    }
private:
    //PRIVATE MEMBER FUNCTIONS==================================================
    /** Checks that integerMap satisfies the following:
      * 1. all entries are contained in [0,integerMap.size() - 1]
      * 2. all non negative integers less than integerMap.size() are
      *    in integerMap
      * Returns true if integerMap satisfies the above
      */
    bool isIntegerMap(vector<int> integerMap) {
        vector<int> testMap = integerMap;
        sort(testMap.begin(), testMap.end());
        for(int i = 0; i < testMap.size(); ++i) {
            if(testMap.at(i) != i)
               return false;
        }
        return true;
    }
    /** Checks that the cycles in cycles are disjoint i.e. that they
      *   have no common elements with each other or themselves
      */
    bool areDisjointCycles(vector<vector<int>> cycles) {
        unordered_map<int, bool> isUsed;
        for(int i = 0; i < cycles.size(); ++i) {
            for(int j = 0; j < cycles.at(i).size(); ++j) {
                if(isUsed.count(cycles.at(i).at(j)) == 1)
                    return false;
                isUsed.emplace(cycles.at(i).at(j), false);
            }
        }
        return true;
    }
    /* Returns the maximum number of spaces a integer less than size will take
     * up when printed out in base 10 plus 1
     */
    int maximumNumberOfSpaces() {
        int maxNumberOfSpaces = 1;
        while(size >= pow(10, maxNumberOfSpaces))
            ++maxNumberOfSpaces;
        return ++maxNumberOfSpaces;
    }
};
