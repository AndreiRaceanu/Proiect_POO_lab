#include<vector>
#include<fstream>
#include<iostream>
#include<map>
#include<algorithm>
#include<iterator>
#include<string>
using namespace std;
class Game
{
    public:
    class User
    {
    public:
    string Surname;
    string Given_name;
    string City;
    int Debt = rand() % 90000 + 10000;
    int Weight = rand() % 50 +50;
    };
    class Competitor:public User
    {
        public:
        Competitor() = default;
        int Competing_number;
        friend bool operator< ( Competitor& a, Competitor& b)
        {
            return a.Competing_number< b.Competing_number;
        }
    };
    class Supervisor:public User
    {
        public:
        void set_mask_shape(string x)
        {
            this->Mask_shape = x;
        }
        string get_mask_shape()
        {
            return Mask_shape;
        }
        int get_suma()
        {
            return this->suma;
        }
        void set_suma(int x)
        {
            this->suma = x;
        }
        friend  bool operator< ( Supervisor& a, Supervisor& b)
        {
            return a.suma> b.suma;
        }
        private:
        int suma;
        string Mask_shape;
    };
    void red_light_green_light();
    void tug_of_war();
    vector<User> Users;
    vector<Supervisor> Supervisors_with_money;
    vector<Competitor> Competitors;
    vector<Competitor> Competitors2; // Are the Competitors who remain after each game
    vector<pair<Supervisor,vector<Competitor>>> Ramasi1;//Is a vector of pairs between supervisor and the competitors who remain after 
    vector<Supervisor> Rectangles;//the first game;
    vector<pair<Supervisor,vector<Competitor>>> Remainders2;//the ones who remain to the very end
    vector<Supervisor> Circles;
    vector<Supervisor> Triangle;
    vector<pair<Supervisor,vector<Competitor>>> V;
    void  setup();
    void Genken();
    void Marbles();
    bool Match(vector<Competitor> V1, Competitor* C1)
    {
        for( auto it = V1.begin();it!=V1.end();it++)
        {
            if(it->City == C1->City && it->Competing_number ==C1->Competing_number && it->Debt==C1->Debt
            && it->Given_name ==C1->Given_name && it->Surname == C1->Surname && it->Weight == C1->Weight)
            {
                return true;
            }
        }
        return false;
    }
     bool Match1(vector<Supervisor> V1, Supervisor* C1)
    {
        for( auto it = V1.begin();it!=V1.end();it++)
        {
            if(it->City == C1->City && it->Debt==C1->Debt 
            && it->Given_name ==C1->Given_name && it->Surname == C1->Surname && it->Weight == C1->Weight)
            {
                return true;
            }
        }
        return false;
    }
};
void Game::setup()
{
    for( int i = 0; i<108;i++)
    {
    User* U1 = new User();
    string surn;
    string cit;
    string g_name;
    // cout<<"Enter your Surname:"<<endl;
    // cin>>surn;
    // cout<<"Enter your given name:"<<"\n";
    // cin>>g_name;
    // cout<<"Enter your city:"<<endl;
    // cin>>cit;
    // U1->Surname = surn;
    // U1->Given_name = g_name;
    // U1->City = cit;
    U1->City = "Bucuresti";
    U1->Given_name = "Andrei";
    U1->Surname = "Raceanu";
    Users.push_back(*U1);
    ofstream File;
    File.open("User_data.csv",ios::app);
    File<<U1->Surname<<","<<U1->Given_name<<","<<U1->City<<","<<U1->Debt<<","<<U1->Weight<<"\n"; 
    delete U1;
    }
    try
    {
        if(Users.size()!=108)
        {
            throw "err";
        }
    }
    catch(const char* input)
    {
        cout<<input;
    }
    //I am going to copy the Users vector in a Copy vector because it might come handy later;
    vector<User> Copy = Users;
    while(true)
    {
        int x = rand() %Copy.size() +0;         //Here I randomly choose an object from the range [0,Size-1], from which 
        Competitor* C = new Competitor();       //I copy the basic info in a pointer;
        User* ptr1 = C;
        ptr1->City = Copy[x].City;              //Polymorphism right here
        ptr1->Debt = Copy[x].Debt;
        ptr1->Given_name = Copy[x].Given_name;
        ptr1->Surname = Copy[x].Surname;
        ptr1->Weight = Copy[x].Weight;
        if(Match(Competitors, C)==false)        //I know this is redundant, because the condition is never going to be true
        {                                     //it can't choose the same object twice since it doesn't exist anymore
            C->Competing_number = Competitors.size();//but in the beginning i planned this to be sort of a checker
            Competitors.push_back(*C);              //if(Match(Competitors,C)) were to be true, then there would have been something
            Copy.erase(Copy.begin()+x);             //wrong with the erase method, same goes for the other while-s;
            if(Competitors.size()==99)
            {
                break;
            }
        }
    }
    vector<User> Copy1 = Copy;
    // cout<<Copy1.size(); meant as a checker;
    while(true)
    {
        int x = rand() %Copy1.size() +0;
        Supervisor* S1 = new Supervisor();
        S1->City = Copy1[x].City;
        S1->Debt=Copy1[x].Debt;
        S1->Given_name =Copy1[x].Given_name;
        S1->set_mask_shape("Triangle");
        S1->Surname = Copy1[x].Surname;
        S1->Weight = Copy1[x].Weight;
        if(Match1(Triangle,S1)==false)
        {
            Triangle.push_back(*S1);
            Copy1.erase(Copy1.begin()+x);
           if(Triangle.size()==3)
           {
               break;
           }
        }
    }

    vector<User> Copy2 = Copy1;
    while(true)
    {
        int x = rand() %Copy2.size() +0;
        Supervisor* S1 = new Supervisor();
        S1->City = Copy2[x].City;
        S1->Debt=Copy2[x].Debt;
        S1->Given_name =Copy2[x].Given_name;
        S1->set_mask_shape ("Circle");
        S1->Surname = Copy2[x].Surname;
        S1->Weight = Copy2[x].Weight;
        if(Match1(Circles,S1)==false)
        {
            Circles.push_back(*S1);
            Copy2.erase(Copy2.begin()+x);
            if(Circles.size()==3)
            {
                break;
            }
        }
    }
    vector<User> Copy3 = Copy2;
    while(true)
    {
        int x = rand() %Copy3.size() +0;
        Supervisor* S1 = new Supervisor();
        S1->City = Copy3[x].City;
        S1->Debt=Copy3[x].Debt;
        S1->Given_name =Copy3[x].Given_name;
        S1->set_mask_shape("Rectangle");
        S1->Surname = Copy3[x].Surname;
        S1->Weight = Copy3[x].Weight;
        if(Match1(Rectangles,S1)==false)
        {
            Rectangles.push_back(*S1);
            Copy3.erase(Copy3.begin()+x);
            if(Rectangles.size()==3)
            {
                break;
            }
        }
    }
  vector<Competitor> V1;
  V1.push_back(*(Competitors.begin()));
  V1.push_back(*(Competitors.begin()+1));
  V1.push_back(*(Competitors.begin()+2));
  V1.push_back(*(Competitors.begin()+3));
  V1.push_back(*(Competitors.begin()+4));
  V1.push_back(*(Competitors.begin()+5));
  V1.push_back(*(Competitors.begin()+6));
  V1.push_back(*(Competitors.begin()+7));
  V1.push_back(*(Competitors.begin()+8));
  V1.push_back(*(Competitors.begin()+9));
  V1.push_back(*(Competitors.begin()+10));
  vector<Competitor> V2;
  V2.push_back(*(Competitors.begin()+11));
  V2.push_back(*(Competitors.begin()+12));
  V2.push_back(*(Competitors.begin()+13));
  V2.push_back(*(Competitors.begin()+14));
  V2.push_back(*(Competitors.begin()+15));
  V2.push_back(*(Competitors.begin()+16));
  V2.push_back(*(Competitors.begin()+17));
  V2.push_back(*(Competitors.begin()+18));
  V2.push_back(*(Competitors.begin()+19));
  V2.push_back(*(Competitors.begin()+20));
  V2.push_back(*(Competitors.begin()+21));
    vector<Competitor> V3;
  V3.push_back(*(Competitors.begin()+22));
  V3.push_back(*(Competitors.begin()+23));
  V3.push_back(*(Competitors.begin()+24));
  V3.push_back(*(Competitors.begin()+25));
  V3.push_back(*(Competitors.begin()+26));
  V3.push_back(*(Competitors.begin()+27));
  V3.push_back(*(Competitors.begin()+28));
  V3.push_back(*(Competitors.begin()+29));
  V3.push_back(*(Competitors.begin()+30));
  V3.push_back(*(Competitors.begin()+31));
  V3.push_back(*(Competitors.begin()+32));
   vector<Competitor> V4;
  V4.push_back(*(Competitors.begin()+33));
  V4.push_back(*(Competitors.begin()+34));
  V4.push_back(*(Competitors.begin()+35));
  V4.push_back(*(Competitors.begin()+36));
  V4.push_back(*(Competitors.begin()+37));
  V4.push_back(*(Competitors.begin()+38));
  V4.push_back(*(Competitors.begin()+39));
  V4.push_back(*(Competitors.begin()+40));
  V4.push_back(*(Competitors.begin()+41));
  V4.push_back(*(Competitors.begin()+42));
  V4.push_back(*(Competitors.begin()+43));
  vector<Competitor> V5;
   V5.push_back(*(Competitors.begin()+44));
  V5.push_back(*(Competitors.begin()+45));
  V5.push_back(*(Competitors.begin()+46));
  V5.push_back(*(Competitors.begin()+47));
  V5.push_back(*(Competitors.begin()+48));
  V5.push_back(*(Competitors.begin()+49));
  V5.push_back(*(Competitors.begin()+50));
  V5.push_back(*(Competitors.begin()+51));
  V5.push_back(*(Competitors.begin()+52));
  V5.push_back(*(Competitors.begin()+53));
  V5.push_back(*(Competitors.begin()+54));
   vector<Competitor> V6;
   V6.push_back(*(Competitors.begin()+55));
  V6.push_back(*(Competitors.begin()+56));
  V6.push_back(*(Competitors.begin()+57));
  V6.push_back(*(Competitors.begin()+58));
  V6.push_back(*(Competitors.begin()+59));
  V6.push_back(*(Competitors.begin()+60));
  V6.push_back(*(Competitors.begin()+61));
  V6.push_back(*(Competitors.begin()+62));
  V6.push_back(*(Competitors.begin()+63));
  V6.push_back(*(Competitors.begin()+64));
  V6.push_back(*(Competitors.begin()+65));
  vector<Competitor> V7;
   V7.push_back(*(Competitors.begin()+66));
  V7.push_back(*(Competitors.begin()+67));
  V7.push_back(*(Competitors.begin()+68));
  V7.push_back(*(Competitors.begin()+69));
  V7.push_back(*(Competitors.begin()+70));
  V7.push_back(*(Competitors.begin()+71));
  V7.push_back(*(Competitors.begin()+72));
  V7.push_back(*(Competitors.begin()+73));
  V7.push_back(*(Competitors.begin()+74));
  V7.push_back(*(Competitors.begin()+75));
  V7.push_back(*(Competitors.begin()+76));
  vector<Competitor> V8;
   V8.push_back(*(Competitors.begin()+77));
  V8.push_back(*(Competitors.begin()+78));
  V8.push_back(*(Competitors.begin()+79));
  V8.push_back(*(Competitors.begin()+80));
  V8.push_back(*(Competitors.begin()+81));
  V8.push_back(*(Competitors.begin()+82));
  V8.push_back(*(Competitors.begin()+83));
  V8.push_back(*(Competitors.begin()+84));
  V8.push_back(*(Competitors.begin()+85));
  V8.push_back(*(Competitors.begin()+86));
  V8.push_back(*(Competitors.begin()+87));
   vector<Competitor> V9;
   V9.push_back(*(Competitors.begin()+88));
  V9.push_back(*(Competitors.begin()+89));
  V9.push_back(*(Competitors.begin()+90));
  V9.push_back(*(Competitors.begin()+91));
  V9.push_back(*(Competitors.begin()+92));
  V9.push_back(*(Competitors.begin()+93));
  V9.push_back(*(Competitors.begin()+94));
  V9.push_back(*(Competitors.begin()+95));
  V9.push_back(*(Competitors.begin()+96));
  V9.push_back(*(Competitors.begin()+97));
  V9.push_back(*(Competitors.begin()+98));
  V.push_back(make_pair(Triangle[0],V1));
  V.push_back(make_pair(Triangle[1],V2));
  V.push_back(make_pair(Triangle[2],V3));
  V.push_back(make_pair(Circles[0],V4));
  V.push_back(make_pair(Circles[1],V5));
  V.push_back(make_pair(Circles[2],V6));
  V.push_back(make_pair(Rectangles[0],V7));
  V.push_back(make_pair(Rectangles[1],V8));
  V.push_back(make_pair(Rectangles[2],V9));
//   for( int i =0;i<9;i++)
//   {
//       for(int j =0;j<11;j++)
//       {
//           cout<<V[i].second[j].Competing_number<<" ";
//       }
//       cout<<"\n";
//   }
}  
void Game::red_light_green_light()
{
    //that's what happens when you get your iterators invalidated and you don't know what struck you, thx ce++
    vector<Competitor> V_1;
    for( int i=0;i<11;i++)
    {
        if(V[0].second[i].Competing_number%2==1)
        {
            V_1.push_back(V[0].second[i]);
        }
    }
    // for(auto it = V_1.begin();it!=V_1.end();it++)
    // {
        // cout<<it->Competing_number<<" ";
    // }
    Ramasi1.push_back(make_pair(V[0].first,V_1));
    vector<Competitor> V_2;
    for( int i=0;i<11;i++)
    {
        if(V[1].second[i].Competing_number%2==1)
        {
            V_2.push_back(V[1].second[i]);
        }
    }
    Ramasi1.push_back(make_pair(V[1].first,V_2));
    vector<Competitor> V_3;
    for( int i=0;i<11;i++)
    {
        if(V[2].second[i].Competing_number%2==1)
        {
            V_3.push_back(V[2].second[i]);
        }
    }
    Ramasi1.push_back(make_pair(V[2].first,V_3));
    vector<Competitor> V_4;
    for( int i=0;i<11;i++)
    {
        if(V[3].second[i].Competing_number%2==1)
        {
            V_4.push_back(V[3].second[i]);
        }
    }
    Ramasi1.push_back(make_pair(V[3].first,V_4));
    vector<Competitor> V_5;
    for( int i=0;i<11;i++)
    {
        if(V[4].second[i].Competing_number%2==1)
        {
            V_5.push_back(V[4].second[i]);
        }
    }
    Ramasi1.push_back(make_pair(V[4].first,V_5));
    vector<Competitor> V_6;
    for( int i=0;i<11;i++)
    {
        if(V[5].second[i].Competing_number%2==1)
        {
            V_6.push_back(V[5].second[i]);
        }
    }
    Ramasi1.push_back(make_pair(V[5].first,V_6));
     vector<Competitor> V_7;
    for( int i=0;i<11;i++)
    {
        if(V[6].second[i].Competing_number%2==1)
        {
            V_7.push_back(V[6].second[i]);
        }
    }
    Ramasi1.push_back(make_pair(V[6].first,V_7));
    vector<Competitor> V_8;
    for( int i=0;i<11;i++)
    {
        if(V[7].second[i].Competing_number%2==1)
        {
            V_8.push_back(V[7].second[i]);
        }
    }
    Ramasi1.push_back(make_pair(V[7].first,V_8));
    vector<Competitor> V_9;
    for( int i=0;i<11;i++)
    {
        if(V[8].second[i].Competing_number%2==1)
        {
            V_9.push_back(V[8].second[i]);
        }
    }
    Ramasi1.push_back(make_pair(V[8].first,V_9));
    //#this is what happens when .erase doesnt work as intended, thx ce++;
    for(auto it = Ramasi1.begin();it!=Ramasi1.end();it++)
    {
        for(auto i = it->second.begin();i!=it->second.end();i++)
        {
            Competitors2.push_back(*i);
        }
    }
    for(auto it = Competitors2.begin();it!=Competitors2.end();it++)
    {
        cout<<it->City<<" "<<it->Competing_number<<" "<<it->Debt<<" "<<it->Given_name<<" "<<it->Surname<<" "<<it->Weight<<"\n";
    }
    cout<<"***********************************************************************************************\n";
    cout<<"Upper are listed the ones who passed the first round of the game\n";
    //cout<<Competitors2.size();
}
void Game::tug_of_war()
{
    vector<Competitor> Team_1;
    vector<Competitor> Team_2;
    vector<Competitor> Winners;
    vector<Competitor> Team_3;
    vector<Competitor> Team_4;
    while(true)
    {
        int x = rand() %Competitors2.size() + 0;
        if(Match(Team_1,&Competitors2[x])==false)
        {
            Team_1.push_back(Competitors2[x]);
            Competitors2.erase(Competitors2.begin()+x);
        }
        if(Team_1.size()==12)
        {
            break;
        }
    }
    while(true)
    {
        int x = rand() %Competitors2.size()+0;
        if(Match(Team_2,&Competitors2[x])==false)
        {
            Team_2.push_back(Competitors2[x]);
            Competitors2.erase(Competitors2.begin()+x);
        }
        if(Team_2.size()==12)
        {
            break;
        }
    }
    while(true)
    {
        int x = rand()%Competitors2.size()+0;
        if(Match(Team_3,&Competitors2[x])==false)
        {
            Team_3.push_back(Competitors2[x]);
            Competitors2.erase(Competitors2.begin()+x);
        }
        if(Team_3.size()==12)
        {
            break;
        }
    }
    while(true)
    {
        int x = rand()%Competitors2.size()+0;
        if(Match(Team_4,&Competitors2[x])==false)
        {
            Team_4.push_back(Competitors2[x]);
            Competitors2.erase(Competitors2.begin()+x);
        }
        if(Team_4.size()==12)
        {
            break;
        }
    }
    //The documentation says that in tug of war the teams are going to be put one againt another 2 by 2, and be eliminated
    //if their weight is smaller, so the ones who will remain is the team with bigger weight;
    // cout<<Competitors2.size();//As a checker
    Competitor C1;
    C1.City = Competitors2.front().City;
    C1.Competing_number = Competitors2.front().Competing_number;
    C1.Debt = Competitors2.front().Debt;
    C1.Given_name = Competitors2.front().Given_name;
    C1.Surname = Competitors2.front().Surname;
    C1.Weight = Competitors2.front().Weight;
    int s1,s2,s3,s4 = 0;
    for(auto it = Team_1.begin();it!=Team_1.end();it++)
    {
        s1 = s1+it->Weight;
    }
     for(auto it = Team_2.begin();it!=Team_2.end();it++)
    {
        s2 = s2+it->Weight;
    }
     for(auto it = Team_3.begin();it!=Team_3.end();it++)
    {
        s3 = s3+it->Weight;
    }
     for(auto it = Team_4.begin();it!=Team_4.end();it++)
    {
        s4 = s4+it->Weight;
    }
    if(s4>s1 && s4> s2 && s4> s3)
    {
        for( int i=0;i<12;i++)
        {
            Competitors2.push_back(Team_4[i]);
        }
        for(auto it = Team_4.begin();it!=Team_4.end();it++)
        {
            Winners.push_back(*it);
        }
    }
    if(s3>s1 && s3> s2 && s3> s4)
    {
        for( int i=0;i<12;i++)
        {
            Competitors2.push_back(Team_3[i]);
        }
        for(auto it = Team_3.begin();it!=Team_3.end();it++)
        {
            Winners.push_back(*it);
        }
    }
    if(s2>s1 && s2> s3 && s2> s4)
    {
        for( int i=0;i<12;i++)
        {
            Competitors2.push_back(Team_2[i]);
        }
         for(auto it = Team_2.begin();it!=Team_2.end();it++)
        {
            Winners.push_back(*it);
        }
    }
    if(s1>s2 && s1> s3 && s1> s4)
    {
        for( int i=0;i<12;i++)
        {
            Competitors2.push_back(Team_1[i]);
        }
         for(auto it = Team_2.begin();it!=Team_2.end();it++)
        {
            Winners.push_back(*it);
        }
    }
    //let's now hope this will not end up in invalidated iterators, because then, i have to make another vector of pairs
    //with the ones remaing;
    // for(auto it = Ramasi1.begin();it!=Ramasi1.end();it++)
    // {
    //     for(auto i = it->second.begin();i!=it->second.end();i++)
    //     {
    //         for(auto j = Losers.begin();j!=Losers.end();j++)
    //         {
    //             if(j->Competing_number==i->Competing_number)
    //             {
    //                 it->second.erase(i);
    //             }
    //         }
    //     }
    // }
    // well, the iterators are invalidated;
    vector<Competitor> V1;
    vector<Competitor> V2;
    vector<Competitor> V3;
    vector<Competitor> V4;
    vector<Competitor> V5;
    vector<Competitor> V6;
    vector<Competitor> V7;
    vector<Competitor> V8;
    vector<Competitor> V9;
    for(auto it = Winners.begin();it!=Winners.end();it++)
    {
        if(it->Competing_number>=0 && it->Competing_number<=10)
        {
            V1.push_back(*it);
        }
        if(it->Competing_number>=11 && it->Competing_number<=21)
        {
            V2.push_back(*it);
        }
        if(it->Competing_number>=22 && it->Competing_number<=32)
        {
            V3.push_back(*it);
        }
        if(it->Competing_number>=33 && it->Competing_number<=43)
        {
            V4.push_back(*it);
        }
        if(it->Competing_number>=44 && it->Competing_number<=54)
        {
            V5.push_back(*it);
        }
        if(it->Competing_number>=55 && it->Competing_number<=65)
        {
            V6.push_back(*it);
        }
        if(it->Competing_number>=66 && it->Competing_number<=76)
        {
            V7.push_back(*it);
        }
        if(it->Competing_number>=77 && it->Competing_number<=87)
        {
            V8.push_back(*it);
        }
        if(it->Competing_number>=88 && it->Competing_number<=98)
        {
            V9.push_back(*it);
        }
    }
    if(C1.Competing_number>=0 && C1.Competing_number<=10)
        {
            V1.push_back(C1);
        }
        if(C1.Competing_number>=11 && C1.Competing_number<=21)
        {
            V2.push_back(C1);
        }
        if(C1.Competing_number>=22 && C1.Competing_number<=32)
        {
            V3.push_back(C1);
        }
        if(C1.Competing_number>=33 && C1.Competing_number<=43)
        {
            V4.push_back(C1);
        }
        if(C1.Competing_number>=44 && C1.Competing_number<=54)
        {
            V5.push_back(C1);
        }
        if(C1.Competing_number>=55 && C1.Competing_number<=65)
        {
            V6.push_back(C1);
        }
        if(C1.Competing_number>=66 && C1.Competing_number<=76)
        {
            V7.push_back(C1);
        }
        if(C1.Competing_number>=77 && C1.Competing_number<=87)
        {
            V8.push_back(C1);
        }
        if(C1.Competing_number>=88 && C1.Competing_number<=98)
        {
            V9.push_back(C1);
        }
      Remainders2.push_back(make_pair(Ramasi1[0].first,V1));
        Remainders2.push_back(make_pair(Ramasi1[1].first,V2));
        Remainders2.push_back(make_pair(Ramasi1[2].first,V3));
        Remainders2.push_back(make_pair(Ramasi1[3].first,V4));
        Remainders2.push_back(make_pair(Ramasi1[4].first,V5));
        Remainders2.push_back(make_pair(Ramasi1[5].first,V6));
        Remainders2.push_back(make_pair(Ramasi1[6].first,V7));
        Remainders2.push_back(make_pair(Ramasi1[7].first,V8));
        Remainders2.push_back(make_pair(Ramasi1[8].first,V9));
        // for(auto it = Competitors2.begin();it!=Competitors2.end();it++)
        // {
        //     cout<<it->Competing_number<<" ";
        // }
        // cout<<"TESTING"<<endl;
        for(auto it= Remainders2.begin();it!=Remainders2.end();it++)
        {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
                cout<<i->City<<" "<<i->Competing_number<<" "<<i->Debt<<" "<<i->Given_name<<" "<<i->Surname<<" "<<i->Weight<<"\n";
            }
        }
    cout<<"*******************************************************************************\n";
    cout<<"Upper are listed the ones who made it through the second game\n";
    // cout<<Competitors2.size(); As a checker;
}
void Game::Marbles()
{
    
    int x,y;
    x = rand()%1000;
    y= rand()%1000;
    if(x<y)
    {         
        for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[1].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
            Competitors2.erase(Competitors2.begin()+1);
    } 
    else
    {    
        for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                    {
                        for(auto i = it->second.begin();i!=it->second.end();i++)
                        {
                             if(Competitors2[0].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
                        }
                    } 
        Competitors2.erase(Competitors2.begin());
    }
    int x1,y1;
    x1 = rand()%1000;
    y1= rand()%1000;
    if(x1<y1)
    {
         for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[2].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
        Competitors2.erase(Competitors2.begin()+2);
    } 
    else
    {
         for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[1].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
        Competitors2.erase(Competitors2.begin()+1);
    }
     int x2,y2;
    x2 = rand()%1000;
    y2= rand()%1000;
    if(x2<y2)
    {
         for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[3].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
        Competitors2.erase(Competitors2.begin()+3);
    } 
    else
    {
            for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[2].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             }  
        Competitors2.erase(Competitors2.begin()+2);
    }
    int x3,y3;
    x3=rand()%1000;
    y3=rand()%1000;
    if(x3<y3)
    {
            for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[4].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             }  
        Competitors2.erase(Competitors2.begin()+4);
    }
    else
    {
        for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[3].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
        Competitors2.erase(Competitors2.begin()+3);
    }
    int x4,y4;
    x4=rand()%1000;
    y4 = rand()%1000;
    if(x4<y4)
    {
for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[5].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
        Competitors2.erase(Competitors2.begin()+5);
    }
    else
    {
        for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[4].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
        Competitors2.erase(Competitors2.begin()+4);
    }
    int x5,y5;
    x5=rand()%1000;
    y5=rand()%1000;
    if(x5<y5)
    {
 for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[6].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
        Competitors2.erase(Competitors2.begin()+6);
    }
    else
    {
         for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
            {
            for(auto i = it->second.begin();i!=it->second.end();i++)
            {
            if(Competitors2[5].Competing_number==i->Competing_number)
            {
             it->second.erase(i);
             break;
            }
             }
             } 
        Competitors2.erase(Competitors2.begin()+5);
    }
    for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
    {
        for(auto i = it->second.begin();i!=it->second.end();i++)
        {
            cout<<i->City<<" "<<i->Competing_number<<" "<<i->Debt<<" "<<i->Given_name<<" "<<i->Surname<<" "<<i->Weight<<" \n";
        }
    }
    cout<<"*******************************************************************************\n";
    cout<<"Up above are listed the ones who finished the 3rd game\n";
    //  cout<<Competitors2.size(); //As a checker,because no matter what comes after these 3 games, it is mandatory that at the end
    //7 players to remain;
}
void Game::Genken()
{
    sort(Competitors2.begin(),Competitors2.end());
    // for(auto it = Competitors2.begin();it!=Competitors2.end();it++)
    // {
    //     cout<<it->Competing_number<<" ";
    // } As a checker to see if the sort method worked as intended using the < operator;
        int x, y;
        x = rand()%3 + 1;
        y = rand()%3 +1;
       if( x==1)
       {
           if(y==1)
           {
               while(true)
               {
                   y = rand()%3+1;
                   if(x!=y)
                   {
                       if(y==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+5);
                       }
                       if(y==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[6].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+6);
                       }
                       break;
                   }
               }
           }
          else if ( y==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[6].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+6);
          }
          else if( y==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+5);
          }
       }
       if(x==2)
       {
             if(y==2)
           {
               while(true)
               {
                   y = rand()%3+1;
                   if(x!=y)
                   {
                       if(y==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+5);
                       }
                       if(y==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[6].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+6);
                       }
                       break;
                   }
               }
           }
          else if ( y==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+5);
          }
          else if( y==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[6].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+6);
          }
       }
          if(x==3)
       {
             if(y==3)
           {
               while(true)
               {
                   y = rand()%3+1;
                   if(x!=y)
                   {
                       if(y==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[6].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+6);
                       }
                       if(y==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+5);
                       }
                       break;
                   }
               }
           }
          else if ( y==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[6].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+6);
          }
          else if( y==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+5);
          }
       }
    // cout<<Competitors2.size()<<" "; //As a checker, it has to be 6, and it is;
    // for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
    // {
    //     for(auto i = it->second.begin();i!=it->second.end();i++)
    //     {
    //         cout<<i->Competing_number<< " ";
    //     }
    // }
            int x1, y1;
        x1 = rand()%3 + 1;
        y1 = rand()%3 +1;
       if( x1==1)
       {
           if(y1==1)
           {
               while(true)
               {
                   y1 = rand()%3+1;
                   if(x1!=y1)
                   {
                       if(y1==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+4);
                       }
                       if(y1==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+5);
                       }
                       break;
                   }
               }
           }
          else if ( y1==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+5);
          }
          else if( y1==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+4);
          }
       }
       if(x1==2)
       {
             if(y1==2)
           {
               while(true)
               {
                   y1 = rand()%3+1;
                   if(x!=y)
                   {
                       if(y1==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+4);
                       }
                       if(y1==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+5);
                       }
                       break;
                   }
               }
           }
          else if ( y1==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+4);
          }
          else if( y1==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+5);
          }
       }
          if(x1==3)
       {
             if(y1==3)
           {
               while(true)
               {
                   y1 = rand()%3+1;
                   if(x1!=y1)
                   {
                       if(y1==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+5);
                       }
                       if(y1==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+4);
                       }
                       break;
                   }
               }
           }
          else if ( y1==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[5].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+5);
          }
          else if( y1==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+4);
          }
       }
    // cout<<Competitors2.size()<<" "; //As a checker, it has to be 5, and it is;
    // for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
    // {
    //     for(auto i = it->second.begin();i!=it->second.end();i++)
    //     {
    //         cout<<i->Competing_number<< " ";
    //     }
    // }
                int x2, y2;
        x2 = rand()%3 + 1;
        y2 = rand()%3 +1;
       if( x2==1)
       {
           if(y2==1)
           {
               while(true)
               {
                   y2 = rand()%3+1;
                   if(x2!=y2)
                   {
                       if(y2==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+3);
                       }
                       if(y2==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+4);
                       }
                       break;
                   }
               }
           }
          else if ( y2==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+4);
          }
          else if( y2==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+3);
          }
       }
       if(x2==2)
       {
             if(y2==2)
           {
               while(true)
               {
                   y2 = rand()%3+1;
                   if(x2!=y2)
                   {
                       if(y2==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+3);
                       }
                       if(y2==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+4);
                       }
                       break;
                   }
               }
           }
          else if ( y2==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+3);
          }
          else if( y2==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+4);
          }
       }
          if(x2==3)
       {
             if(y2==3)
           {
               while(true)
               {
                   y2 = rand()%3+1;
                   if(x2!=y2)
                   {
                       if(y2==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+4);
                       }
                       if(y2==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+3);
                       }
                       break;
                   }
               }
           }
          else if ( y2==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[4].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+4);
          }
          else if( y2==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+3);
          }
       }
    // cout<<Competitors2.size()<<" "; //As a checker, it has to be 4, and it is;
    // for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
    // {
    //     for(auto i = it->second.begin();i!=it->second.end();i++)
    //     {
    //         cout<<i->Competing_number<< " ";
    //     }
    // }
    int x3, y3;
    x3=rand()%3+1;
    y3 = rand()%3+1;
       if( x3==1)
       {
           if(y3==1)
           {

               while(true)
               {
                   y3 = rand()%3+1;
                   if(x3!=y3)
                   {
                       if(y3==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+2);
                       }
                       if(y3==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+3);
                       }
                       break;
                   }
               }
           }
          else if ( y3==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+3);
          }
          else if( y3==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+2);
          }
       }
       if(x3==2)
       {
             if(y3==2)
           {
               while(true)
               {
                   y3 = rand()%3+1;
                   if(x3!=y3)
                   {
                       if(y3==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+2);
                       }
                       if(y3==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+3);
                       }
                       break;
                   }
               }
           }
          else if ( y3==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+2);
          }
          else if( y3==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+3);
          }

       }
          if(x3==3)
       {
             if(y3==3)
           {
               while(true)
               {
                   y3 = rand()%3+1;
                   if(x3!=y3)
                   {
                       if(y3==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+3);
                       }
                       if(y3==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+2);
                       }
                       break;
                   }
               }
           }
          else if ( y3==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[3].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+3);
          }
          else if( y3==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+2);
          }

       }
    // cout<<Competitors2.size()<<" "; //As a checker, it has to be 3, and it is;
    // for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
    // {
    //     for(auto i = it->second.begin();i!=it->second.end();i++)
    //     {
    //         cout<<i->Competing_number<< " ";
    //     }
    // }
          int x4, y4;
    x4=rand()%3+1;
    y4 = rand()%3+1;
       if( x4==1)
       {
           if(y4==1)
           {

               while(true)
               {
                   y4 = rand()%3+1;
                   if(x4!=y4)
                   {
                       if(y4==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+1);
                       }
                       if(y4==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+2);
                       }
                       break;
                   }
               }
           }
          else if ( y4==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+2);
          }
          else if( y4==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+1);
          }
       }
       if(x4==2)
       {
             if(y4==2)
           {
               while(true)
               {
                   y4 = rand()%3+1;
                   if(x4!=y4)
                   {
                       if(y4==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+1);
                       }
                       if(y4==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+2);
                       }
                       break;
                   }
               }
           }
          else if ( y4==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+1);
          }
          else if( y4==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+2);
          }

       }
          if(x4==3)
       {
             if(y4==3)
           {
               while(true)
               {
                   y4 = rand()%3+1;
                   if(x4!=y4)
                   {
                       if(y4==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+2);
                       }
                       if(y4==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+1);
                       }
                       break;
                   }
               }
           }
          else if ( y4==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+2);
          }
          else if( y4==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+1);
          }

       }
    // cout<<Competitors2.size()<<" "; //As a checker, it has to be 2, and it is;
    // for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
    // {
    //     for(auto i = it->second.begin();i!=it->second.end();i++)
    //     {
    //         cout<<i->Competing_number<< " ";
    //     }
    // }
        int x5, y5;
    x5=rand()%3+1;
    y5 = rand()%3+1;
       if( x5==1)
       {
           if(y5==1)
           {

               while(true)
               {
                   y5 = rand()%3+1;
                   if(x5!=y5)
                   {
                       if(y5==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[0].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+0);
                       }
                       if(y5==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+1);
                       }
                       break;
                   }
               }
           }
          else if ( y5==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[0].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+1);
          }
          else if( y5==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+1);
          }
       }
       if(x5==2)
       {
             if(y5==2)
           {
               while(true)
               {
                   y5 = rand()%3+1;
                   if(x5!=y5)
                   {
                       if(y5==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[0].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+0);
                       }
                       if(y5==3)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+1);
                       }
                       break;
                   }
               }
           }
          else if ( y5==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[0].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+0);
          }
          else if( y5==3)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+1);
          }

       }
          if(x5==3)
       {
             if(y5==3)
           {
               while(true)
               {
                   y5 = rand()%3+1;
                   if(x5!=y5)
                   {
                       if(y5==1)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[1].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+1);
                       }
                       if(y5==2)
                       {
                           for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[0].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
                           Competitors2.erase(Competitors2.begin()+0);
                       }
                       break;
                   }
               }
           }
          else if ( y5==1)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[2].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+2);
          }
          else if( y5==2)
          {
              for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
                           {
                               for(auto i = it->second.begin();i!=it->second.end();i++)
                               {
                                   if(i->Competing_number == Competitors2[0].Competing_number)
                                   {
                                       it->second.erase(i);
                                       break;
                                   }
                               }
                           }
              Competitors2.erase(Competitors2.begin()+0);
          }

       }
    // cout<<Competitors2.size()<<" "; //As a checker, it has to be 1, and it is;
    // for(auto it = Remainders2.begin();it!=Remainders2.end();it++)
    // {
    //     for(auto i = it->second.begin();i!=it->second.end();i++)
    //     {
    //         cout<<i->Competing_number<< " ";
    //     }
    // }
    cout<<"****************************************************************************\n";
    cout<<"The one and only who made it after 4 games is:\n";
    // cout<<Competitors2.size()<<" "<<endl;
    cout<<Competitors2.front().City<<" "<<Competitors2.front().Competing_number<<" "<<Competitors2.front().Debt<<" "<<Competitors2.front().Given_name<<" "<<Competitors2.front().Surname<<" "<<Competitors2.front().Weight<<" "<<endl;
}
int main()
{
    Game G1;
    G1.setup();
    G1.red_light_green_light();
    G1.tug_of_war();
    G1.Marbles();
    G1.Genken();
    int s=0;
    for(auto it = G1.Competitors.begin();it!=G1.Competitors.end();it++)
    {
        if(it->Competing_number==G1.Competitors2.front().Competing_number)
        {
            continue;
        }
        s=s+it->Debt;
    }
    cout<<"***********************************************\n";
    cout<<"The champion won:\n";
    cout<<s<<"\n";
    //each supervisor will receive the amount of money his competing team was worth in debt - personal debt
    //the supervisor which had the winner monitored will receive 10 times the winner's debt as reward - personal debt
    int i=0;
    for(auto it = G1.Remainders2.begin();it!=G1.Remainders2.end();it++)
    {
        if(it->second.size()==0)
        {
            for(auto j = G1.V[i].second.begin();j!=G1.V[i].second.end();j++)
            {
                G1.V[i].first.set_suma(G1.V[i].first.get_suma() + j->Debt);
            }
            G1.V[i].first.set_suma(G1.V[i].first.get_suma() - G1.V[i].first.Debt);
            G1.Supervisors_with_money.push_back(G1.V[i].first);
        }
        if(it->second.size()==1)
        {
            G1.V[i].first.set_suma(G1.Competitors2.front().Debt * 10 - G1.V[i].first.Debt);
            G1.Supervisors_with_money.push_back(G1.V[i].first);
        }
        i++;
    }
    sort(G1.Supervisors_with_money.begin(),G1.Supervisors_with_money.end());
    cout<<"********************************************************8\n";
    cout<<"The supervisors after their received money in descending order are:\n";
    for(auto it = G1.Supervisors_with_money.begin();it!=G1.Supervisors_with_money.end();it++)
    {
        cout<<it->City<<" "<<it->Debt<<" "<<it->Given_name<<" "<<it->get_mask_shape()<<" "<<it->Surname<<" "<<it->Weight<<" With the gain "<<it->get_suma()<<"\n";
    }
    int s1,s2,s3=0;
    for(auto it = G1.Circles.begin();it!=G1.Circles.end();it++)
    {
        s1 =s1 +it->get_suma();
    }
    for(auto it = G1.Triangle.begin();it!=G1.Triangle.end();it++)
    {
        s2 =s2 + it->get_suma();
    }
    for(auto it = G1.Rectangles.begin();it!=G1.Rectangles.end();it++)
    {
        s3 = s3 + it->get_suma();
    }
    cout<<"*********************************************************\n";
    cout<<"The team of supervisors who gained the most money is...\n";
    if(s1>s2 && s1>s3)
    {
        cout<<"Circles";
    }
    else if( s2>s1 && s2>s3)
    {
        cout<<"Triangle";
    }
    else if(s3>s1 && s3> s2)
    {
        cout<<"Rectangles";
    }
}