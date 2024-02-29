#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <func.hpp>

std::string TRASH;

using namespace std;

class Error {
public:
    Error() {
        this->ErrorReport();
    }
    void ErrorReport() {
        cout << "Error. Something goes wrong";
    }
};

class MyBook {
    string Author; 	//автор книги
    string Name;
    double Cost;
    unsigned int Year; 	//год издания
public:
    MyBook() {}

    MyBook(const MyBook& book) {
        Author = book.Author;
        Name = book.Name;
        Cost = book.Cost;
        Year = book.Year;
    }
    MyBook(string s) {
        Author = s;
        Name = "";
        Cost = 0.0;
        Year = 2000;
    }
    void input(istream& in) {
        getline(in, Author, '\n');
        getline(in, Name, '\n');
        in >> Cost >> Year;
        getline(in, TRASH);
    }

    void output (ostream& out) {
        out << Author << " " << Name << " " << Cost << " " << Year << endl;
    }

    string getAuthor() {
        return Author;
    }

    string getName() {
        return Name;
    }

    MyBook& operator= (const MyBook& book) {
        Author = book.Author;
        Name = book.Name;
        Cost = book.Cost;
        Year = book.Year;
        return *this;
    }

    friend bool operator> (const MyBook& book1, const MyBook& book2) {
        if (book1.Author > book2.Author)
            return true;
        else if (book1.Author == book2.Author && book1.Name > book2.Name)
            return true;
        else if (book1.Author == book2.Author && book1.Name == book2.Name)
            return false;
        else if (book1.Author == book2.Author && book1.Name < book2.Name)
            return false;
        else if (book1.Author < book2.Author)
            return false;
        else
            cout << "\nError. Something goes wrong with \">\". \n";
        return false;
    }

    friend bool operator< (const MyBook& book1, const MyBook& book2) {
        if (book1.Author > book2.Author)
            return false;
        else if (book1.Author == book2.Author && book1.Name > book2.Name)
            return false;
        else if (book1.Author == book2.Author && book1.Name == book2.Name)
            return false;
        else if (book1.Author == book2.Author && book1.Name < book2.Name)
            return true;
        else if (book1.Author < book2.Author)
            return true;
        else
            cout << "\nError. Something goes wrong with \">\". \n";
        return false;
    }

    friend bool operator!= (const MyBook& book1, const MyBook& book2) {
        if (book1.Author != book2.Author || book1.Name != book2.Name)
            return true;
        else
            return false;
    }
};

class MyShelf {
    vector<MyBook> myShelf;
public:
    MyShelf() {}

    MyShelf(const MyShelf& sh) {
        myShelf = sh.myShelf;
    }

    MyShelf(const MyShelf& sh, int i, int j) {
        if (i >= 0 && i < (int)sh.myShelf.size()) {
            while (i <= j) {
                this->myShelf.push_back(sh.myShelf[i]);
                i++;
            }
        }
        else {
            cout << "Array index out of bounds. Returning full copy...";
            myShelf = sh.myShelf;
        }
    }

    int size() {
        return myShelf.size();
    }

    void AddBooks(istream& in) {
        MyBook book;
        int n;
        in >> n;
        getline(in, TRASH);
        for(int i = 0; i < n; i++) {
            book.input(in);
            myShelf.push_back(book);
        }
    }

    void OutputShelf(ostream& out) {
        for (int i = 0; i < (int)myShelf.size(); i++) {
            MyBook book = myShelf[i];
            book.output(out);
        }
    }

    MyBook getBook(int a) {
        if (a >= 0 && a < (int) myShelf.size())
            return myShelf[a];
        else
            return myShelf[0];
    }

    void Swap(int a, int b) {
        if (a < 0 || b < 0 || a >= (int)myShelf.size() || b >= (int)myShelf.size())
            cout << "\nThere aren't such elements as " << a + 1 << " or " << b + 1 << ".\n";
        else
            func::swap(myShelf[a], myShelf[b]);
    }

    void sortShelf() {
        //func::QuickSort(0, myShelf.size() - 1, myShelf);
        sort(myShelf.begin(), myShelf.end());
    }

    void sortShelf(int L, int R) {
        func::QuickSort(L, R, myShelf);
    }

    int SearchBook(MyBook book) {
        return func::BinarySearch(0, myShelf.size() - 1, myShelf, book);
    }

