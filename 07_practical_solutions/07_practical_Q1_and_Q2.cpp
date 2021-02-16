#include <iostream>
#include <string>
#include <vector>
using namespace std;


// QUESTION 1 CLASSES & FUNCTIONS 
class Date{
    protected: int d ; int m; int year; string date_string;
    public: 
    Date(int d1,int m1,int year1){
      date_string = to_string(d1)+"/"+to_string(m1)+"/"+to_string(year1);
    }
  };

class Blood:Date{
  protected: string dt; int sys; int dia;
  public:
  Blood(int nsys,int ndia,Date d): Date(d){
    dt=date_string;
    sys = nsys;
    dia = ndia;
  }
  void print(){cout<<sys<<"\t\t\t"<<"\t\t"<<dia<<"\t\t"<<dt<<endl;}
  friend class Patient;
};



class Patient{
  private:
  // main variables 
  string name;
  vector<Blood> records;
  // temporary variables
  vector<Blood> pressure_records;
  int hi_abnorm_id=-1;
  int hi_abnorm_val = 0;
  int sum_distolic; 
  
  public: 
  // constructor 
  Patient(string name1):
    name(name1){}

  //addRecord  
  void addRecord(Blood b){
    records.push_back(b);
  }
  //printReport
  void printReport(){
    // general overview 
    cout<<"\nPatient "<<name<<"\n"<<"systolic \t diastolic \t date"<<endl;
    for (int i = 0; i < records.size(); i++){
      sum_distolic += records[i].dia; 
      if (records[i].sys>140){
        if (records[i].sys>hi_abnorm_val){
          hi_abnorm_val=records[i].sys;
          hi_abnorm_id = i;}
      }
      cout << "\t"<<records[i].sys << "\t \t \t"<<records[i].dia<<"\t\t"<<records[i].dt<<endl;;
    }

    // specific information according to Q2: 

    //the highest abnormal systolic blood pressures, together with the corresponding diastolic value, and the day it has been measured;
    if (hi_abnorm_val==0){
      cout<<"\nno measurement was too high";}
      else {cout<< "\nHighest abnormal systolic blood pressure was " << records[hi_abnorm_id].sys << " the respective diastolic meassure was " << records[hi_abnorm_id].dia << " and it got recorded on the "<<records[hi_abnorm_id].dt <<endl;}
    
    // the average diastolic blood pressure
    cout << "\nThe average diastolic blood pressure was: " << sum_distolic/records.size()<<endl;
    
    // the list (possibly containing a single element) of pressure records for a patient whose systolic pressure is maximal
    cout <<"\nThese are the pressure records for "<<name<< " where the systolic pressure is max\n systolic \t diastolic \t date\n"; 
    for (int i = 0; i < records.size(); i++){
      if (records[i].sys==hi_abnorm_val){
        cout << "\t"<<records[i].sys << "\t \t \t"<<records[i].dia<<"\t\t"<<records[i].dt<<endl;;
      pressure_records.push_back(records[i]);}
    }
  }
};



// QUESTION 2 CLASSES & FUNCTIONS 
#include <iostream>
using namespace std; 

// exception methods
void FullStackException(){
  string msg = "This operation is not possible as the Stack is already full";
  cout<< msg;
};

void EmptyStackException(){
  string msg = "This operation is not possible as the Stack is empty";
  cout<< msg;
};


template<typename T>
class StackI {
  public:
    virtual void push(T t) = 0;
    virtual void pop() = 0;
    virtual T top() =0;
    virtual bool isEmpty() =0;
    virtual void print()=0;
};

template<typename T>
class Stack: public StackI <T> {
  private: 
    int nb_elem = 0;
    int size_arr = 0;
    T *myStack; 

  public: 
  // constructors 
    Stack(){            //default 
      myStack = new T[20];
      size_arr=20;
    }

    Stack(int n){myStack = new T[n]; size_arr=n;} //with given n 

    void push (T t){
      if (size_arr == nb_elem)
          FullStackException(); 
      else {
        myStack[size_arr-nb_elem] = t;
        nb_elem+=1;
      }}

    void pop(){
      if (isEmpty())
         EmptyStackException(); 
      else{
        nb_elem-=1; // it does not actualy need to be removed as we only look at the slice from length of array - nbelem until the end 
      }
    }

    T top(){
      if (0 == nb_elem)
         EmptyStackException(); 
      else {
        return myStack[nb_elem]; // it does not actualy need to be removed as we only look at the slice from length of array - nbelem until the end 
      }
    }

     bool isEmpty(){
       return (0 == nb_elem);
     }

    void print(){
      
      if (isEmpty())
         EmptyStackException(); 
      else{
        cout<<"\nThese are the stack element (left-most element = element on top of the stack and the right-most element = element at the bottom of the stack)\n";
        for (int i=1;i<=nb_elem;i++){ // needs to be changed later
          cout<<myStack[i]<<" ";
        }
        cout<<"\n";
      }
    }

    ~ Stack(){
      cout <<"\nDestructing Stack"<<endl;
      delete myStack;
    }
};


int main() {
  // QUESTION 1 main part (test code)
  Patient mary("Mary");
  mary.addRecord(Blood(94,61, Date(2,5,2013)));
  mary.addRecord(Blood(97,65, Date(3,5,2013)));
  mary.addRecord(Blood(144,99, Date(4,5,2013)));
  mary.addRecord(Blood(123,88, Date(5,5,2013)));
  mary.addRecord(Blood(177,110, Date(6,5,2013)));
  mary.addRecord(Blood(145,89, Date(7,5,2013)));
  mary.printReport();

  Patient john("John");
  john.addRecord(Blood(88,57,Date(15,5,2013)));
  john.addRecord(Blood(95,61,Date(16,5,2013)));
  john.addRecord(Blood(114,80,Date(17,5,2013)));
  john.addRecord(Blood(151,96,Date(18,5,2013)));
  john.addRecord(Blood(176,104,Date(19,5,2013)));
  john.addRecord(Blood(176,110,Date(20,5,2013)));
  john.printReport();

  // QUESTION 2 main part 
  cout<< "\n\n-----------------------------------------\n QUESTION 2 \n\n ";
  Stack<double> stacky(3);
  stacky.push(10);
  stacky.push(11);
  stacky.pop();
  stacky.push(230102310);
  stacky.push(23487);
  cout <<"what is on top: "<< stacky.top()<<endl;
  stacky.print();

}

