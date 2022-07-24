#include<fstream>
#include<bits/stdc++.h>
using namespace std ;

class Data {
    public:
    vector<string> header = vector<string> (5, "");
    vector<vector<string>> table;

    Data(int n){
        ifstream inFile;
        inFile.open("sample2(1).csv");

        for (int i = 0; i < n-1; i++) getline (inFile, header[i], ',');
        inFile >> header[n-1];

        vector<string> row (n);
        while (!inFile.eof()) {
            for (int i = 0; i < n-1; i++) getline (inFile, row[i], ',');
            inFile >> row[n-1];
            table.push_back (row);
        }
        inFile.close();
    }
};
typedef struct Node{
    int no_of_person;
    string floor_no;
    int room_no;
    string person1;
    string person2;
    struct Node *left;
    struct Node *right;
    
}node;


node* create_Node(vector<string> temp){
    node *t=new node();
    t->floor_no=temp[0];
    t->person1=temp[1];
    t->person2=temp[2];
    if(temp[2]!="")
    {
        t->no_of_person=2;
    }
    else{
        t->no_of_person=1;
    }
    t->left=NULL;
    t->right=NULL;
    return t;
}

void map_node(node *t,unordered_map<string,node*> &node_add)
{
    node_add[t->person1]=t;
    node_add[t->person2]=t;
}

void coupling(stack<node*> &st,node *t){
    if(st.empty())
    {
        st.push(t);
        return ;
    }
    else{
        node *p1=st.top();
        p1->person2=t->person1;
        p1->no_of_person++;

        return ;
    }
}

void adj_list(unordered_map<string,vector<string>> &neighbors,vector<string> temp)
{
    neighbors[temp[1]].push_back(temp[0]);
    neighbors[temp[1]].push_back(temp[3]);
    neighbors[temp[1]].push_back(temp[4]);
    neighbors[temp[1]].push_back("N");

    if((temp[2]).compare("-1")!=0)
    {
        neighbors[temp[2]].push_back(temp[0]);
        neighbors[temp[2]].push_back(temp[3]);
        neighbors[temp[2]].push_back(temp[4]);
        neighbors[temp[2]].push_back("N");
    }

    
}

deque<node*> qt;
void allocate_floor1(unordered_map<int,vector<node*>> &floors,unordered_map<string,vector<string>> &neighbors,unordered_map<string,node*> &node_add){

    
    queue<node*> q;
    for(int i=0;i<floors[1].size();i++){
       
        node *t=floors[1][i];
        if(neighbors[t->person1][3]!="A"){
             //cout<<"i"<<" "<<i<<"\n";
            q.push(t);
            while(!q.empty()){
                node *nod=q.front();
                deque<node*> tem;
                
                if((neighbors[nod->person1][1]).compare("-1")!=0){
                    if(stoi(neighbors[nod->person1][0])==stoi(neighbors[neighbors[nod->person1][1]][0])&&neighbors[neighbors[nod->person1][1]][3]!="A"){
                    if(!(neighbors[neighbors[nod->person1][1]][1]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][1]][2]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][1]][1]).compare(nod->person2)||!(neighbors[neighbors[nod->person1][1]][2]).compare(nod->person2)){
                        tem.push_back(node_add[neighbors[nod->person1][1]]);
                        //cout<<"tem 1 "<<node_add[neighbors[nod->person1][1]]->person1<<endl;
                        q.push(node_add[neighbors[nod->person1][1]]);
                        neighbors[neighbors[nod->person1][1]][3]="A";
                    
                        
                    }
                }
                }
                if((neighbors[nod->person1][3]!="A")&&(neighbors[nod->person2][3]!="A"))
                {
                    tem.push_back(node_add[nod->person1]);
                    //cout<<"tem 2 "<<nod->person1<<endl;
                }
                neighbors[nod->person1][3]="A";
                neighbors[nod->person2][3]="A";
                
                
                if((neighbors[nod->person1][2]).compare("-1")!=0){
                    if(stoi(neighbors[nod->person1][0])==stoi(neighbors[neighbors[nod->person1][2]][0])&&neighbors[neighbors[nod->person1][2]][3]!="A"){
                    if(!(neighbors[neighbors[nod->person1][2]][1]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][2]][2]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][2]][1]).compare(nod->person2)||!(neighbors[neighbors[nod->person1][2]][2]).compare(nod->person2)){
                        tem.push_back(node_add[neighbors[nod->person1][2]]);
                        //cout<<"tem 3 "<<node_add[neighbors[nod->person1][2]]->person1<<endl;
                        q.push(node_add[neighbors[nod->person1][2]]);
                        neighbors[neighbors[nod->person1][2]][3]="A";
                       
                        
                    }
                }
                }
                if(qt.empty())
                {
                    while(!tem.empty()){
                    qt.push_back(tem.front());
                    tem.pop_front();
                    }
                }
                else{
                    if(qt.front()==nod)
                    {
                        while(!tem.empty())
                        {
                            qt.push_front(tem.front());
                            tem.pop_front();
                        }
                    }
                    else{
                        while(!tem.empty())
                        {
                            qt.push_back(tem.front());
                            tem.pop_front();
                        }
                    }
                }
                q.pop();
            }

        }
    }
    
}