    bool cmp_bookAuthor(MyBook* element, MyBook* const value) {
        if (element->getAuthor() < value->getAuthor())
            return true;
        else
            return false;
    }

    MyShelf AuthorSearch(string &s) {
        int i = 0;
        while (i + 1 <= (int)myShelf.size() - 1) {
            if (s == myShelf[i].getAuthor())
                break;
            i++;
        }
        if (s != myShelf[i].getAuthor()) {
            MyShelf BooksWithOneAuthor;
            return BooksWithOneAuthor;
        }
        else {
            int j = i;
            while (s == myShelf[j].getAuthor()) {
                if (j + 1 <= (int)myShelf.size() - 1)
                    j++;
                else {
                    MyShelf BooksWithOneAuthor(*this, i, j);
                    return BooksWithOneAuthor;
                }
            }
            MyShelf BooksWithOneAuthor(*this, i, j-1);
            return BooksWithOneAuthor;
        }
        /*MyBook book(s);
        auto i = lower_bound(myShelf.begin(), myShelf.end(), &book, cmp_bookAuthor);
        auto j = upper_bound(myShelf.begin(), myShelf.end(), &book, cmp_bookAuthor);
        int start = distance(myShelf.begin(), i);
        int end = start + distance(i, j);
        MyShelf BookWithOneAuthor(*this, start, end);  //ошибка с типом iterator. Как с ним работать?
        return BookWithOneAuthor;*/
    }

    MyShelf& operator= (const MyShelf& shelf) {
        for (int i = 0; i < (int)shelf.myShelf.size(); i++) {
            myShelf[i] = shelf.myShelf[i];
        }
        return *this;
    }
};

class Library {
    vector<MyShelf> myLib;
public:
    Library() {}
    Library(const Library& Lib) {
        for (int i = 0; i < (int)Lib.myLib.size(); i++) {
            myLib[i] = Lib.myLib[i];
        }
    }
    void push_back(MyShelf& shelf) {
        myLib.push_back(shelf);
    }
    void InputLib(istream& in) {
        int n;
        in >> n; in.ignore();
        for (int i = 0; i < n; i++) {
            MyShelf shelf;
            shelf.AddBooks(in);
            push_back(shelf);
        }
    }
    void OutputLib(ostream& out) {
        for (int i = 0; i < (int)myLib.size(); i++) {
            cout << i + 1 << ": ";
            myLib[i].OutputShelf(out);
            cout << endl;
        }
    }
    void OutputLib(ostream& out, int n) {
        myLib[n].OutputShelf(out);
    }
    void SortAllShelfs() {
        for (int i = 0; i < (int)myLib.size(); i++) {
            myLib[i].sortShelf();
        }
    }
    void SortShelf(int a) {
        myLib[a].sortShelf();
    }

    void AuthorSearch(string &s, ostream& out) {
        int k = 0;
        while (k <= (int)myLib.size() - 1) {
            if (myLib[k].AuthorSearch(s).size() > 0) {
                cout << k + 1 << " :\n";
                myLib[k].AuthorSearch(s).OutputShelf(out);
                k++;
            }
            else
                k++;
            continue;
        }
    }
};

void shelfSolution() {
    MyShelf shelf;
    ifstream in ("in.txt");
    if(!in.is_open()){
        Error();
    }
    shelf.AddBooks(in);
    shelf.OutputShelf(cout);
    cout << "\nSorted Shelf:_________________________________________ \n";
    shelf.sortShelf();
    shelf.OutputShelf(cout);

    string s;
    getline(cin, s);
    cout << endl;
    MyShelf AuthorShelf = shelf.AuthorSearch(s);
    if (AuthorShelf.size() == 0) {
        cout << "There isn't such books";
    }
    else {
        AuthorShelf.OutputShelf(cout);
    }
}

void LibSolution() {
    Library lib;
    ifstream in ("inLibrary.txt");
    lib.InputLib(in);
    cout << "_________________________________________________________\n";
    lib.OutputLib(cout);
    lib.SortAllShelfs();
    cout << "\nSorted Library:_________________________________________ \n";
    lib.OutputLib(cout);
    string s;
    cout << endl << "Enter author to search: \n";
    getline(cin, s);
    cout << s << " wrote this books: \n";
    lib.AuthorSearch(s, cout);
}

int main() {
    shelfSolution();
    cin.get();
    LibSolution();
    return 0;
}
