#include<bits/stdc++.h>
using namespace std;

class Student{
    int studId;
  public:  Student(int id){
        studId=id;
    }
    int getId(){
        return studId;
    }
};
class Book{
   string name;
   set<int> issued;
   set<int> available;

  public:  Book(string name){
   this->name=name;
  } 
  int isAvail(string name){
    if(!available.empty()){
        int k=*available.begin();
        available.erase(k);
         issued.insert(k);
        return k;
    }
    return -1;
   }
   void addCopy(int id){
         available.insert(id);
         return;
   }
   void removeFromCopy(int id){
        issued.erase(id);
        available.insert(id);
   }
};

class Library{
  
    map<Student*,int> mp;
    map<string, Book*> books;
    map<int,Book*> copyToBook;//bookId ,aur book ka referencee store krega
          int nextId=1;
    public: 
    void issueBook(string BookN, Student* stud){
              if(mp.find(stud)!=mp.end()){
                cout<<"Student already has the book,so no book will be given for now"<<endl;
                return;
              }
              if(books.find(BookN)!=books.end()){
                Book *b=books[BookN];
                int k=b->isAvail(BookN);
                      

               if(k==-1) {cout<<"book currently unavailable,visit aferewards"<<endl;
               return;}
                mp[stud]=k;
               cout<<"Issued bookId is:"<<k<<" to student "<< stud->getId()<<endl;
              }else{
                cout<<"this book is not present in the libraray"<<endl;
              }
            }
       
    void returnBook(Student *stud, int id){
        if(mp.find(stud)==mp.end() || mp[stud]!=id){
            cout<<"This copy was not issued to this student"<<endl;
            return;
        }
          copyToBook[id]->removeFromCopy(id);
          mp.erase(stud);
          cout<<"Student"<< stud->getId()<< " returned book id "<<id<<endl;
    }
         
int addBook(string name){
    if(books.find(name)==books.end()){
        Book *b=new Book(name);
        books[name]=b;
    }
    Book *b=books[name];//isse nayi almirah nhi bnti ,purani almirah hi return hoti h
        int id=nextId++;
        b->addCopy(id);
        copyToBook[id]=b;
        return id;
    
}

};
// class Librarian{
// Library &library;// this is a assocaition relarionship, it can access all the methods of the library class

// public: Librarian(Library& lib){
//     library=lib;
//     //giving access to the library through this function,
//     // this may be required or may not be required at all
// }

// };
int main(){
    Library lib;
//    Librarian lb(lib);

    Student s1(1),s2(2),s3(3);
     lib.addBook("Insects");
    lib.addBook("Insects");
    lib.addBook("Animals");

        lib.issueBook("Insects",&s1);
    lib.issueBook("Insects",&s1);
    lib.issueBook("Insects",&s2);
    lib.issueBook("Insects",&s3);
    lib.issueBook("Birds",&s3);
    lib.returnBook(&s2,1);
    lib.returnBook(&s1,1);
    lib.issueBook("Insects",&s3);
    return 0;


}