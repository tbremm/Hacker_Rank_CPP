// https://www.hackerrank.com/challenges/virtual-functions/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
    private:
        string name;
        int age;

    public:
        virtual void getdata() {};
        virtual void putdata() {};

        string getName() { return name; }

        int getAge() { return age; }

        void setName(string n) { name = n; }

        void setAge(int a) { age = a; }

};

class Professor : public Person {
    private:
        static int cur_id;
        int id;
        int pubs;
    
    public:
        Professor() { cur_id++; }

        void getdata() {
            string n = "";
            int a = 0;
            cin >> n >> a >> pubs;
            setName(n);
            setAge(a);
            id = cur_id;
        }

        void putdata() {
            cout << getName() << " " << getAge() << " " << pubs << " " << id << endl;
        }
};

int Professor::cur_id = 0;

class Student : public Person {
    private:
        static int cur_id;
        int id;
        int marks[6];
    
    public:
        Student() { cur_id++; }

        void getdata() {
            string n = "";
            int a = 0;
            cin >> n >> a;
            for (int i = 0; i < 6; i++) {
                cin >> marks[i];
            }
            setName(n);
            setAge(a);
            id = cur_id;
        }

        void putdata() {
            int sum = 0;
            for (int i = 0; i < 6; i++) {
                sum += marks[i];
            }
            cout << getName() << " " << getAge() << " " << sum << " " << id << endl;
        }
};

int Student::cur_id = 0;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}