void allocate_floor2(unordered_map<int,vector<node*>> &floors,unordered_map<string,vector<string>> &neighbors,unordered_map<string,node*> &node_add){

    
    queue<node*> q;
    for(int i=0;i<floors[2].size();i++){
       //cout<<"size "<<floors[2].size()<<endl;
        node *t=floors[2][i];
        if(neighbors[t->person1][3]!="A"){
            // cout<<"i"<<" "<<i<<"\n";
            q.push(t);
            while(!q.empty()){
                node *nod=q.front();
                deque<node*> tem;
                
                if(stoi(neighbors[nod->person1][0])==stoi(neighbors[neighbors[nod->person1][1]][0])&&neighbors[neighbors[nod->person1][1]][3]!="A"){
                    if(!(neighbors[neighbors[nod->person1][1]][1]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][1]][2]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][1]][1]).compare(nod->person2)||!(neighbors[neighbors[nod->person1][1]][2]).compare(nod->person2)){
                        tem.push_back(node_add[neighbors[nod->person1][1]]);
                        //cout<<"tem 1 "<<node_add[neighbors[nod->person1][1]]->person1<<endl;
                        q.push(node_add[neighbors[nod->person1][1]]);
                        neighbors[neighbors[nod->person1][1]][3]="A";
                    
                        
                    }
                }
                if((neighbors[nod->person1][3]!="A")&&(neighbors[nod->person2][3]!="A"))
                {
                    tem.push_back(node_add[nod->person1]);
                    //cout<<"tem 2 "<<nod->person1<<endl;
                }
                neighbors[nod->person1][3]="A";
                neighbors[nod->person2][3]="A";
                
                
                if(stoi(neighbors[nod->person1][0])==stoi(neighbors[neighbors[nod->person1][2]][0])&&neighbors[neighbors[nod->person1][2]][3]!="A"){
                    if(!(neighbors[neighbors[nod->person1][2]][1]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][2]][2]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][2]][1]).compare(nod->person2)||!(neighbors[neighbors[nod->person1][2]][2]).compare(nod->person2)){
                        tem.push_back(node_add[neighbors[nod->person1][2]]);
                        //cout<<"tem 3 "<<node_add[neighbors[nod->person1][2]]->person1<<endl;
                        q.push(node_add[neighbors[nod->person1][2]]);
                        neighbors[neighbors[nod->person1][2]][3]="A";
                    
                        
                    }
                }
                if(qt.empty())
                {
                    while(!tem.empty()){
                    qt.push_back(tem.front());
                    tem.pop_front();
                    }
                }
                else{
                    if(qt.front()==nod)
                    {
                        while(!tem.empty())
                        {
                            qt.push_front(tem.front());
                            tem.pop_front();
                        }
                    }
                    else{
                        while(!tem.empty())
                        {
                            qt.push_back(tem.front());
                            tem.pop_front();
                        }
                    }
                }
                q.pop();
            }

        }
    }
    
}


