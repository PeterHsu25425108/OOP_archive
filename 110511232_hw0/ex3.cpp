#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
using namespace std;

struct point
{
    int x;
    int y;
};

struct node
{
    point p;
    node* next;
    node* prev;
};

struct inter
{
    point p;
    point* way_arr;//[up,down,left,right]
    inter* prev;
};

point* get_pos(string input,int& pos_num);
node* start_ptr(string* map,point* pos,int row_count,int pos_num);
point* possible_way(node* current,string* map,inter* choice);
bool is_Exit(node* current,string* map,int row_count,int col_count);
void add_path(point k,node** current_ptr);
void delete_path(point k, node** current_ptr, inter** choice_ptr);
void delete_inter(inter** choice_ptr);
void add_inter(inter** choice_ptr,node* current,point* wayout);
bool in_path(node* current,point k);
bool in_choice(inter* choice,point k);
bool same_point(point a,point b);
void show_path(node** current_ptr)
{
    node* current=*current_ptr;
    node* start=current->next;
    node* ptr=start;
    cout<<"show path:"<<endl;
    cout<<ptr->p.x<<','<<ptr->p.y<<" ";
    ptr=ptr->next;
    while(ptr!=start)
    {
        cout<<ptr->p.x<<','<<ptr->p.y<<" ";
        ptr=ptr->next;
    }
    cout<<endl;
}
void show_choice(inter** choice_ptr)
{
    inter* last=*choice_ptr;
    inter* ptr=last;
    cout<<"show choice:"<<endl;
    if(ptr==NULL)
    {
        cout<<"no choice"<<endl;
        return;
    }
    cout<<ptr->p.x<<','<<ptr->p.y<<" ";
    ptr=ptr->prev;
    while(ptr!=NULL)
    {
        cout<<"while"<<endl;
        cout<<ptr->p.x<<','<<ptr->p.y<<" ";
        ptr=ptr->prev;
        if(ptr->prev==ptr)
        {
            cout<<"prev connect to ptr"<<endl;
            break;
        }
    }
    cout<<endl;
}

