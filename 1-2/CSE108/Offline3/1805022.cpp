#include<iostream>
using namespace std;

int getNumSize(int n){
    int sz = 0;
    while(n){
        sz++;
        n/=10;
    }
    //cout<<"numsize "<<sz<<endl;
    return sz;
}

bool okay(char *s){
    int sz = 0;
    while(s[sz]){
        if( s[sz]<'0' or s[sz]>'9' )
            return false;
        sz++;
    }
    return true;
}

class StringMath{
    char* p;
public:
    //Add necessary constructors and destructors and functions
    //...
    // empty constructor
    StringMath(){
        //cout<<"Initializing object with empty constructor"<<endl;
        p = new char[2];
        p[0] = '0';     //Initializing with zero
        p[1] = 0;
    }

    //contstructor with string
    StringMath(char* num){
        //cout<<"Initializing object with number constructor"<<endl;
        int sz = 0;
        while(num[sz])  //finding the size of string
            sz++;
        if( !okay(num)){
            cout<<"Not a valid number input"<<endl;
            p = new char[2];
            p[0] = '0';     //Initializing with zero
            p[1] = 0;
            return;
        }
        p = new char[sz+1];
        sz = 0;
        while(num[sz]){
            p[sz] = num[sz];    //copying the string to the variable p
            sz++;
        }
        p[sz] = 0;
    }

    //copy constructor
    StringMath(const StringMath &sm){
        int sz = 0;
        while(sm.p[sz])
            sz++;
        p = new char[sz+1];
        sz = 0;
        while(sm.p[sz]){
            p[sz] = sm.p[sz];
            sz++;
        }
        p[sz] = 0;
    }

    // to get the size of the numberstring
    int getSize(){
        int sz = 0;
        while(p[sz])
            sz++;
        return sz;
    }

    //Assignment operator
    StringMath operator=(StringMath sm){
        int sz = sm.getSize();
        delete[] p;
        p = new char[sz+1];
        for(int i=0;i<sz;i++)
            p[i] = sm.p[i];
        p[sz] = 0;
        return sm;
    }

    StringMath operator+(int num){

        if ( num<0 ){
            cout<<"Error! This library doesn't support negative number"<<endl;
            return *this;
        }
        int szthat = getNumSize(num)-1;
        char* numString = new char[szthat+2];
        for(int i=szthat;i>=0;i--){
            int d = num%10;
            num/=10;
            numString[i] = d+'0';
        }
        numString[szthat+1] = 0;
        StringMath res(numString);
        return *this+res;
    }

    StringMath operator+(StringMath sm){
        int szthis = this->getSize()-1;
        int szthat = sm.getSize()-1;
        int sz = 0;
        int mx = szthis;
        if( szthat>mx )
            mx = szthat;
        char* sum = new char[mx+3];
        sz = mx+1;
        int num = 0,carry = 0;
        while(szthis>=0 or szthat>=0){
            int thisdigit = 0;
            int thatdigit = 0;
            if( szthis>=0 )
                thisdigit = p[szthis] - '0';
            if( szthat>=0 )
                thatdigit = sm.p[szthat] - '0';
            num = thisdigit+thatdigit+carry;
            carry = num/10;
            num%=10;
            szthis--;
            szthat--;
            sum[sz--] = num+'0';
        }
        if( carry )
            sum[sz--] = carry+'0';
        sum[mx+2] = 0;
        while(sz>=0){
            sum++;
            sz--;
        }

        StringMath res(sum);
        return res;
    }

    // Relational operator
    bool operator>(StringMath & sm){
        if( sm.getSize()!=this->getSize() ){
            return this->getSize()>sm.getSize();
        }
        int sz = sm.getSize();
        for(int i=0;i<sz;i++){
            if( sm.p[i]!=this->p[i] ){
                return this->p[i]>sm.p[i];
            }
        }
        return false;
    }
    // comparision with num
    bool operator>(int num){
        if( num <0 ) return true;
        int szthat = getNumSize(num)-1;
        char* numString = new char[szthat+2];
        for(int i=szthat;i>=0;i--){
            int d = num%10;
            num/=10;
            numString[i] = d+'0';
        }
        numString[szthat+1] = 0;
        StringMath res(numString);
        return *this>res; // used the already declared comparator method
    }

    // post increament
    StringMath operator++(int x){
        StringMath temp = *this;
        *this = temp+1;
        return temp;
    }

    //useless print function
    void print(){
        int sz = 0;
        cout<<"The number is ";
        while(p[sz])
            cout<<p[sz++];
        cout<<endl;
    }

    //ostream method
    friend ostream& operator<<(ostream& os,StringMath &sm);
    friend StringMath operator+(int x,StringMath &sm);

    //destructor
    ~StringMath(){
        //cout<<"Deleting object"<<endl;
        delete[] p;
    }
};

ostream& operator<<(ostream& os,StringMath &sm){
    int sz = 0;
    os<<"The number is ";
    while(sm.p[sz])
        os<<sm.p[sz++];
    os<<endl;
    return os;
}

StringMath operator+(int num,StringMath &sm){
    int szthat = getNumSize(num)-1;
    char* numString = new char[szthat+2];
    for(int i=szthat;i>=0;i--){
        int d = num%10;
        num/=10;
        numString[i] = d+'0';
    }
    numString[szthat+1] = 0;
    StringMath res(numString);
    return sm+res;
}


int main(){
    StringMath S1;
    StringMath S2("123");
    StringMath S3("757");
    StringMath S4("220");
    StringMath S5;
    S5 = S2+S3;
    int n= 345;
    S4=S4;
    S1=S4;
    //Print the character string ofS1and S4
    cout<<S1<<S4;
    S1=S2+S3+S4;
    //Print the character string of S1, S2, S3 and S4, where S1 contains the character string: “1100”
    cout<<S1<<S2<<S3<<S4;

    S5=S4=S3;
    //Print the character string of S5, S4 and S3
    cout<<S5<<S4<<S3;
    if(S3 > n ){
        S5= S3+n;
    }
    // Print the character string of S5, where S5 contains the character string: “1102”
    cout<<S5;
    S5= n+S2;
    // Print the character string of S5, where S5 contains the character string: “468”
    cout<<S5;
    if(S5 > S2){
        S5++;
        //Assume prefix increment
    }
    // Print the character string of S5, where S5 contains the character string: “469”
    cout<<S5;
}
