#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

string ascii_str(string chunk);
string* hash_func(string* H,string wi);
string AND(string a,string b);
string XOR(string* input_set,int l);
string NOT(string input);
string ADD(string* input_set,int l);
string RotR(string input,int shift);
string Ch(string x,string y,string z);
string Maj(string x,string y,string z);

int main(int argc,char** argv)
{
	ifstream in_file;
    ofstream out_file;
    in_file.open(argv[1]);
    out_file.open(argv[2]);
    char c;
    string block="";
    string* block_arr;
    int block_num=0;
    
    while(in_file.get(c))
    {
        block+=c;
        if(block.length()>=2048)
        {
            string* temp=new string [block_num+1];
            if(block_num>0)
            {
                for(int i=0;i<block_num;i++)
                {
                    temp[i]=block_arr[i];
                }
            }
            temp[block_num]=block;
            if(block_num>0)
            {
                delete [] block_arr;
            }
            block_arr=temp;
            block="";
            block_num++;
        }
    }
    
    /*if(block_num==0)
    {
        block_arr=new string [1];
        block_arr[0]=block;
        block_num++;
    }*/

    if(block.length()>0)
    {
        string* temp=new string [block_num+1];
        if(block_num>0)
        {
            for(int i=0;i<block_num;i++)
            {
                temp[i]=block_arr[i];
            }
        }
        temp[block_num]=block;
        if(block_num>0)
        {
            delete [] block_arr;
        }
        block_arr=temp;
        block="";
        block_num++;
    }

    while(block_arr[block_num-1].length()<2048)
    {
        block_arr[block_num-1]+='_';
    }

    //cout<<"block_num: "<<block_num<<endl;

    //cout<<"digest start"<<endl;
    string* digest_arr;
    int digest_num=0;
    for(int i=0;i<block_num;i++)//produce digest for each block
    {
        //cout<<"length"<<i<<": "<<block_arr[i].length()<<endl;
        //cout<<"block["<<i<<"]: "<<block_arr[i]<<endl;
        string* H=new string [8];
        H[0]="01101010000010011110011001100111";
        H[1]="10111011011001111010111010000101";
        H[2]="00111100011011101111001101110010";
        H[3]="10100101010011111111010100111010";
        H[4]="01010001000011100101001001111111";
        H[5]="10011011000001010110100010001100";
        H[6]="00011111100000111101100110101011";
        H[7]="01011011111000001100110100011001";
        string* chunk_arr=new string [512];
        //cout<<"H"<<endl;
        for(int j=0;j<512;j++)
        {
            chunk_arr[j]=block_arr[i].substr(4*j,4);
        }
        //cout<<"substr"<<endl;
        for(int j=0;j<512;j++)
        {
            string str=ascii_str(chunk_arr[j]);
            cout<<"index = "<<j<<endl;
            cout<<"chunk"<<j<<" = "<<chunk_arr[j]<<endl;
            cout<<"W"<<j<<" = "<<str<<endl;
            H=hash_func(H,str);
        }
        //cout<<"hash"<<endl;
        string digest;
        for(int j=0;j<8;j++)
        {
            digest+=H[j];
        }
        cout<<"digest = "<<digest<<endl;
        cout<<"========================================="<<endl;
        string* new_arr=new string [digest_num+1];
        if(digest_num>0)
        {
            for(int j=0;j<digest_num;j++)
            {
                new_arr[j]=digest_arr[j];
            }
        }
        new_arr[digest_num]=digest;
        if(digest_num>0)
        {
            delete []  digest_arr;
        }
        digest_arr=new_arr;
        digest_num++;
    }

    //cout<<"digest done"<<endl;
    string* H=new string [8];
    H[0]="01101010000010011110011001100111";
    H[1]="10111011011001111010111010000101";
    H[2]="00111100011011101111001101110010";
    H[3]="10100101010011111111010100111010";
    H[4]="01010001000011100101001001111111";
    H[5]="10011011000001010110100010001100";
    H[6]="00011111100000111101100110101011";
    H[7]="01011011111000001100110100011001";
    string top_str;
    for(int i=0;i<digest_num;i++)
    {
        top_str+=digest_arr[i];
    }
    for(int i=0;i<(top_str.length()/32);i++)
    {
        string str=top_str.substr(32*i,32);
        cout<<"index = "<<i<<endl;
        cout<<"W"<<i<<" = "<<str<<endl;
        H=hash_func(H,str);
    }

    string top_digest;
    for(int i=0;i<8;i++)
    {
        top_digest+=H[i];
    }

    cout<<"digest = "<<top_digest<<endl;
    cout<<"========================================="<<endl;

    cout<<"top digest: "<<top_digest<<endl;
    out_file<<top_digest<<endl;
    for(int i=0;i<digest_num;i++)
    {
        cout<<"digest["<<i<<"]: "<<digest_arr[i]<<endl;
        out_file<<digest_arr[i]<<endl;
    }

    in_file.close();
    out_file.close();
    return 0;
}

string ascii_str(string chunk)
{
    string val;
    for(int i=0;i<4;i++)
    {
        string bin;
        int x=(int)chunk[i];
        while((x>0)||(bin.length()<8))
        {
            if(x%2==0)
            {
                bin='0'+bin;
            }
            else
            {
                bin='1'+bin;
            }
            x/=2;
        }
        val+=bin;
    }
    return val;
}

