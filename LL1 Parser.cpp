#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fr first
#define se second
map<pair<char,char>, string> table;
string production[100][2];
string new_grammar[100][2];
string finalAns[100][2];
int t;
int n;
char strt;
char newstrt;
string Non_Terminal;
string Nterminals;
map<string,string> hash;
map<char,string> unhash;
int no_of_rules;
set<char> NT;
set<char> T;
map<char,vector<string> > productions;
string left_side[20];
string right_side[20];
map<char,set<char> > First, Follow;
map<char,int> marked;
int done[100];
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
bool check(string left_side, string right_side, char NT, vector<int> &part)
{
    int count=0;
    vector<string> parts = split(right_side);
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
                //if (alpha.size()==0)
                //	continue;
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
    //      vector<pair<string,string> >
    //      print(production,t);
    //  for (int i=0; i<n; i++)
    //      cout<<new_grammar[i][0]<<"->"<<new_grammar[i][1]<<"\n";
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
                            //  new_temp+=delta[z]+gamma;
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
    //  }
    //  for (int i=0; i<t; i++)
    //  {
    //      cout<<"Eliminating Left Recursion\n";
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
	    unhash[x] = new_grammar[i][0];
	    x = (char)(x+1);
	}
	for (int i=0; i<n; i++) 
	{
	    finalAns[i][0]=hash[new_grammar[i][0]];
	    string right = new_grammar[i][1];
	    string rule = "";
	    for(int j=0; j<right.length(); j++)
	    {
			if(right[j]>='A' && right[j]<='Z') {
		    	string temp = "";
			    temp += right[j];
			    if(j+1<right.length())
			    {
					if(right[j+1]=='\'') 
					{
				    	temp += right[j+1];
				    	j++;
					}
		    	}
		    	else
		    	{
					temp = right[j];
		    	}
		    	rule += hash[temp];
			}
			else
			{
		    	rule += right[j];
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
void PrintFirst()
{
	cout<<"\n\nFIRST\n\n";
    for(set<char>::iterator it=NT.begin(); it!=NT.end(); it++) 
    {
        set<char> fst = First[*it];
        cout<<unhash[(*it)]<<" - ";
        for(set<char>::iterator it2 = fst.begin(); it2!=fst.end(); it2++)
        {
            cout<<(*it2)<<" ";
        }
        cout<<endl;
    }
}
void PrintFollow()
{
	cout<<"\n\nFOLLOW\n\n";
    for(set<char>::iterator it=NT.begin(); it!=NT.end(); it++) 
    {
        set<char> ttemp = Follow[*it];
        cout<<unhash[(*it)]<<" - ";
        for(set<char>::iterator it2 = ttemp.begin(); it2!=ttemp.end(); it2++) 
        {
            cout<<(*it2)<<" ";
        }
        cout<<endl;
    }
}
void PrintTable()
{
	cout<<"\n\nParsing Table\n\n";
	set<char>::iterator it1, it2;
	char NTerm, Term;
	for (it1=NT.begin(); it1!=NT.end(); it1++)
	{
		NTerm=*it1;
		for (it2=T.begin(); it2!=T.end(); it2++)
		{
			Term=*it2;
			if (Term=='~')
				Term='$';
			
			if (table.find(mp(NTerm,Term))==table.end());
	//			cout<<"M["<<unhash[NTerm]<<","<<Term<<"] = "<<"Empty"<<endl;
			else
			{
				cout<<"M["<<unhash[NTerm]<<","<<Term<<"] = "<<unhash[NTerm]<<" -> ";
                //cout<<"M["<<NTerm<<","<<Term<<"] = "<<NTerm<<" -> ";
				string tmp = table[mp(NTerm,Term)];
				for (int i=0; i<tmp.size(); i++)
				{
					if (unhash.find(tmp[i])==unhash.end())
						cout<<tmp[i];
					else
                    {
						cout<<unhash[tmp[i]];
                        //cout<<tmp[i];
                    }
				}
				cout<<endl;
			}
		}
	}
	/*cout<<"Partial Table: \n";
	for(map<pair<char,char>,string>::iterator it=table.begin(); it!=table.end(); it++) 
    {
        cout<<"( "<<(it->fr).fr<<","<<(it->fr).se<<" ) = "<<it->se<<endl;
    }*/
}
void searchFirst(char NTerm)
{
    if(marked[NTerm]==1) 
    {
        return;
    }
    for(int i=0; i<productions[NTerm].size(); i++)
    {
        string right = productions[NTerm][i];
        int flag;
        for(int j=0; j<right.length(); j++) 
        {
            searchFirst(right[j]);
            set<char> tmp = First[right[j]];
            flag = 0;
            for(set<char>::iterator it=tmp.begin(); it!=tmp.end();it++)
            {
                char temp = *it;
                if(temp != '~') {
                    First[NTerm].insert(temp);
                }
                if(temp=='~') {
                    flag = 1;
                }
            }
            if(flag==0) 
                break;
        }
        if(flag) 
        {
            First[NTerm].insert('~');
        }
    }
    marked[NTerm] = 1;
}

void calculateFirst()
{
    
    for(set<char>::iterator it=T.begin(); it!=T.end(); it++) 
    {
        First[*it].insert(*it);
        marked[*it] = 1;
    }
    for(set<char>::iterator it=NT.begin(); it!=NT.end(); it++)
    {
        char NTerm = *it;
        searchFirst(NTerm);
    }
}

bool checkNonTerminal(char c)
{
    if (c>='A' && c<='Z')
        return true;
    return false;
}

void searchFollow() 
{
    //First Insert $ in Start Symbol
    Follow[newstrt].insert('$');
    while(1)
    {
        int tempp = 0;
        for(int i=0;i<no_of_rules;i++) 
        {
            for(int j=0;j<right_side[i].length();j++) 
            {
                if(checkNonTerminal(right_side[i][j])) 
                {
                    string right = "";
                    int len = right_side[i].length();
                    if((j+1)<len)
                    {
                        right = right_side[i].substr(j+1);
                    }
                    int flag=1;
                    set<char> ttemp; 
                    ttemp.clear();
                    for(int k=0;k<right.length();k++) 
                    {
                        searchFirst(right[k]);
                        set<char> tmp = First[right[k]];
                        flag = 0;
                        for(set<char>::iterator it=tmp.begin(); it!=tmp.end();it++) 
                        {
                            char temp = *it;
                            if(temp != '~') {
                                ttemp.insert(temp);
                            }
                            if(temp=='~') {
                                flag = 1;
                            }
                        }
                        if(flag==0) {
                            break;
                        }
                    }
                    if(flag) {
                        if(left_side[i][0] != right_side[i][j])
                        {
                            for(set<char>::iterator it=Follow[left_side[i][0]].begin(); it!=Follow[left_side[i][0]].end();it++) 
                            {
                                ttemp.insert(*it);
                            }
                        }
                    }
                    int temp = Follow[right_side[i][j]].size();
                    for(set<char>::iterator it=ttemp.begin(); it!=ttemp.end(); it++) {
                        Follow[right_side[i][j]].insert(*it);
                    }
                    if(temp != Follow[right_side[i][j]].size()) {
                        tempp = 1;
                    }
                }
            }
        }
        if(tempp==0) break;
    }
}

void createParseTable() 
{
    for(int i=0;i<no_of_rules;i++) 
    {
        string right = right_side[i];
        int j;
        int has_eps;
        set<char> frst;
        frst.clear();
        set<char> flw;
        flw.clear();
        for(j=0;j<right.length();j++) 
        {
            searchFirst(right[j]);
            set<char> tmp = First[right[j]];
            has_eps = 0;
            for(set<char>::iterator it=tmp.begin(); it!=tmp.end();it++) {
                char temp = *it;
                if(temp != '~') {
                    frst.insert(temp);
                }
                if(temp=='~') {
                    has_eps = 1;
                }
            }
            if(has_eps==0)
                break;
        }
        if(has_eps)
        {
            for(set<char>::iterator it=Follow[left_side[i][0]].begin(); it!=Follow[left_side[i][0]].end(); it++) 
            {
                flw.insert(*it);
            }
        }

        //Insert and Check for Conflict
        //First-First
        for(set<char>::iterator it=frst.begin(); it!=frst.end(); it++) 
        {
            if(table.find(mp(left_side[i][0],(*it))) == table.end()) 
            {
                table[mp(left_side[i][0],(*it))] = right;
	        }
            else 
            {
		        //cout<<left_side[i]<<" -> "<<right_side[i]<<endl;
                cout<<"FIRST FIRST CONFLICT\n";
                exit(1);
            }
        }
        //First-Follow
        for(set<char>::iterator it=flw.begin(); it!=flw.end(); it++) 
        {
            if(table.find(mp(left_side[i][0],(*it))) == table.end()) 
            {
                table[mp(left_side[i][0],(*it))] = right;
            }
            else 
            {
                //cout<<left_side[i]<<" -> "<<right_side[i]<<endl;
                cout<<"FIRST FOLLOW CONFLICT\n";
                exit(1);
            }
        }

    }
}


void MapNewtoDash()
{
	map<string,string>::iterator tt;
    for (tt=hash.begin(); tt!=hash.end(); tt++)
    {
    	unhash[tt->second[0]]=tt->first;
    }
}

bool Simulate(string s) {
    s += "$";
    stack<char> st;
    st.push('$');
    st.push(newstrt);
    int i=0;
    while(1) 
    {
        while(st.top() == '~') 
        {
            st.pop();
        }
        char NTerm = st.top();
        st.pop();
        char Term = s[i];
        if(table.find(mp(NTerm,Term))==table.end()) {
            return 0;
        }
        string over = table[mp(NTerm,Term)];
        reverse(over.begin(),over.end());
        for(int j=0;j<over.size();j++) 
        {
            st.push(over[j]);
        }
        while(st.top()=='~') {
            st.pop();
        }
        while(st.size() && i<s.length() && st.top()==s[i]) {
            i++;
            st.pop();
        }
        if(i==s.length() && st.empty()) 
            return 1;
    }
    return 1;
}
void leftFactoring() 
{
    int flag = 1;
    while(flag) 
    {
        flag = 0;
        for(int i=0;i<Nterminals.length();i++) 
        {
            vector<string> r = productions[Nterminals[i]];
            int idx = 0;
            string common = "";
            for(int j=0;j<r.size();j++) 
            {
                for(int k=j+1;k<r.size();k++) 
                {
                    int l = 0;
                    for(int m=0;m<r[j].size() && m<r[k].size() && r[j][m]==r[k][m];m++) 
                    {
                        l++;
                    }
                    if(l>idx) 
                    {
                        idx = l;
                        common = r[j].substr(0,idx);
                    }
                }
            }
            if(idx>0) 
            {
                flag = 1;
        //      cout<<idx<<" "<<common<<endl;
                vector<string> tempr; tempr.clear();
                vector<string> rest; rest.clear();
                for(int j=0;j<r.size();j++) 
                {
                    if(r[j].substr(0,idx) == common) 
                    {
                        if(idx==r[j].length()) 
                        {
                            rest.push_back("~");
                        }
                        else
                        {
                            rest.push_back(r[j].substr(idx));
                        }
                    }
                    else 
                    {
                        tempr.push_back(r[j]);
                    }
                }
                char c;
                for(int j=65;j<91;j++)
                {
                    if(done[j]==0) 
                    {
                        done[j] = 1;
                        c = (char)(j);
                        break;
                    }
                }
                Nterminals += c;
                string nt = "";
                nt += c;
                tempr.push_back(common+nt);
                productions[Nterminals[i]] = tempr;
                productions[c] = rest;
            }
        }
    }
}
void printLeftFactor()
{
    for(map<char,vector<string> >::iterator it=productions.begin(); it!=productions.end(); it++) 
    {
        char NT = it->first;
        vector<string> right = it->second;
        for(int j=0;j<right.size();j++) {
            cout<<NT<<" -> "<<right[j]<<endl;
        }
    }
}
int main()
{
    cout<<"Enter the no of productions: ";
    cin>>t;
    for (int i=0; i<t; i++)
    {
		cout<<"Enter left_side of Production "<<i+1<<" : ";
		cin>>production[i][0];
		cout<<"Enter right_side of Production "<<i+1<<" : ";
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
    cout<<"After Eliminating Left Recursion : \n";
    EliminatineLeftRecur();
    printAns();
    MapDashtoNew();
    MapNewtoDash();
    cout<<"After Mapping to New Symbols : \n";
    printFinal();
    FindStart();
    cout<<"Old Start = "<<strt<<" New Start = "<<newstrt<<endl;

    //LL(1) Part Starts Here
    Nterminals="";
    no_of_rules=n;
    for(int i=0; i<no_of_rules; i++) 
    {
     	left_side[i]=finalAns[i][0];
        NT.insert(left_side[i][0]);
        done[left_side[i][0]]=1;
        Nterminals += left_side[i][0];
        right_side[i]=finalAns[i][1];
        productions[left_side[i][0]].pb(right_side[i]);
        for(int j=0;j<right_side[i].size();j++) 
        {
            if(!(right_side[i][j]>='A' && right_side[i][j]<='Z'))
            {
                T.insert(right_side[i][j]);
            }
            else if(right_side[i][j]>='A' && right_side[i][j]<='Z') {
                NT.insert(right_side[i][j]);
                done[right_side[i][j]]=1;
                Nterminals +=right_side[i][j];
            }
            else 
            {
                T.insert(right_side[i][j]);
            }
        }
    }

    leftFactoring();
    //Calculating First
    cout<<"After Left Factoring : \n";
    printLeftFactor();
    calculateFirst();

    //Calculating Follow
    searchFollow();

    //PrintFirst
    PrintFirst();
    
    //PrintFollow
    PrintFollow();

    //LL(1) Parsing Table
    createParseTable();

    //Print LL(1) Parsing Table
    PrintTable();

    cout<<"Enter No of Queries: ";
    int q;
    cin>>q;
    for (int i=0; i<q; i++)
	{

	    //Parsing
	    cout<<"Enter input string : ";
	    string s;
	    cin>>s;
	    bool anss = Simulate(s);
	    if(anss) 
	    {
	        cout<<"String Accepted\n";
	    }
	    else 
	    {
	        cout<<"String Rejected\n";
	    }
	}
	return 0;
}

    