int main(int argc,char** argv)
{
	ifstream in_file;
	ofstream out_file;
	in_file.open(argv[1]);
	out_file.open(argv[2]);
	
	string input;
	string* map;
	int row_count=0;
    point* pos;
    int pos_num=0;
    point empty_point={-1,-1};

	while(getline(in_file,input))
	{
		if(isdigit(input[0]))
		{
			if(pos_num>0)
            {
                delete [] pos;
                pos_num=0;
            }
            string* temp=new string [row_count+1];
            for(int i=0;i<row_count;i++)
            {
                temp[i]=map[i];
            }
            temp[row_count]=input;
            if(row_count>0)
                delete [] map;
            map=temp;
            row_count++;
		}
		else if(input[0]=='[')
		{
            int col_count=map[0].length();
			pos=get_pos(input,pos_num);
			cout<<"map:"<<endl;
            for(int i=0;i<row_count;i++)
            {
                for(int j=0;j<map[i].length();j++)
                {
                    cout<<map[i][j]<<" ";
                }
                cout<<endl;
            }
            node* current=start_ptr(map,pos,row_count,pos_num);
            cout<<"."<<endl<<"("<<current->p.x+1<<", "<<current->p.y+1<<")"<<endl;//print start point
            out_file<<"."<<endl<<"("<<current->p.x+1<<", "<<current->p.y+1<<")"<<endl;

            inter* choice =NULL;
            while(!is_Exit(current,map,row_count,col_count))
            {
                //cout<<"isExit==false"<<endl;
                point* wayout=possible_way(current,map,choice);/*return all NULL when blocked by 3 1s and one occupied blank pos
                or when the point itself is an intersection at which all the posible steps lead to dead ends*/
                //cout<<"possible way"<<endl;
                int num_way=0;
                for(int i=0;i<4;i++)
                {
                    num_way+=(same_point(wayout[i],{-1,-1})) ? 0 : 1;
                }
                //cout<<"num_way: "<<num_way<<endl;
                /*for(int i=0;i<4;i++)
                {
                    cout<<wayout[i].x<<" "<<wayout[i].y<<endl;
                }*/

                if(num_way==0)
                {
                    /*cout<<"no way out"<<endl;
                    cout<<"current pos before delete_path: "<<current->p.x<<","<<current->p.y<<endl;*/
                    delete_path(current->p, &current, &choice);
                }
                else if(num_way>=2)
                {
                    bool add_new_inter;
                    //cout<<"multiple ways"<<endl;
                    point current_pos=current->p;
                    //cout<<"current_pos"<<endl;
                    add_new_inter=(choice==NULL) ? true :(!same_point(current_pos,choice->p));
                    //cout<<endl<<add_new_inter<<endl<<endl;
                    if(add_new_inter)
                    {
                        //cout<<"add_inter_activate"<<endl;
                        add_inter(&choice,current,wayout);//activate only when current pos isn't in choice
                    }
                    //cout<<"choice(outside): ";
                    /*if(choice==NULL)
                        cout<<"choice==NULL(outside)"<<endl;*/
                    /*for(int i=0;i<4;i++)
                    {
                        point f=choice->way_arr[i];
                        cout<<f.x<<" "<<f.y<<endl;
                    }*/

                    /*cout<<"choice->prev(outside): ";
                    if(choice->prev==NULL)
                    {
                        cout<<"NULL"<<endl;
                    }
                    else
                    {
                        for(int i=0;i<4;i++)
                        {
                            point f=choice->way_arr[i];
                            cout<<f.x<<" "<<f.y<<endl;
                        }
                    }*/

                    int idx=0;
                    while(same_point(wayout[idx],{-1,-1}))//here
                        idx++;
                    point k=wayout[idx];
                    add_path(k,&current);
                    //cout<<"multiple ways done"<<endl;
                }
                else
                {
                    //cout<<"only one way"<<endl;
                    int idx=0;
                    while(same_point(wayout[idx],{-1,-1}))//here
                        idx++;
                    point k=wayout[idx];
                    /*cout<<"k: "<<k.x<<" "<<k.y<<endl;
                    cout<<"old pos: "<<current->p.x<<" "<<current->p.y<<endl;
                    point f=current->next->p;
                    cout<<"old start: "<<f.x<<" "<<f.y<<endl;*/
                    add_path(k,&current);
                    /*cout<<"new pos: "<<current->p.x<<" "<<current->p.y<<endl;
                    f=current->next->p;
                    cout<<"new start: "<<f.x<<" "<<f.y<<endl;*/
                    //cout<<"next isExit: "<<is_Exit(current,map,row_count,col_count)<<endl;
                }
                //show_path(&current);
                //show_choice(&choice);
                if((choice==NULL)&&(current->next==current))
                    break;
                //cout<<"doesn't break"<<endl;
            }

            node* ptr=current->next;
            node* start=ptr;
            cout<<"[("<<start->p.x+1<<" ,"<<start->p.y+1<<")";
            out_file<<"[("<<start->p.x+1<<" ,"<<start->p.y+1<<")";
            ptr=ptr->next;
            while(ptr!=start)
            {
                cout<<", ("<<ptr->p.x+1<<", "<<ptr->p.y+1<<")";
                out_file<<", ("<<ptr->p.x+1<<", "<<ptr->p.y+1<<")";
                ptr=ptr->next;
            }
            cout<<"]"<<endl;
            out_file<<"]"<<endl;
            char test;
            //in_file.get(test);
            if(in_file.get(test))
            {
                /*cout<<"next row"<<endl;
                out_file<<"next row"<<endl;*/
                cout<<endl;
                out_file<<endl;
            }
            row_count=0;
            pos_num=0;
		}
	}

	in_file.close();
	out_file.close();
	return 0;
}

point* get_pos(string input,int& pos_num)
{
    point* val;
    for(int j=0;j<input.length();j++)
    {
        char c=input[j];
        if(c=='(')
        {
            string str=input.substr(j,6);
            point* temp=new point [pos_num+1];
            for(int i=0;i<pos_num;i++)
            {
                temp[i]=val[i];
            }
            temp[pos_num]={str[1]-'1',str[4]-'1'};
            if(pos_num>0)
                delete [] val;
            val=temp;
            pos_num++;
        }
    }
    return val;
}

