


#include<bits/stdc++.h>
#include<iostream>
#include "LL1_parser_implementation.c"
using namespace std;







struct ref_table{
	string name;
	string type;
	string who;
	int level;
}ref_table[100];

struct table{
	string name;
	string ret_type;
	int ptr;
	int num_par;
	int g_flag;
}table[100];


int data_type(string s)
{
	int t = (s.length()>0) && (s == "int") || (s == "float") || (s == "double") || (s=="char");
	if(t==1)
		return 1;
	else return 0;
}

string get_type(string s,int n1,int n2)
{
	string res;
	for(int i=0;i<n1;i++)
	{
		if(table[i].name == s)
		{
			res = table[i].ret_type;
			return res;
		}
	}
	for(int i=0;i<n2;i++)
	{
		if(ref_table[i].name == s)
		{
			res = ref_table[i].type;
			return res;
		}
	}
	return "-1";
}

int get_flag(string s,int n1,int n2)
{
	int res;
	for(int i=0;i<n1;i++)
	{
		if(table[i].name == s)
		{
			res = table[i].g_flag;
			return res;
		}
	}
	return -1;
}

int get_n_par(string s,int n1,int n2)
{
	int res;
	for(int i=0;i<n1;i++)
	{
		if(table[i].name == s)
		{
			res = table[i].num_par;
			return res;
		}
	}
	return -1;
}
int get_ptr(string s,int n1,int n2)
{
	int res;
	for(int i=0;i<n1;i++)
	{
		if(table[i].name == s)
		{
			res = table[i].ptr;
			return res;
		}
	}
	return -1;
}





