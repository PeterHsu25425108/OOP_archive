#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

struct arrlen
{
	int* arr;
	int len;
};

void init(int**& mtr);
string binstr(int x,int l);
void number_of_Ch(int**& mtr,string bitstr);
void modeOne(int**& mtr,string bitstr);
void modeTwo(int**& mtr,string bitstr);
void modeThree(int**& mtr,string bitstr);
void show(int** mtr);
arrlen outer_set(string msg,string err_check);
string upper(char x,char& state);
string lower(char x,char& state);
string digit(char x,char& state);
void fill_ring(int* a,int**& mtr,int set_l);

int main(int argc,char** argv)
{
	int** mtr;
	init(mtr);
	ifstream in_file;
	in_file.open(argv[1]);
	string msg;
	getline(in_file,msg);
	string err_check;
	getline(in_file,err_check);
	string mode1_str;
	getline(in_file,mode1_str);
	string mode2_str;
	getline(in_file,mode2_str);
	string mode3_str;
	getline(in_file,mode3_str);
	
	int ch_count=msg.length()-1;
	string num_ch_str=binstr(ch_count,6);
	int mode1=atoi(mode1_str.c_str());
	string mode_One_str=binstr(mode1,6);
	int mode2=atoi(mode2_str.c_str());
	string mode_Two_str=binstr(mode2,7);
	int mode3=atoi(mode3_str.c_str());
	string mode_Three_str=binstr(mode3,7);

	arrlen out=outer_set(msg,err_check);
	int* a=out.arr;
	int set_l=out.len;

	number_of_Ch(mtr,num_ch_str);
	modeOne(mtr,mode_One_str);
	modeTwo(mtr,mode_Two_str);
	modeThree(mtr,mode_Three_str);
	fill_ring(a,mtr,set_l);

	show(mtr);
	in_file.close();
	return 0;
}

void fill_ring(int* a,int**& mtr,int set_l)
{
	int idx=0;
	for(int i=1;i<=12;i++)
	{
		for(int j=0;j<=1;j++)
		{
			mtr[i][j]=a[idx];
			idx++;
			if(idx==set_l)
				return;
		}
	}

	for(int j=0;j<=12;j++)
	{
		for(int i=14;i>=13;i--)
		{
			mtr[i][j]=a[idx];
			idx++;
			if(idx==set_l)
				return;
		}
	}
	
	for(int i=14;i>=2;i--)
	{
		for(int j=14;j>=13;j--)
		{
			mtr[i][j]=a[idx];
			idx++;
			if(idx==set_l)
				return;
		}
	}

	for(int j=14;j>=2;j--)
	{
		for(int i=0;i<=1;i++)
		{
			mtr[i][j]=a[idx];
			idx++;
			if(idx==set_l)
				return;	
		}
	}
}

arrlen outer_set(string msg,string err_check)
{
	string word=msg+err_check;
	string bitstr="";
	char state='u';
	for(int i=0;i<word.length();i++)
	{
		char x=word[i];
		switch(state)
		{
			case 'u':
				bitstr+=upper(x,state);
				break;
			case 'l':
				bitstr+=lower(x,state);
				break;
			case 'd':
				bitstr+=digit(x,state);
				break;
			default:
				cerr<<"Invalid state: "<<state<<endl;
		}
	}

	int* out = new int [bitstr.length()];
	for(int i=0;i<bitstr.length();i++)
	{
		if(bitstr[i]=='0')
		{
			out[i]=0;
		}
		else if(bitstr[i]=='1')
		{
			out[i]=1;
		}
	}
	int c = bitstr.length();
	arrlen val={out,c};
	return val;
}

string upper(char x,char& state)
{
	string val;
	if(islower(x))
	{
		val=binstr(28,5)+lower(x,state);
		state='l';

	}
	else if(isdigit(x)||(x==',')||(x=='.'))
	{
		val=binstr(30,5)+digit(x,state);
		state='d';
	}
	else
	{
		int code = x-'A'+2;
		val=binstr(code,5);
	}
	return val;
}

string lower(char x,char& state)
{	
	string val;
	if(isupper(x))
	{
		val=binstr(30,5)+digit(x,state);
		state='u';

	}
	else if(isdigit(x)||(x==',')||(x=='.'))
	{
		val=binstr(30,5)+digit(x,state);
		state='d';
	}
	else
	{
		int code = x-'a'+2;
		val=binstr(code,5);
	}
	return val;
}

string digit(char x,char& state)
{
	string val;
	if(islower(x))
	{
		val=binstr(14,4)+upper(x,state);
		state='l';

	}
	else if(isupper(x))
	{
		val=binstr(14,4)+upper(x,state);
		state='u';
	}
	else
	{
		int code=((isdigit(x)) ? (int)x-'0'+2 : ((x==',') ? 12 : 13));
		val=binstr(code,4);
		
	}
	return val;
}

void show(int** mtr)
{
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			cout<<mtr[i][j];
			if(j==14)
			{
				cout<<endl;
			}
		}
	}
}

void init(int**& mtr)
{
	mtr=new int* [15];
	for(int i=0;i<15;i++)
	{
		mtr[i]=new int [15];
		for(int j=0;j<15;j++)
		{
			mtr[i][j]=0;
		}
	}

	mtr[7][7]=1;
	for(int i=3;i<=11;i++)
	{
		mtr[i][3]=1;
		mtr[i][11]=1;
	}
	for(int j=3;j<=11;j++)
	{
		mtr[3][j]=1;
		mtr[11][j]=1;
	}

	for(int i=5;i<=9;i++)
	{
		mtr[i][5]=1;
		mtr[i][9]=1;
	}
	for(int j=5;j<=9;j++)
	{
		mtr[5][j]=1;
		mtr[9][j]=1;
	}

	mtr[2][2]=1;
	mtr[2][3]=1;
	mtr[3][2]=1;
	mtr[2][12]=1;
	mtr[3][12]=1;
	mtr[11][12]=1;
}

string binstr(int x,int l)
{
	string val="";
	while(x>0)
	{
		char ch=(char)x%2+'0';
		val=ch+val;
		x/=2;
	}
	while(val.length()<l)
	{
		val='0'+val;
	}
	return val;
}

void number_of_Ch(int**& mtr,string bitstr)
{
	int l=bitstr.length();
	mtr[4][12]=bitstr[l-1]-'0';
	for(int i=0;i<l-1;i++)
	{
		mtr[2][i+6]=bitstr[i]-'0';
	}
}

void modeOne(int**& mtr,string bitstr)
{
	int l=bitstr.length();
	for(int i=0;i<l;i++)
	{
		mtr[10-i][12]=bitstr[i]-'0';
	}
}

void modeTwo(int**& mtr,string bitstr)
{
	int l=bitstr.length();
	for(int i=0;i<l;i++)
	{
		mtr[12][10-i]=bitstr[i]-'0';
	}
}

void modeThree(int**& mtr,string bitstr)
{
	int l=bitstr.length();
	for(int i=0;i<l;i++)
	{
		mtr[10-i][2]=bitstr[i]-'0';
	}
}

