int main()
{
    cout << "Test 1 ----" << endl;
    cout << "Begin testing constructors" << endl;
    Permutation perm1 = Permutation();
    
    Permutation perm2 = Permutation({3,2,1,0});
    vector<vector<int>> cycles;
    vector<int> cycle1, cycle2, cycle3;
    cycle1.push_back(1);
    cycle1.push_back(2);
    cycle1.push_back(7);
    cycle2.push_back(5);
    cycle3.push_back(19);
    cycle3.push_back(4);
    cycles.push_back(cycle1);
    cycles.push_back(cycle2);
    cycles.push_back(cycle3);
    Permutation perm3 = Permutation(cycles);
    
    cout << "Size: " << perm2.getSize() << endl; 
    cout << "Target: " << "(3, 2, 1, 0)" <<endl;
    perm2.printOneLine(cout);
    cout << endl;
    perm2.printTwoLine(cout);
    perm2.printCycles(cout, true);
    cout << endl;
    perm2.printCycles(cout, false);
    cout << endl;
    cout << "perm3\nsize: " << perm3.getSize() << endl; 
    perm3.printOneLine(cout);
    cout << endl;
    perm3.printTwoLine(cout);
    perm3.printCycles(cout, true);
    cout << endl;
    perm3.printCycles(cout, false);
    cout << endl;
    cout << "Test 1 complete" << endl;
    cout << "Test 2 ----" << endl;
    Permutation perm4 = Permutation({1,2,0});
    Permutation perm5 = perm4 * perm4;
    perm4.printOneLine(cout); 
    cout << " * ";
    perm4.printOneLine(cout);
    cout << " = ";
    perm5.printOneLine(cout);
    cout << endl;
    cout << "Test 2 complete";
    return 0;
}
