#include<bits/stdc++.h>
using namespace std;

struct tac{
	string opnd1;
	string opnd2;
	char op;
	string temp;
};

// Function to verify whether a character is english letter or numeric digit.
// We are assuming in this solution that operand will be a single character
bool IsOperand(char C)
{
	if(C >= '0' && C <= '9') return true;
	if(C >= 'a' && C <= 'z') return true;
	if(C >= 'A' && C <= 'Z') return true;
	return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/' || C== '$')
		return true;

	return false;
}

// Function to verify whether an operator is right associative or not.
int IsRightAssociative(char op)
{
	if(op == '$') return true;
	return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op)
{
	int weight = -1;
	switch(op)
	{
	case '+':
	case '-':
		weight = 1;
	case '*':
	case '/':
		weight = 2;
	case '$':
		weight = 3;
	}
	return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2)
{
	int op1Weight = GetOperatorWeight(op1);
	int op2Weight = GetOperatorWeight(op2);

	if(op1Weight == op2Weight)
	{
		if(IsRightAssociative(op1)) return false;
		else return true;
	}
	return op1Weight > op2Weight ?  true: false;
}


string InfixToPostfix(string expression)
{
	// Declaring a Stack from Standard template library in C++.
	stack<char> S;
	string postfix = ""; // Initialize postfix as empty string.
	for(int i = 0;i< expression.length();i++) {

		// Scanning each character from left.
		// If character is a delimitter, move on.
		if(expression[i] == ' ' || expression[i] == ',') continue;

		// If character is operator, pop two elements from stack, perform operation and push the result back.
		else if(IsOperator(expression[i]))
		{
			while(!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(),expression[i]))
			{
				postfix+= S.top();
				S.pop();
			}
			S.push(expression[i]);
		}
		// Else if character is an operand
		else if(IsOperand(expression[i]))
		{
			postfix +=expression[i];
		}

		else if (expression[i] == '(')
		{
			S.push(expression[i]);
		}

		else if(expression[i] == ')')
		{
			while(!S.empty() && S.top() !=  '(') {
				postfix += S.top();
				S.pop();
			}
			S.pop();
		}
	}

	while(!S.empty()) {
		postfix += S.top();
		S.pop();
	}

	return postfix;
}