void allocate_floor3(unordered_map<int,vector<node*>> &floors,unordered_map<string,vector<string>> &neighbors,unordered_map<string,node*> &node_add){

    
    queue<node*> q;
    for(int i=0;i<floors[3].size();i++){
       
        node *t=floors[3][i];
        if(neighbors[t->person1][3]!="A"){
             //cout<<"i"<<" "<<i<<"\n";
            q.push(t);
            while(!q.empty()){
                node *nod=q.front();
                deque<node*> tem;
                
                if(stoi(neighbors[nod->person1][0])==stoi(neighbors[neighbors[nod->person1][1]][0])&&neighbors[neighbors[nod->person1][1]][3]!="A"){
                    if(!(neighbors[neighbors[nod->person1][1]][1]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][1]][2]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][1]][1]).compare(nod->person2)||!(neighbors[neighbors[nod->person1][1]][2]).compare(nod->person2)){
                        tem.push_back(node_add[neighbors[nod->person1][1]]);
                        //cout<<"tem 1 "<<node_add[neighbors[nod->person1][1]]->person1<<endl;
                        q.push(node_add[neighbors[nod->person1][1]]);
                        neighbors[neighbors[nod->person1][1]][3]="A";
                        
                        
                    }
                }
                if((neighbors[nod->person1][3]!="A")&&(neighbors[nod->person2][3]!="A"))
                {
                    tem.push_back(node_add[nod->person1]);
                    //cout<<"tem 2 "<<nod->person1<<endl;
                }
                neighbors[nod->person1][3]="A";
                neighbors[nod->person2][3]="A";
                
                
                if(stoi(neighbors[nod->person1][0])==stoi(neighbors[neighbors[nod->person1][2]][0])&&neighbors[neighbors[nod->person1][2]][3]!="A"){
                    if(!(neighbors[neighbors[nod->person1][2]][1]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][2]][2]).compare(nod->person1)||!(neighbors[neighbors[nod->person1][2]][1]).compare(nod->person2)||!(neighbors[neighbors[nod->person1][2]][2]).compare(nod->person2)){
                        tem.push_back(node_add[neighbors[nod->person1][2]]);
                        //cout<<"tem 3 "<<node_add[neighbors[nod->person1][2]]->person1<<endl;
                        q.push(node_add[neighbors[nod->person1][2]]);
                        neighbors[neighbors[nod->person1][2]][3]="A";
                        
                    }
                }
                if(qt.empty())
                {
                    while(!tem.empty()){
                    qt.push_back(tem.front());
                    tem.pop_front();
                    }
                }
                else{
                    if(qt.front()==nod)
                    {
                        while(!tem.empty())
                        {
                            qt.push_front(tem.front());
                            tem.pop_front();
                        }
                    }
                    else{
                        while(!tem.empty())
                        {
                            qt.push_back(tem.front());
                            tem.pop_front();
                        }
                    }
                }
                q.pop();
            }

        }
    }
    
}
void output1(deque<node*> &qt,int floor){
    int count=0;
    ofstream myFile;
    myFile.open("floor1.csv");
    myFile<<"Room_No."<<","<<"Person_1"<<","<<"Person_2"<<endl;
    while(1){
        node *t=qt.front();
         myFile<<(floor+count)<<","<<t->person1<<","<<t->person2<<endl;
        qt.pop_front();
        count++;
        if(qt.size()==0)
        {
            //cout<<"empty qt\n";
            break;
        }
        if(count==100)
        break;
    }
    
}

void output2(deque<node*> &qt,int floor){
    int count=0;
    ofstream myFile;
    myFile.open("floor2.csv");
    
    myFile<<"Room_No."<<","<<"Person_1"<<","<<"Person_2"<<endl;
    while(1){
        node *t=qt.front();
         myFile<<(floor+count)<<","<<t->person1<<","<<t->person2<<endl;
        qt.pop_front();
        count++;
        if(qt.size()==0)
        {
            //cout<<"empty qt\n";
            break;
        }
        if(count==100)
        break;
    }
}

void output3(deque<node*> &qt,int floor){
    int count=0;
    ofstream myFile;
    myFile.open("floor3.csv");
    myFile<<"Room_No."<<","<<"Person_1"<<","<<"Person_2"<<endl;
    while(1){
        node *t=qt.front();
         myFile<<(floor+count)<<","<<t->person1<<","<<t->person2<<endl;
        qt.pop_front();
        count++;
        if(qt.size()==0)
        {
            //cout<<"empty qt\n";
            break;
        }
        if(count==100)
        break;
    }
    
}

int main(){
    Data table (5);
    unordered_map<string,node*> node_add; 
    unordered_map<string,vector<string>> neighbors;
    unordered_map<int,vector<node*>> floors;
    stack<node*> st;

    // for (const auto& str : table.header)
    // cout<<str<<" "; cout<<"\n";
    
    for (const auto& vec : table.table) {
        //cout<<table.table.size()<<endl;
        vector<string> temp;
        
        for (const auto& v : vec) 
        {
            //cout<<v<<endl;
            temp.push_back(v);
        }
        
        adj_list(neighbors,temp);
        node *t=create_Node(temp);
        
        if(t->no_of_person==2)
        {
            //cout<<t->no_of_person<<endl;
            map_node(t,node_add);
            floors[stoi(t->floor_no)].push_back(t);
            //cout<<floors[stoi(t->floor_no)].size()<<endl;
        }
        else{
            coupling(st,t);
            if(st.top()->no_of_person==2)
            {
                node *p=st.top();
                st.pop();
                floors[stoi(p->floor_no)].push_back(p);
                map_node(p,node_add);
            }
        }
    }
    allocate_floor1(floors,neighbors,node_add);
    allocate_floor2(floors,neighbors,node_add);
    allocate_floor3(floors,neighbors,node_add);

    // while(!qt.empty()){
    //     cout<<qt.front()->person1<<" "<<qt.front()->person2<<endl;
    //     qt.pop_front();
    // }
    

    output1(qt,100);
    if(qt.size()!=0)
    output2(qt,200);
    if(qt.size()!=0)
    output3(qt,300);
    return 0;
}