string* hash_func(string* H,string wi)
{
    string* result=new string [8];

    string* xor_set_1=new string [3];
    xor_set_1[0]= RotR(H[4], 6);
    xor_set_1[1]=RotR(H[4],11);
    xor_set_1[2]=RotR(H[4],25);

    string* xor_set_2=new string [3];
    xor_set_2[0]= RotR(H[0], 2);
    xor_set_2[1]=RotR(H[0],13);
    xor_set_2[2]=RotR(H[0],22);

    string* t1_set=new string [4];
    t1_set[0]=H[7];
    t1_set[1]=XOR(xor_set_1,3);
    //cout<<"t1_set[1]: "<<t1_set[1]<<endl;
    //cout<<"XOR safe"<<endl;
    t1_set[2]=Ch(H[4],H[5],H[6]);
    //cout<<"Ch safe"<<endl;
    t1_set[3]=wi;
    //cout<<"Enter ADD"<<endl;
    string T1=ADD(t1_set,4);
    //cout<<"ADD safe"<<endl;
    
    string* t2_set=new string [2];
    t2_set[0]=XOR(xor_set_2,3);
    t2_set[1]=Maj(H[0],H[1],H[2]);
    //cout<<"Maj safe"<<endl;
    string T2=ADD(t2_set,2);

    cout<<"t1 = "<<T1<<endl;
    cout<<"t2 = "<<T2<<endl;

    for(int i=0;i<8;i++)
    {
        if(i==0)
        {
            string* add_arr=new string [2];
            add_arr[0]=T1;
            add_arr[1]=T2;
            result[i]=ADD(add_arr,2);
        }
        else if(i==4)
        {
            string* add_arr=new string [2];
            add_arr[0]=H[3];
            add_arr[1]=T1;
            result[i]=ADD(add_arr,2);
        }
        else
        {
            result[i]=H[i-1];
        }
    }
    
    for(int i=7;i>=0;i--)
    {
        cout<<"h'["<<i<<"]: = "<<result[i]<<endl;
    }

    cout<<endl<<endl;

    delete [] H;
    return result;
}

string AND(string a,string b)
{
    string val=a;
    for(int j=0;j<32;j++)
    {
        if((a[j]=='1')&&(b[j]=='1'))
        {
            val[j]='1';
        }
        else
        {
            val[j]='0';
        }
        //cout<<"ND val: "<<val<<endl;
    }
    //cout<<"AND done"<<endl;
    return val;
}

string XOR(string* input_set,int l)
{    
    string val=input_set[0];
    for(int j=0;j<32;j++)
    {
        int count=0;
        for(int i=0;i<l;i++)
        {
            if(input_set[i][j]=='1')
                count+=1;
        }

        if(count%2==1)
        {
            val[j]='1';
        }
        else
        {
            val[j]='0';
        }
    }
    return val;
}

string NOT(string input)
{
    string val=input;
    for(int i=0;i<input.length();i++)
    {
        val[i]=(input[i]=='1') ? '0' : '1';
    }
    return val;
}

string ADD(string* input_set,int l)
{
    string a=input_set[0];
    if(l>1)
    {
        for(int i=1;i<l;i++)
        {
            string result;
            for(int j=0;j<32;j++)
            {
                result+='0';
            }
            string b=input_set[i];
            bool cin=false;
            for(int j=31;j>=0;j--)
            {
                char s;
                if(cin)
                {
                    s=(a[j]==b[j]) ? '1' : '0';
                }
                else
                {
                    s=(a[j]!=b[j]) ? '1' : '0';
                }
                result[j]=s;
                bool x=(a[j]=='1')&&(b[j]=='1');
                bool y=(a[j]=='1')&&cin;
                bool z=(b[j]=='1')&&cin;
                cin=(x||y||z) ? true : false;
            }
            a=result;
        }
    }
    return a;
}

string RotR(string input,int shift)
{
    //cout<<"rotr input"<<input<<endl;
    int l=input.length();
    string val=input;
    for(int i=0;i<l;i++)
    {
        int j=(i+shift)%l;
        val[j]=input[i];
    }
    //cout<<"val: "<<val<<endl;
    return val;
}

string Ch(string x,string y,string z)
{
    /*string* a=new string [2];
    a[0]=x;
    a[1]=y;
    string* b=new string [2];
    b[0]=NOT(x);
    cout<<"NOT safe"<<endl;
    b[1]=z;*/
    string* c=new string[2];
    c[0]=AND(x,y);
    //cout<<"AND safe"<<endl;
    c[1]=AND(z,NOT(x));
    string val =XOR(c,2);
    return val;
}

string Maj(string x,string y,string z)
{
    /*string* a=new string [2];
    string* b=new string [2];
    string* c=new string [2];
    a[0]=x;
    a[1]=y;
    b[0]=x;
    b[1]=z;
    c[0]=y;
    c[1]=z;*/
    string* d=new string [3];
    d[0]=AND(x,y);
    d[1]=AND(x,z);
    d[2]=AND(y,z);
    string val=XOR(d,3);
    return val;
}
