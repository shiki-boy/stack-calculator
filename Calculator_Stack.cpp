#include<iostream>
#include<string.h>
#include<cstdlib>
#include<vector>
#include<stack>
#include<math.h>
using namespace std;

float tonumber(string a){
	return atof(a.c_str());          // converts in const char *
}
bool in(char x,string a) {
    if(a.find(x,0) > a.length())
        return false;
    else
        return true;
}

bool check_precedence(char a, char b);
void doPostfix(string a,string &b);
float doOperation(float,float,char);


int main(){

	string a,a1;
	a1 = "(";
	for(int i=0;;i++){
		if(a == "=")
			break;
		cin>>a;
		a1 = a1+a;
	}
	a1[a1.size()-1] = ')';
	cout<<a1<<endl;

    cout<<endl;
    string p = a1;            // a1 is the input string..................
    string y;
    float n;
    vector <float> numbers;
    for(int i=0;i<p.size();i++){
        if( p[i] == '(' || p[i] == ')' )
            continue;
        if(isdigit(p[i]) || p[i] == '.')
            y = y + p[i];

        else if( !isalnum(p[i]) ){
            n = tonumber(y);
            numbers.push_back(n);
            y="";
        }

    }
    n = tonumber(y);            // for the last number
    numbers.push_back(n);

    string o;
    doPostfix(p,o);
    cout<<endl<<o<<endl;
    string nc;
    int counter=0;
    float n1,n2;
    stack <float> finalStack;
    for(int i=0;i<o.length();i++){
        string operators = "-+*/^";
        nc = nc + o[i];
        if(tonumber(nc) == numbers[counter] && counter<numbers.size()){
            finalStack.push(numbers[counter]);
            counter++;
            nc="";
        }
        if(in(o[i],operators)){
            // pop last two numbers
            n1 = finalStack.top();
            finalStack.pop();
            n2 = finalStack.top();
            finalStack.pop();
            float answer = doOperation(n2,n1,o[i]);
            finalStack.push(answer);
            nc="";
        }
    }
    cout<<endl<<"ANSWER IS ... "<<finalStack.top();
    return 0;
}


void doPostfix(string a, string &b){
    stack <int> S;
    string x = a;
    string operators = "+-*/^";

        for(int i=0;i<x.length();i++){

        if(x[i] == '('){
            S.push(x[i]);}

        else if( in(x[i] , operators) ){
            check_again:
                if (check_precedence(x[i] , S.top() )){
                    S.push(x[i]);
                 }
                else{
                    b = b + (char)S.top();
                    S.pop();
                    goto check_again;
                }
          }

        else if( x[i] == ')'){

            while(S.top() != '('){
                b=b+(char)S.top();
                S.pop();
            }
           S.pop(); // removes the left bracket
        }

        else{                   // for numbers
            b = b + x[i];
        }



    }

}

bool check_precedence(char a, char b){
    if( b=='(' || b==')')
        return true;

    string x = "-+__*/__^";
    int p1 = x.find(a,0);

    int p2 = x.find(b,0);
    if(p1 - p2 < 0 )
        return false;
    else if(p2 - p1 == 1 || p1 - p2 == 1)
			return false;
	else if(p1 - p2 > 2 )
		return true;
	else if(p1 == p2)
		return false;

}

float doOperation(float n1,float n2,char c){
    if(c == '+')
        return (n1+n2);
    if(c == '-')
        return (n1-n2);
    if(c == '*')
        return (n1*n2);
    if(c == '/')
        return (n1/n2);
    if(c == '^')
        return (pow(n1,n2));
}