node* start_ptr(string* map,point* pos,int row_count,int pos_num)
{
    node* current_ptr;
    int k=0;
    point start=pos[k];
    while(map[start.x][start.y]=='1')
    {
        start=pos[k+1];
        k++;
    }
    /*cout<<"x: "<<start.x<<endl;
    cout<<"y: "<<start.y<<endl;*/
    current_ptr=new node;
    current_ptr->p=start;
    current_ptr->prev=current_ptr;
    current_ptr->next=current_ptr;
    return current_ptr;
}

bool is_Exit(node* current,string* map,int row_count,int col_count)
{
    /*cout<<"row_count: "<<row_count<<endl;
    cout<<"col_count: "<<col_count<<endl;*/
    int a=current->p.x;
    int b=current->p.y;
    //cout<<"is_Exit done"<<endl;
    return ((a==0)||(a==row_count-1)||(b==0)||(b==col_count-1));
}

point* possible_way(node* current,string* map,inter* choice)
{
    point* val=new point [4];
    point current_pos=current->p;
    int a=current_pos.x;
    int b=current_pos.y;
    //cout<<"in_choice start"<<endl;
    if(in_choice(choice,current_pos))
    {
        //cout<<"in choice"<<endl;
        val=choice->way_arr;
    }
    else
    {
        //cout<<"not in choice"<<endl;
        for(int i=0;i<4;i++)
        {
            //cout<<"udlr"<<endl;
            point way;
            point u={a-1,b};
            point d={a+1,b};
            point l={a,b-1};
            point r={a,b+1};
            point empty_point={-1,-1};
            switch(i)
            {
                case 0:
                    way=(map[a-1][b]=='0') ? u : empty_point;
                    break;
                case 1:
                    way=(map[a+1][b]=='0') ? d : empty_point;
                    break;
                case 2:
                    way=(map[a][b-1]=='0') ? l : empty_point;
                    break;
                case 3:
                    way=(map[a][b+1]=='0') ? r : empty_point;
                    break;
                default:
                    break;
            }
            val[i]=way;
        }
    }
    //cout<<"for"<<endl;
    for(int i=0;i<4;i++)
    {
        if(!same_point(val[i],{-1,-1}))
        {
            if(in_path(current,val[i]))
                val[i]={-1,-1};
        }
    }
    return val;
}

void add_path(point k,node** current_ptr)
{
    node* current=*current_ptr;
    node* start=current->next;
    node* element=new node;
    (*element).p=k;
    (*element).prev=current;
    (*element).next=start;
    current->next=element;
    start->prev=element;
    current=element;
    (*current_ptr)=element;
}