int main()
{
	ifstream file ("input.txt");
	ofstream myfile;
  //myfile.open("output.txt");
	string line;
	int n_line = 0;
	cout<<"\n\n***************\nRunning Code Generation\n****************\n\n";
	//data structure used to store all temporaries in the form of quadruples
	tac t[100];
	int ct = 0;

	int cl=0;
	int t_ind=0;

	int st_for = 0;
	int cf = 0,ce = 0;
	stack<char> track;
	vector<pair<int,int> > v;								//to keep track of if else in first pass
	vector<int> wh_line;

	vector<pair<int,int> > v_line;
	vector<int> End;
	while(getline(file,line))
	{
		n_line++;

		int l = line.length();
		char str[150];
		int last;
		for(int i=0;i<l;i++)
		{
			str[i] = line[i];
			last=i;
		}
		str[last+1] = '\0';
		char *token  = strtok(str," ");
		int cs=0;
		string word[100];
		int cw=0;
		while(token!=NULL)
		{
			word[cw++] = token;
			token = strtok(NULL," ");
		}

		if(word[1] == "=" && cw>4)
		{
			//cout<<"Three Address Code for line: "<<n_line<<endl;
			//cout<<"    "<<line<<endl;

			//temp = word[2];
			if((word[3] == "+" || word[3] == "-") && (word[5]=="*" || word[5]=="/")){
				string temp[2];
				temp[0]= word[2];
				temp[1] = word[3];
				word[3] = word[5];word[2] = word[6];
				word[5] = temp[1];word[6] = temp[0];
			}

			v_line.push_back(make_pair(n_line,0));
			string p = "";
			for(int i=2;i<l;i++)
				p = p+word[i];
			string post = InfixToPostfix(p);
			//cout<<post<<endl;
			int lp = post.length();
			//cout<<"   Its' postFix: "<<post<<endl;
			stack<string> st;

			int start = ct;
			for(int i=0;i<lp;i++)
			{
				if(post[i]=='+' || post[i]=='*' || post[i]=='-')
				{
					string right = st.top();
					st.pop();
					string left = st.top();
					st.pop();
					t[ct].opnd1 = left;
					t[ct].opnd2 = right;
					t[ct].op = post[i];
					int num = t_ind;
					std::string out_string;
					std::stringstream ss;
					ss << num;
					out_string = ss.str();
					t[ct].temp = "t"+out_string;
					st.push(t[ct].temp);
					ct++;
					t_ind++;

				}
				else
				{
					string strrr = "";
					strrr = strrr + post[i];
					st.push(strrr);

				}
			}
			int end = ct;
			End.push_back(ct);
			//printing the three address code that was just added to the quadruple structure
			for(int i=start;i<end;i++)
			{
				//cout<<t[i].temp<<" = "<<t[i].opnd1<<" "<<t[i].op<<" "<<t[i].opnd2<<endl;
			}
			//cout<<endl;

		}



		if(st_for == 1)
		{
			for(int i=0;i<cw;i++)
			{
				//cout<<word[i]<<" ";
				if(word[i] == "if")
				{
					cf++;
					wh_line.push_back(n_line);
				}
				if(word[i] == "else")
				{
					ce++;
					wh_line.push_back(n_line);
				}
				if(word[i]=="{")
					track.push('{');
				if(!track.empty() && word[i]=="}")
					track.pop();

			}
			//cout<<endl;
			if(track.empty())
			{
				st_for=0;								//indicates that exited the for block
				//cout<<"if:"<<cf<<" else:"<<ce<<endl;
				v.push_back(make_pair(cf,ce));
				wh_line.push_back(n_line);
				cf = 0;ce=0;
			}

		}

		if(word[0] == "for" && st_for==0)
		{
			track.push('{');
			st_for = 1;									//indicates that we are inside the for block
			string start = word[4];
			string end = word[8];
			/*if(word[7] == "<")
			{
				cout<<"if "<<word[6]<<" >= "<<word[8]<<" goto L"<<c_lab<<endl;
				c_lab++;
			}
			if(word[7] == ">")
			{
				cout<<"if "<<word[6]<<" <= "<<word[8]<<" goto L"<<c_lab<<endl;
				c_lab++;
			}*/
		}



	}
	while(!track.empty())
		track.pop();

	cout<<endl;
	//myfile<<endl;
	cout<<"Temporaries\n";
	//myfile<<"Temporaries\n";
	for(int i=0;i<ct;i++)
	{
		cout<<i<<": "<<t[i].temp<<" = "<<t[i].opnd1<<" "<<t[i].op<<" "<<t[i].opnd2<<endl;
		//myfile<<i<<": "<<t[i].temp<<" = "<<t[i].opnd1<<" "<<t[i].op<<" "<<t[i].opnd2<<endl;

	}
	cout<<endl;
	cout<<"*****************************************************************************\n";
	cout<<"*****************************************************************************\n";
	//myfile<<endl;
	//myfile<<"*****************************************************************************\n";
	//myfile<<"*****************************************************************************\n";
	//starting 2nd pass for brancing statement
	//collected all necessary details for the branching and assigning labels

	ifstream file2 ("input.c");



	/*for(int i=0;i<wh_line.size();i++)
		cout<<wh_line[i]<<"  ";
	cout<<endl;*/
	/*for(int i=0;i<v_line.size();i++)
		cout<<v_line[i].first<<"  ";
	cout<<endl;*/

	/*for(int i=0;i<End.size();i++)
		cout<<End[i]<<" ";
	cout<<endl;*/

	int tt1 = 0;
	int stt = 0;


	int c_lab = 0;
	int cv=0;
	st_for=0;
	int tl=0;
	int one = 0,two=0;
	n_line=0;
	int inr=0,dcr=0;
	int tt = 0;
	int pt = 0;
	int ste = 0;
	while(getline(file2,line))
	{
		n_line++;
		int l = line.length();
		char str[150];
		int last;
		for(int i=0;i<l;i++)
		{
			str[i] = line[i];
			last=i;
		}
		str[last+1] = '\0';
		char *token  = strtok(str," ");
		int cs=0;
		string word[100];
		int cw=0;
		while(token!=NULL)
		{
			word[cw++] = token;
			token = strtok(NULL," ");
		}




		if(st_for == 1)
		{

			if(two == 1)
			{

				for(int i=0;i<cw;i++)
				{
					//cout<<word[i]<<" ";
					if(word[i] == "if")
					{
						cout<<"if "<<word[2]<<" "<<word[3]<<" "<<word[4]<<" != "<<word[6]<<" goto L"<<c_lab<<endl;
						//myfile<<"if "<<word[2]<<" "<<word[3]<<" "<<word[4]<<" != "<<word[6]<<" goto L"<<c_lab<<endl;

					}
					if(word[i] == "else")
					{
						cout<<"goto L"<<(c_lab+1)<<endl;
						cout<<"L"<<c_lab<<": ";
						//myfile<<"goto L"<<(c_lab+1)<<endl;
						//myfile<<"L"<<c_lab<<": ";
						tl++;
					}
					if(word[i]=="{")
						track.push('{');
					if(!track.empty() && word[i]=="}")
						track.pop();

				}
				//cout<<endl;
				if(n_line>wh_line[tl] && n_line<wh_line[tl+1])
				{
						if(cw>1 && cw<5){
							cout<<line<<endl;
							//myfile<<line<<endl;
						}
						else
						{
							cout<<"Temporaries-> [";
							cout<<ste<<", "<<End[tt]-1<<"]\n";
							//myfile<<"Temporaries-> [";
							//myfile<<ste<<", "<<End[tt]-1<<"]\n";
							ste=End[tt];
							tt++;
						}

				}
				if(track.empty())
				{
					st_for=0;								//indicates that exited the for block
					//cout<<"if:"<<cf<<" else:"<<ce<<endl;
					two = 0;
					if(inr==1)
					{
						cout<<"L"<<(c_lab+1)<<": i = i + 1  ";
						cout<<"goto L"<<(c_lab-1)<<endl;
						//myfile<<"L"<<(c_lab+1)<<": i = i + 1  ";
						//myfile<<"goto L"<<(c_lab-1)<<endl;
						inr=0;
					}
					if(dcr==1)
					{
						cout<<"L"<<(c_lab+1)<<": i = i - 1  ";
						cout<<"goto L"<<(c_lab-1)<<endl;
						//myfile<<"L"<<(c_lab+1)<<": i = i - 1  ";
						//myfile<<"goto L"<<(c_lab-1)<<endl;
						dcr=0;
					}
					tl++;
					c_lab++;
					cout<<endl;
					cout<<endl;
					//myfile<<endl;
					//myfile<<endl;
				}
			}
			if(one == 1)
			{

				for(int i=0;i<cw;i++)
				{
					//cout<<word[i]<<" ";
					if(word[i] == "if")
					{
						cout<<"if "<<word[2]<<" "<<word[3]<<" "<<word[4]<<" != "<<word[6]<<" goto L"<<(c_lab)<<endl;
						//myfile<<"if "<<word[2]<<" "<<word[3]<<" "<<word[4]<<" != "<<word[6]<<" goto L"<<(c_lab)<<endl;
						tl++;
					}
					if(word[i]=="{")
						track.push('{');
					if(!track.empty() && word[i]=="}")
						track.pop();

				}
				if(n_line>wh_line[tl] && n_line<wh_line[tl+1])
				{
					if(cw>1 && cw<5){
						cout<<line<<endl;
						//myfile<<line<<endl;
					}
					else
					{
						cout<<"Temporaries-> [";
							cout<<ste<<", "<<End[tt]-1<<"]\n";
							//myfile<<"Temporaries-> [";
								//myfile<<ste<<", "<<End[tt]-1<<"]\n";
							ste=End[tt];
							tt++;
					}
				}
				//cout<<endl;
				if(track.empty())
				{
					st_for=0;								//indicates that exited the for block
					//cout<<"if:"<<cf<<" else:"<<ce<<endl;
					one = 0;
					if(inr==1)
					{
						cout<<"L"<<(c_lab)<<": i = i + 1  goto L"<<(c_lab-1);
						//myfile<<"L"<<(c_lab)<<": i = i + 1  goto L"<<(c_lab-1);
						inr = 0;
					}
					if(dcr==1)
					{
						cout<<"L"<<(c_lab)<<": i = i - 1  goto L"<<(c_lab-1);
						dcr = 0;
					}
					tl++;
					c_lab++;
					cout<<endl;
					cout<<endl;
					//myfile<<endl;
					//myfile<<endl;
				}
			}


		}


		if(word[0] == "for")
		{
			track.push('{');
			string start = word[4];
			string end = word[8];
			st_for=1;
			if(word[7] == "<")
			{
				cout<<"L"<<c_lab<<":  if "<<word[6]<<" >= "<<word[8]<<" goto next.for()"<<endl;
				//myfile<<"L"<<c_lab<<":  if "<<word[6]<<" >= "<<word[8]<<" goto next.for()"<<endl;
				c_lab++;
			}
			if(word[7] == ">")
			{
				c_lab++;
				cout<<"L"<<c_lab<<":  if "<<word[6]<<" <= "<<word[8]<<" goto next.for()"<<endl;
				//myfile<<"L"<<c_lab<<":  if "<<word[6]<<" <= "<<word[8]<<" goto next.for()"<<endl;
				c_lab++;
			}

			//checking whether inside it is (if,else) or (if)
			if(v[cv].first == 1 && v[cv].second == 1)
			{
				two = 1;
			}
			else if(v[cv].first == 1 && v[cv].second == 0)
			{
				one = 1;
			}
			if(word[11] == "--")
				dcr=1;
			if(word[11] =="++")
				inr=1;
			cv++;

		}
	}
 //myfile.close();
}