int main()
{

	
	

	ifstream file ("input.txt");
	string line;
	int cr=0,ct=0;
	int f_enter = 0;
	string name="";
	int n_line=0;
	stack<char> level;
	string c_error[100];
	int ce=0;
	
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
		char *token  = strtok(str," ;,");
		int cs=0;
		string word[100];
		int cw=0;
		while(token!=NULL)
		{
			word[cw++] = token;
			token = strtok(NULL," ;,");
		}
		/*cout<<n_line<<". ";
		for(int i=0;i<cw;i++)
			cout<<word[i]<<" ";
		cout<<endl;*/

		//finding the format for knowing proper entities.
		int small=0,curl=0;
		for(int i=0;i<cw;i++)
		{
			if(word[i] == "(" || word[i] == ")")
				small++;
			else if(word[i] == "{")
				curl++;
		}
		//cout<<small<<" "<<curl<<endl;
		

		//converting integer to string.
		std::string out_string;
		std::stringstream ss;
		ss << n_line;
		out_string = ss.str();



		//type_casting
		if((word[1] == "=" && data_type(word[4])) ||  (word[0]=="(" && word[1] =="(" && data_type(word[2])))				//format for type casting
		{
			//cout<<line<<endl;
			string lhs_type;
			if(word[1]=="=")											//format c = ( ( float )  d )
			{
				
				lhs_type = get_type(word[0],ct,cr);
				int flag=0;
				string rhs_type;
				for(int i=cw-1;i>=0;i--)
				{
					if(data_type(word[i]) && word[i]=="float")
					{
						rhs_type = "float";
						break;
					}
				}

				//cannot assign float to an int.
				if(lhs_type == "int" && rhs_type =="float")
				{
					c_error[ce++] = "f TYPE MISMATCH: in line "+out_string;
				}
				for(int i=0;i<cw;i++)
				{
					if(data_type(word[i]))
					{
						string p_type = get_type(word[i+2],ct,cr);

						//int cant be typecasted to float
						if(p_type == "int" && data_type(word[i]) && word[i]=="float")
						{
							c_error[ce++] = "f TYPE CASTE ERROR: in line "+out_string;
							break;
						}

					}
				}
				
			}
			else																		//format: ( ( float ) c ) = ( ( float ) d ) 
			{
				int eq;
				string lhs_type,rhs_type;
				for(int i=0;i<cw;i++)
				{
					if(word[i] == "=")
					{
						eq = i;
						break;
					}
				}
				int al = 0;
				for(int i=0;i<eq;i++)
				{
					if(data_type(word[i]) && word[i]=="float")
					{
						lhs_type = "float";
						string p_type = get_type(word[i+2],ct,cr);

						//int cant be typecasted to float
						if(p_type == "int" && data_type(word[i]) && word[i]=="float")
						{
							c_error[ce++] = "f TYPE CASTE ERROR: in line "+out_string;
							al =1;
							break;
						}
					}
					else if(data_type(word[i]) && word[i]=="int")
					{
						lhs_type = "int";
					}
				}
				int suc_caste = 0;
				for(int i=eq+1;i<cw;i++)
				{
					if(data_type(word[i]) && word[i] == "float")
					{
						rhs_type = "float";
						string p_type = get_type(word[i+2],ct,cr);
						if(p_type == "int" && data_type(word[i]) && word[i] =="float")
						{
							if(al == 0)
							{
								c_error[ce++] = "f TYPE CASTE ERROR: in line "+out_string;
								suc_caste = 1;
								break;
							}
							
						}
					}
				}

				//cannot assign float to an int.
				if(lhs_type == "int" && rhs_type == "float")
				{
					c_error[ce++] = "f TYPE MISMATCH: in line "+out_string;

				}
			}
			
		}

		//typeChecking
		if(word[1] == "=" && word[2] != "(")										//type check format
		{
			string beginW = word[0];												//search on both global variable and local symbol tables

			
			string begin_type;							//will contain lhs.type()

			int f_in_table = 0;
			for(int i=0;i<ct;i++)
			{
				if(beginW == table[i].name)
				{
					begin_type = table[i].ret_type;
					f_in_table = 1;
					break;
				}
			}
			if(f_in_table == 0)
			{
				for(int i=0;i<cr;i++)
				{
					if(beginW == ref_table[i].name)
					{
						begin_type = ref_table[i].type;
						break;
					}
				}
			}
			
			string t_type;								//will contain rhs.type()
			int iflag=0,fflag=0;

			//checking for int
			for(int j=0;j<word[2].length();j++)
			{
				char ch = word[2][j];
				if((ch>='0' && ch<='9'))
				{

				}
				else
				{
					iflag=1;
					break;
				}
			}
			if(iflag == 0)
				t_type = "int";

			if(iflag==1)
			{
				//checking for float
				for(int j=0;j<word[2].length();j++)
				{
					char ch = word[2][j];
					if((ch>='0' && ch<='9') || ch=='.')
					{

					}
					else
					{
						fflag=1;
						iflag=0;
						break;
					}
				}
				if(fflag==0)
					t_type = "float";
			}
			
			if(fflag == 1)
			{
				f_in_table = 0;
				for(int i=0;i<ct;i++)
				{
					if(table[i].name == word[2])
					{
						t_type = table[i].ret_type;
						f_in_table = 1;
						break;
					}
				}
				if(f_in_table == 0)
				{
					for(int i=0;i<cr;i++)
					{
						if(ref_table[i].name == word[2])
						{
							t_type = ref_table[i].type;
							break;
						}
					}
				}
				
			}

			//cout<<n_line<<"   "<<begin_type<<"   "<<t_type<<endl;

			//if lhs.type() != rhs.type()
			if(begin_type=="int" && t_type != begin_type)
			{
				c_error[ce++] = "f TYPE MISMATCH: at line no. "+out_string;
			}

		}
		


		//if we are already in the scope of a function
		if(f_enter == 0)
		{
			if(small == 0 && curl == 0)												//its a global variable
			{
				if(data_type(word[0]))
				{
					//entering data in global symbol table
					table[ct].name = word[1];
					table[ct].ret_type = word[0];
					table[ct].ptr = cr;
					table[ct].num_par = 0;
					table[ct].g_flag = 1;

					//entering data in local symbol table
					ref_table[cr].name = word[1];
					ref_table[cr].type = word[0];
					ref_table[cr].who = "var";
					ref_table[cr].level = 0;
					cr++;
					ct++;
				}
			}

			if(small>0 && curl ==0)													//its a prototype declaration
			{
				//cout<<line<<endl;
				table[ct].name = word[1];
				table[ct].ret_type = word[0];

				int st=0,end=0;
				int n_par=0;

				//finding number of paramters
				for(int i=0;i<cw;i++)
				{
					if(word[i] == "(")
					{
						st=i;
						break;
					}
				}
				for(int i=cw-1;i>=0;i--)
				{
					if(word[i]==")")
					{
						end=i;
						break;
					}
				}
				for(int i=st+1;i<end;i++)
				{
					if(data_type(word[i]))
						n_par++;
				}
				table[ct].num_par = n_par;
				table[ct].g_flag=0;
				table[ct].ptr = 0;
				ct++;

			}

			if(data_type(word[0]) && small>0 && curl>0)								//function definition
			{

				//search whether there was a protoype declared or not
				int present = -1;
				for(int i=0;i<ct;i++)
				{
					if(table[i].name == word[1])
					{
						present = i;
						break;
					}
				}

				//if prototype declaration is present
				if(present != -1)
				{
					table[present].ptr = cr;
					if(word[0] != table[present].ret_type)
					{
						c_error[ce++] = "f Conflicting types for function "+table[present].name+"(): EARLIER DECLARED AS "+table[present].ret_type;
					}
					int st=0,end=0;

					//finding number of paramters
					int n_par=0;
					for(int i=0;i<cw;i++)
					{
						if(word[i] == "(")
						{
							st=i;
							break;
						}
					}
					for(int i=cw-1;i>=0;i--)
					{
						if(word[i]==")")
						{
							end=i;
							break;
						}
					}
					for(int i=st+1;i<end;i++)
					{
						if(data_type(word[i]))
							n_par++;
						else
						{
							ref_table[cr].name = word[i];
							ref_table[cr].type = word[i-1];
							ref_table[cr].who = "par";
							ref_table[cr].level = 1;
							cr++;
						}
					}
					if(n_par != table[present].num_par)
					{
						c_error[ce++] = "f Conflicting types for function "+table[present].name+"(): CONFLICTING #no PARAMETRES";
					}
					
					level.push('{');
					f_enter = 1;
					name=table[present].name;

				}

				//no prototype was found
				else
				{
					table[ct].name = word[1];
					table[ct].ret_type = word[0];
					table[ct].ptr = cr;
					int st=0,end=0;

					//finding number of paramters
					for(int i=0;i<l;i++)
					{
						if(word[i] == "(")
						{
							st=i;
							break;
						}
					}
					for(int i=l-1;i>=0;i--)
					{
						if(word[i]==")")
						{
							end=i;
							break;
						}
					}
					int n_par=0;
					for(int i=st+1;i<end;i++)
					{
						if(data_type(word[i]))
							n_par++;
						else
						{
							ref_table[cr].name = word[i];
							ref_table[cr].type = word[i-1];
							ref_table[cr].who = "par";
							ref_table[cr].level = 1;
							cr++;
						}
					}
					table[ct].num_par = n_par;
					table[ct].g_flag = 0;
					
					level.push('{');
					f_enter = 1;
					name = table[ct].name;
					ct++;
					//cout<<"Entered: "<<n_line<<endl;
					for(int i=0;i<ct;i++)
					{
						for(int j=i+1;j<ct;j++)
						{
							if(table[j].ptr < table[i].ptr)
							{
								struct table temp = table[j];
								table[j] = table[i];
								table[i] = temp;
							}
						}
					}


				}
				
			}
		}
		else if(f_enter == 1)
		{
			//cout<<level.size()<<"\n";
			int n_lev = 2;
			if(data_type(word[0]))
			{
				for(int i=1;i<cw;i++)
				{
					if(word[0]!=word[i])
					{
						ref_table[cr].name = word[i];
						ref_table[cr].type = word[0];
						ref_table[cr].who = "var";
						ref_table[cr].level = level.size()+1;
						cr++;
					}
					
				}
			}
			else
			{
				
				for(int i=0;i<cw;i++)
				{
					if(data_type(word[0]))
					{
						ref_table[cr].name = word[1];
						ref_table[cr].type = word[0];
						ref_table[cr].who = "var";
						ref_table[cr].level = level.size()+1;
						cr++;
					}

					//checking for return type
					else if(word[0] == "return")
					{
						string f_name = table[ct-1].name;
						//cout<<f_name<<endl;
						string r = table[ct-1].ret_type;
						int f1=0,f2=0;
						for(int j=0;j<word[1].length();j++)
						{
							char ch = word[1][j];
							if(ch>='0' && ch<='9')
							{

							}
							else
							{
								f1=1;
								break;
							}
						}
						if(f1==1)
						{
							for(int j=0;j<word[1].length();j++)
							{
								char ch = word[1][j];
								if((ch>='0' && ch<='9') || ch=='.')
								{

								}
								else
								{
									f2=1;
									break;
								}
							}
						}
						if(f1==1 && f2==1)
						{

							//checking in local sysmbol tables
							string o_ret = table[ct-1].ret_type;
							string i_ret;
							int st = table[ct-1].ptr;

							for(int j=0;j<ct;j++)
							{
								if(table[j].name == word[1])
								{
									i_ret = table[j].ret_type;
									break;
								}
							}
							for(int j=st;j<cr;j++)
							{
								if(ref_table[j].name == word[1])
								{
									i_ret = ref_table[j].type;
									break;
								}
							}
							if(i_ret == o_ret)
							{
								c_error[ce++] = "dt In function "+name+"():  RETURN TYPE MATCHES ";
							}
							else
							{
								c_error[ce++] = "df In function "+name+"():  MISMATCH IN RETURN TYPE";
							}
						}
						else if(f1==0 && r=="int")
						{
							
							c_error[ce++] = "dt In function "+name+"():  RETURN TYPE MATCHES ";
						}
						else if(f2==0)
						{
							if((r=="float" || r=="double"))
								c_error[ce++] = "dt In function "+name+"():  RETURN TYPE MATCHES";
							else
								c_error[ce++] = "df In function "+name+"():  MISMATCH IN RETURN TYPE";

						}
						
					}

					//maintaing the level information using stack
					else if(word[i] == "}")
					{
						if(level.top() =='{')
						{
							level.pop();
							n_lev--;
						}
						
					}
					else if(word[i]=="{")
					{
						level.push('{');
						n_lev++;
					}
				}
				if(level.size() == 0)
				{
					f_enter = 0;
					name="";
					//cout<<"Exit: "<<n_line<<endl;
				}
			}
		}

		for(int i=0;i<ct;i++)
		{
			for(int j=i+1;j<ct;j++)
			{
				if(table[j].ptr < table[i].ptr)
				{
					struct table temp = table[j];
					table[j] = table[i];
					table[i] = temp;
				}
			}
		}

		
	}
	cout<<"\n\n";
	

	ifstream file3 ("input.txt");
	ofstream out ("input2.txt");
	while(getline(file3,line))
	{
		int l = line.length();
		char str[150];
		int last;
		for(int i=0;i<l;i++)
		{
			str[i] = line[i];
			last=i;
		}
		str[last+1] = '\0';
		char *token  = strtok(str," ;,");
		int cs=0;
		string word[100];
		int cw=0;
		while(token!=NULL)
		{
			word[cw++] = token;
			token = strtok(NULL," ;,");
		}
		if(data_type(word[0]))
		{
			if(get_flag(word[1],ct,cr) == 0 )
			{
				if(word[cw-1]!="{")
				{
					//cout<<line<<endl;
				}
				else
					out << line<<endl;
			}
			
			
			else
			{
				out << line << endl;
			}

		}
		else if(word[1] == "=" && get_flag(word[2],ct,cr) == 0)
		{
			//cout<<line<<endl;
		}
		else
		{
			 out << line<<endl;
		}
	}


	int parse_result = parse();

	cout<<"\n\n";
	if(parse_result == 1)
	{
		cout<<ANSI_COLOR_GREEN<<"PARSED SUCCESSFULLY\n"<<ANSI_COLOR_RESET<<endl;
	}
	else
	{
		cout<<ANSI_COLOR_RED<<"FOUND ERRORS DURING PARSING\n"<<ANSI_COLOR_RESET<<endl;
	}

	//since we don't have the track of parameters of the function untill we encounter it's definiton, therefore we must compile it twice(multiple times).
	//first to collect information about all functions then checking for their errors.


	//2nd compilation for (fincding errors in function calls)
	ifstream file2 ("input.txt");
	n_line = 0;
	remove("input2.txt");
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
		char *token  = strtok(str," ;,");
		int cs=0;
		string word[100];
		int cw=0;
		while(token!=NULL)
		{
			word[cw++] = token;
			token = strtok(NULL," ;,");
		}


		std::string out_string;
		std::stringstream ss;
		ss << n_line;
		out_string = ss.str();

		//check valid function call
		if(word[1] == "=" && get_flag(word[2],ct,cr)==0)											//this is a function call
		{
			//cout<<line<<endl;
			int act_par = get_n_par(word[2],ct,cr);
			int pr_par=(cw-1) - 4;
			//cout<<act_par<<"  "<<pr_par<<endl;
			int al=0;
			if(act_par != pr_par)
			{
				c_error[ce++] = "f ERROR IN FUNCTION CALL at line "+out_string+": MISMATCH in #no of Arguments ";
				al=1;
			}
			int st = get_ptr(word[2],ct,cr);
			string act_types[10];
			string pr_types[10];
			int cct=0;
			int ccp=0;
			for(int i=st;i<cr;i++)
			{
				if(ref_table[i].who == "par")
				{
					act_types[cct++] = ref_table[i].type;
				}
				else break;
			}
			for(int i=4;i<cw-1;i++)
			{
				pr_types[ccp++] = get_type(word[i],ct,cr);
			}
			/*for(int i=0;i<cct;i++)
				cout<<act_types[i]<<"  ";
			cout<<endl;
			for(int i=0;i<ccp;i++)
			{
				cout<<pr_types[i]<<"  ";
			}
			cout<<endl;*/
			int min = ccp>cct?cct:ccp;
			int flag = 0;
			for(int i=0;i<min;i++)
			{
				if(pr_types[i]!=act_types[i])
				{
					c_error[ce++] = "f ERROR IN FUNCTION CALL at line "+out_string+": Conflicting types for the arguments.";
					flag=1;
				}
			}
			if(flag==0 && al==0)
			{
				c_error[ce++] = "t SUCCESSFUL CALL TO FUNCTION at line "+out_string;
			}

		}
	}

	//Printing of all the prepared data structures
	//Symbol tables
	//Errors
	//differentiated by various color codes.

	cout<<ANSI_COLOR_BLUE<<"				GLOBAL_SYMBOL_TABLE				"<<ANSI_COLOR_RESET<<"\n\n";
	//printing the symbol table
	cout<<ANSI_COLOR_RED<<"SNO"<<setw(15)<<"NAME"<<setw(15)<<"TYPE"<<setw(15)<<"PTR"<<setw(15)<<"#PAR"<<setw(15)
	<<"GV_flag\n"<<ANSI_COLOR_RESET;
	for(int i=0;i<ct;i++)
	{
		cout<<ANSI_COLOR_GREEN<<i<<"."<<setw(15)<<table[i].name<<setw(15)<<table[i].ret_type<<setw(15)
		<<table[i].ptr<<setw(15)<<table[i].num_par<<setw(15)<<table[i].g_flag<<ANSI_COLOR_RESET<<endl;
	}
	cout<<endl<<"\n\n";


	cout<<ANSI_COLOR_BLUE<<"				LOCAL_SYMBOL_TABLES				"<<ANSI_COLOR_RESET<<"\n\n";
	int temp = table[0].ptr;
	int temp2 = table[1].ptr;
	int ctr=2;
	int kk=0;
	int kke = cr;
	while(1)
	{
		
		cout<<ANSI_COLOR_RED<<"SNO"<<setw(15)<<"NAME"<<setw(15)<<"TYPE"<<setw(15)<<"WHO"<<setw(15)<<"LEVEL\n"<<ANSI_COLOR_RESET;
		for(int i=temp;i<temp2;i++)
		{
			cout<<ANSI_COLOR_GREEN<<i<<"."<<setw(15)<<ref_table[i].name<<setw(15)<<ref_table[i].type<<setw(15)<<ref_table[i].who<<setw(15)
			<<ref_table[i].level<<ANSI_COLOR_RESET<<endl;
			kk++;
			
		}
		cout<<endl<<endl;
		temp = temp2;
		if(ctr<ct)
		{
			temp2 = table[ctr].ptr;
			ctr++;
		}
		else temp2=cr;
		
		if(kk>=cr)
			break;
	}
	cout<<endl<<endl;


	int tot_err=0;
	cout<<ANSI_COLOR_BLUE<<"  ERROR HANDLING"<<ANSI_COLOR_RESET<<endl<<endl;
	for(int i=0;i<ce;i++)
	{
		if(c_error[i][0] == 'd' && c_error[i][1] == 'f')
		{
			tot_err++;
			cout<<ANSI_COLOR_RED;
			for(int j=2;j<c_error[i].length();j++)
				cout<<c_error[i][j];
			cout<<endl;
			i++;
		}
		else if(c_error[i][0] == 'd' && c_error[i][1] == 't')
		{
			cout<<ANSI_COLOR_GREEN;
			for(int j=2;j<c_error[i].length();j++)
				cout<<c_error[i][j];
			cout<<endl;
			i++;
		}
		else
		{
			if(c_error[i][0] == 't')
			{
				cout<<ANSI_COLOR_GREEN;
				for(int j=1;j<c_error[i].length();j++)
					cout<<c_error[i][j];
				cout<<endl;
			}
			else
			{
				tot_err++;
				cout<<ANSI_COLOR_RED;
				for(int j=1;j<c_error[i].length();j++)
					cout<<c_error[i][j];
				cout<<endl;
			}
		}
	}

	cout<<ANSI_COLOR_GREEN<<"\n COMPLETE !\n";
	cout<<ANSI_COLOR_RED<<" FOUND "<<tot_err<<" ERRORS";
	cout<<"\n\n";
	
}