void delete_path(point k, node** current_ptr, inter** choice_ptr)/*turn the first term in choice->way to false, if choice->way h
as no point in it after that,delete the first term of choice*/
{
    node* current=*current_ptr;
    inter* choice=*choice_ptr;
    point empty_point={-1,-1};
    if(choice==NULL)
    {
        //cout<<"delete all path"<<endl;
        node* ptr=current;
        node* start=current->next;
        while(ptr!=start)
        {
            node* temp=ptr;
            ptr=ptr->prev;
            ptr->next=start;
            start->prev=ptr;
            delete [] temp;
        }
        (*current_ptr)=ptr;
    }
    else if(same_point(choice->p,current->p))
    {
        //point empty_point={-1,-1};
        //cout<<"delete choice"<<endl;
        int idx=0;
        while(same_point(choice->way_arr[idx],empty_point)&&(idx<4))
        {
            idx++;
        }
        if(idx<4)
        {
            /*cout<<"way_arr before eliminating:"<<endl;
            for(int i=0;i<4;i++)
            {
                cout<<choice->way_arr[i].x<<","<<choice->way_arr[i].y<<endl;
            }
            cout<<"eliminate point"<<idx<<endl;*/
            (*choice_ptr)->way_arr[idx]={-1,-1};
        }
        else
        {
            //cout<<"delete intersection"<<endl;
            delete_inter(choice_ptr);
            /*cout<<"first inter after deleting inter: ";
            if((*choice_ptr)==NULL)
            {
                cout<<"no inter left"<<endl;
            }
            else
            {
                point f=(*choice_ptr)->p;
                cout<<f.x<<","<<f.y<<endl;
            }*/
            if(current->next!=current)
            {
                point new_pos=(*choice_ptr)->p;
                node* ptr=current;
                node* start=current->next;
                while(!same_point(ptr->p,new_pos))
                {
                    node* old_ptr=ptr;
                    ptr=ptr->prev;
                    ptr->next=start;
                    start->prev=ptr;
                    delete old_ptr;
                    old_ptr=NULL;
                }
                (*current_ptr)=ptr;
            }

            inter* prev_inter=(*choice_ptr);
            if(prev_inter!=NULL)
            {
                point* prev_ways=prev_inter->way_arr;
                int idx=0;
                while(same_point(prev_ways[idx],empty_point))
                    idx++;
                //prev_inter->way_arr[idx]=empty_point;
                (*choice_ptr)->way_arr[idx]=empty_point;
            }
            //cout<<"current pos after resetting to last intersection: "<<(*current_ptr)->p.x<<","<<(*current_ptr)->p.y<<endl;
        }
    }
    else//set pos to the first intersecion and set the first choice point to {-1,-1}
    {
        //cout<<"eliminate way"<<endl;
        point new_pos=choice->p;
        node* ptr=current;
        node* start=current->next;
        while(!same_point(ptr->p,new_pos))
        {
            node* old_ptr=ptr;
            ptr=ptr->prev;
            ptr->next=start;
            start->prev=ptr;
            delete old_ptr;
            old_ptr=NULL;
        }
        (*current_ptr)=ptr;
        //cout<<"current pos after resetting to intersection: "<<(*current_ptr)->p.x<<","<<(*current_ptr)->p.y<<endl;

        point* ways=choice->way_arr;
        int idx=0;
        while(idx<4)
        {
            if(!same_point(ways[idx],empty_point))
                break;
            idx++;
        }
        choice->way_arr[idx]=empty_point;
        /*cout<<endl<<"ways after eliminating way:"<<endl;
        for(int i=0;i<4;i++)
        {
            point f=choice->way_arr[i];
            cout<<f.x<<","<<f.y<<" ";
        }
        cout<<endl<<endl;*/
    }
}

void delete_inter(inter** choice_ptr)
{
    inter* choice=*choice_ptr;
    inter* temp=choice;
    (*choice_ptr)=choice->prev;
    delete [] temp; 
}

void add_inter(inter** choice_ptr,node* current,point* wayout)
{
    inter* choice=*choice_ptr;
    if(choice==NULL)
    {
        //cout<<"adding first choice"<<endl;
        (*choice_ptr)=new inter;
        (*choice_ptr)->p=current->p;
        (*choice_ptr)->way_arr=wayout;
        (*choice_ptr)->prev=NULL;
        //(*choice_ptr)=element;
    }
    else
    {
        //cout<<"adding next choice"<<endl;
        inter* element=new inter;
        //cout<<"suspect"<<endl;
        element->p=current->p;
        //cout<<"point done"<<endl;
        element->way_arr=wayout;
        element->prev=choice;
        (*choice_ptr)=element;
    }
}

bool in_path(node* current,point k)
{
    node* ptr=current;
    if(same_point(ptr->p,k))
    {
        return true;
    }
    ptr=ptr->next;
    while(ptr!=current)
    {
        if(same_point(ptr->p,k))
        {
            return true;
        }
        ptr=ptr->next;
    }
    return false;
}
bool in_choice(inter* choice,point k)
{
    if(choice==NULL)
    {
        //cout<<"choice==NULL"<<endl;
        return false;
    }
    inter* ptr=choice;
    if(same_point(ptr->p,k))
    {
        //cout<<"found k in choice"<<endl;
        return true;
    }
    ptr=ptr->prev;
    //cout<<"while"<<endl;
    while(ptr!=NULL)
    {
        if(same_point(ptr->p,k))
        {
            return true;
        }
        ptr=ptr->prev;
    }
    //cout<<"in_choice done"<<endl;
    return false;
}

bool same_point(point a,point b)
{
    //cout<<"same_point start"<<endl;
    return ((a.x==b.x)&&(a.y==b.y));
}
