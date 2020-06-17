// https://www.hackerrank.com/challenges/box-it/problem

#include<bits/stdc++.h>

using namespace std;
//Implement the class Box  
//l,b,h are integers representing the dimensions of the box

class Box {
    public:
        Box() {
            l = 0;
            b = 0;
            h = 0;
        }

        Box(int length, int breadth, int height) {
            l = length;
            b = breadth;
            h = height;
        }

        Box(Box &box) {
            l = box.getLength();
            b = box.getBreadth();
            h = box.getHeight();
        }

        int getLength() {
            return l;
        }

        int getBreadth() {
            return b;
        }

        int getHeight() {
            return h;
        }

        long long CalculateVolume() {
            return static_cast<long long>(l) * b * h;
        }

        bool operator<(Box& B) {
			if (l < B.getLength()) {
				return true;
			} else if (b < B.b && l == B.getLength()) {
				return true;
			} else if (h < B.getHeight() && b == B.getBreadth() && l == B.getLength()) {
				return true;
			} else {
				return false;
			}
		}

        friend ostream& operator<<(ostream& out, const Box& B) {
			out << B.l << " " << B.b << " " << B.h;
			return out;
		}

    private:
        long l;
        long b;
        long h;
};

void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}