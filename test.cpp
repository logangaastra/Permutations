int main()
{
    cout << "Begin testing Permutation.cpp" << endl;
    cout << "Testing default constructor" << endl;
    Permutation p1 = Permutation();
    if(p1.getSize() != p1.DEFAULT_SIZE) {
        cout << "Error: default constructor should set size to DEFAULT_SIZE"
          << endl;
        return 1;
    }
    cout << "Printing One Line" << endl;
    cout << p1 << endl;
    cout << "Printing Two Line" << endl;
    p1.printTwoLine(cout);
    cout << "Note: Both will depend on DEFAULT_SIZE variable in Permutation" 
      << endl;
    cout << "Default constructor testing complete!" << endl;
    cout << "Testing vector constructor" << endl;
    Permutation p2 = Permutation({1,2,4,0,3});
    if(p2.getSize() != 5) {
        cout << "Error: vector constructor returns wrong size" << endl;
        return 1;
    }
    cout << "Printing One Line" << endl;
    cout << p2 << endl;
    cout << "Target: (1, 2, 4, 0, 3)" << endl;
    cout << "Printing Two Line" << endl;
    p2.printTwoLine(cout);
    cout << "Target:" << endl;
    cout << "[ 0 1 2 3 4]\n[ 1 2 4 0 3]" << endl;
    cout << "Vector constructor testing complete!" << endl;
    cout << "All testing complete!" << endl;
    return 0;
}
