#include<bits/stdc++.h>
using namespace std;
string production[100][2];
string new_grammar[100][2];
string finalAns[100][2];
int t;
int n;
char strt;
char newstrt;
string Non_Terminal;
map<string,string> hash;
vector<string> split(string str)
{
    string temp = "|";
    temp += str;
    temp +="|";
    int n=temp.size();
    vector<string> res;
    int i=0;
    string part;
    while (i<n)
    {
	part = "";
	if (temp[i]=='|')
	    i++;
	else
	{
	    while (i<n && temp[i]!='|')
	    {
		part += temp[i];
		i++;
	    }
	    res.push_back(part);
	}
    }
    return res;
}
bool check(string LHS, string RHS, char NT, vector<int> &part)
{
	int count=0;
    vector<string> parts = split(RHS);
    for (int i=0; i<parts.size(); i++)
    {
		if (parts[i][0]==NT)
		{
		    part.push_back(i);
		    cout<<"found in "<<i<<endl;
		}
    }
    if (part.size()>0)
    	return true;
    return false;
}
void Remove_Direct(int i)
{
	bool flag=false;
	vector<string> RHS_Part = split(production[i][1]);
	vector<string>::iterator it;
	string temp;
	for (it=RHS_Part.begin(); it!=RHS_Part.end(); it++)
	{
	    temp=*it;
	    if (temp[0]==production[i][0][0])
	    {
			flag=true; //This Means Direct Left Recursion is there
			break;
	    }
	}
	if (flag==true)
	{
		bool again=false;
		bool beta=false;
	    string s="";
	    for (it=RHS_Part.begin(); it!=RHS_Part.end(); it++)
	    {
			temp = *it;
			if (temp[0]==production[i][0][0])
			{
			    new_grammar[n][0] = production[i][0]+"'";
			    string alpha = temp.substr(1);
			    new_grammar[n][1] = alpha + production[i][0]+"'";
			    n++;
			    if (again==false)
			    {
			    	new_grammar[n][0] = production[i][0]+"'";
			    	new_grammar[n][1] = "~";
			    	n++;
			    	again=true;
			    }
			}
			else
			{
				beta=true;
			    new_grammar[n][0] = production[i][0];
			    new_grammar[n][1] = temp + production[i][0] + "'";
			    n++;
			    s += temp+production[i][0]+"'|";

			}
	    }
	    if (beta==false) {
	    	new_grammar[n][0] = production[i][0];
	    	new_grammar[n][1] = production[i][0]+"'";
	    	n++;
	    }
	    production[i][1]=s.substr(0,s.length()-1);

	}
	else
	{
	    for (it=RHS_Part.begin(); it!=RHS_Part.end(); it++)
	    {
			temp = *it;
			new_grammar[n][0] = production[i][0];
			new_grammar[n][1] = temp;
			n++;
		}
	}
	//		vector<pair<string,string> >
	//		print(production,t);
	//	for (int i=0; i<n; i++)
	//		cout<<new_grammar[i][0]<<"->"<<new_grammar[i][1]<<"\n";
}
void EliminatineLeftRecur()
{
	for (int i=0; i<t; i++)
    {
		for (int j=0; j<i; j++)
		{
	    	vector<int> part;
	    	bool ans = check(production[i][0],production[i][1],Non_Terminal[j],part);
	    	if (ans==true)
	    	{
				string new_temp="";
				vector<string> parts = split(production[i][1]);
				for (int k=0; k<parts.size(); k++)
				{
				    if (find(part.begin(),part.end(),k)!=part.end())
				    {
						string gamma = parts[k].substr(1);
						vector<string> delta = split(production[j][1]);
						for (int z=0; z<delta.size(); z++)
						{
						    //if (z==delta.size()-1)
						    //	new_temp+=delta[z]+gamma;
						    //else
						    new_temp+=delta[z]+gamma+"|";
						}
		    		}
		    		else
				    {
						//if (k==parts.size()-1)
						//new_temp+=parts[k];
						//else
						new_temp+=parts[k]+"|";
				    }
				}
				production[i][1]=new_temp.substr(0,new_temp.length()-1);
	    	}
		}
	//	}
	//	for (int i=0; i<t; i++)
	//	{
	//		cout<<"Eliminating Left Recursion\n";
		Remove_Direct(i);
	}
}
void printAns()
{
    cout<<"New Grammar\n";
    for (int i=0; i<n; i++)
		cout<<new_grammar[i][0]<<"->"<<new_grammar[i][1]<<"\n";
}
void printFinal()
{
    cout<<"Final Grammar with New Symbols\n";
    for (int i=0; i<n; i++)
		cout<<finalAns[i][0]<<"->"<<finalAns[i][1]<<"\n";
}
void MapDashtoNew()
{
	char x = 'A';
	for(int i=0; i<n; i++) 
	{
	    hash[new_grammar[i][0]] = x;
	    x = (char)(x+1);
	}
	for (int i=0; i<n; i++) 
	{
	    finalAns[i][0]=hash[new_grammar[i][0]];
	    string rhs = new_grammar[i][1];
	    string rule = "";
	    for(int j=0; j<rhs.length(); j++)
	    {
			if(rhs[j]>='A' && rhs[j]<='Z') {
		    	string temp = "";
			    temp += rhs[j];
			    if(j+1<rhs.length())
			    {
					if(rhs[j+1]=='\'') 
					{
				    	temp += rhs[j+1];
				    	j++;
					}
		    	}
		    	else
		    	{
					temp = rhs[j];
		    	}
		    	rule += hash[temp];
			}
			else
			{
		    	rule += rhs[j];
			}
	    }
	//  cout<<rule<<endl;
	    finalAns[i][1] =rule;
	}
}
void FindStart()
{
	string temp = "";
	temp += strt;
	newstrt = hash[temp][0];
}
int main()
{
    cout<<"Enter the no of productions: ";
    cin>>t;
    for (int i=0; i<t; i++)
    {
		cout<<"Enter LHS of Production "<<i+1<<" : ";
		cin>>production[i][0];
		cout<<"Enter RHS of Production "<<i+1<<" : ";
		cin>>production[i][1];
    }
    strt = production[0][0][0];
    n=0;
    
    //Algorithm starts here
    Non_Terminal="";
    for (int i=0; i<t; i++)
    {
		Non_Terminal += production[i][0][0];
    }

    EliminatineLeftRecur();
    printAns();
    MapDashtoNew();
    printFinal();
    FindStart();
    cout<<"Old Start = "<<strt<<" New Start = "<<newstrt<<endl;
	return 0;
}

    





