#include<bits/stdc++.h>
#include <cstdlib>
#include<unistd.h> 
#include <iostream>
using namespace std;
vector<pair<int,int>> steps={{1,0},{-1,0},{0,1},{0,-1}};
map<pair<int,int>,char> directions={{{1,0},'D'},{{-1,0},'U'},{{0,1},'R'},{{0,-1},'L'}};
#define bigstruct pair< int, pair<int,int> >
int mod;
set<pair<int,int>> strange_coins;
void intro()        // This prints the instructions of the game
{
    cout<<"-----------------------------------------------------------Welcome to Demo Dogs Game------------------------------------------------------------------"<<endl<<endl;
    cout<<"You are in hawkins and were kidnaped by Vecna and bought to upside down. Now you wakeup and got chance to escape.\n\n";
    cout<<"Inorder to get out of Upside Down you have to reach the gate at (9,9) co-ordinate of upside down which connects to hawkins lab and you are currently at (0,0).\n\n";
    cout<<"In this game Upside game is a 10 by 10 matrix and things are not that simple Vecna knew you escape and he sent demodogs and demobats behind you.";
    cout<<"\n\nDemo Creatures are fixed and spread over Upside Down in your hunt.";
    cout<<"\n\nOnce you kill all demo creatures of a place they again come to life after you move to other place this is because of somekind of magical spell by Vecna.";
    cout<<"\n\nEach time you encounter a democreatures you fought them and this decrease your health which is intially 100000 strange points";
    cout<<" by the strange power of democreatures.\n\nAditionally their are some strange coins spreaded over Upside down.\n\nA strange coin is something that can either suggest you a direction where you should move to get minimum loss or tell you nearest location of other strange coin.";
    cout<<"\n\nIntially you have only 3 strange coins which were given to you by El before you were kidnaped for your safety.";
    cout<<"\n\nIn each turn your position will be shown to you and direction in which you want to go is asked, remember there are only limited strange coins so use wisely.\n\n";
    cout<<"If your health points reduced to zero or below you are dead.\n\nIf you tried to step out of Upside Down Vecna will track you and you will be killed.";
    cout<<"\n\n                Best of Luck get out of Upside Down\n\n";
    cout<<"Loading.........................";
    sleep(100);
    system("cls");
}
class Board
{
    public:
    vector<vector<int>> board,hint_board;
    Board()     // Intizialize the powers of democreatures and strange coins locations.
    {
        for(int i=0;i<10;i++)
        {
            vector<int> z;
            for(int j=0;j<10;j++)
            {
                int num=-(rand()%mod);
                z.push_back(num);
            }
            board.push_back(z);
        }
        hint_board=vector<vector<int>>(10,vector<int>(10));
        int coins=min(50,rand()%mod);
        while(coins--)
        {
            int i,j;
            i=rand()%10;
            j=rand()%10;
            hint_board[i][j]+=1;
            strange_coins.insert({i,j});
        }
    }
    char shortestpath(int i,int j,int val)      // This uses dijkstra's algorithm to find path whith minimum loss and also find direction of one such path from choosen node in which we should procced.
    {
        vector<vector<int>> tmp=vector<vector<int>>(10,vector<int>(10,INT_MIN));
        vector<vector<pair<int,int>>> lstvisit(10,vector<pair<int,int>>(10,{-1,-1}));
        priority_queue<bigstruct, vector<bigstruct>, greater<bigstruct> > pq;
        pq.push({val,{i,j}});
        tmp[i][j]=val;
        while(pq.size())
        {
            int p=pq.top().second.first;
            int q=pq.top().second.second;
            int points=pq.top().first;
            pq.pop();
            for(auto x:steps)
            {
                if(p+x.first<10 and p+x.first>=0 and q+x.second<10 and q+x.second>=0)
                {
                    if(tmp[p][q]+board[p+x.first][q+x.second]>tmp[p+x.first][q+x.second])
                    {
                        tmp[p+x.first][q+x.second]=tmp[p][q]+board[p+x.first][q+x.second];
                        pq.push({tmp[p+x.first][q+x.second],{p+x.first,q+x.second}});
                        lstvisit[p+x.first][q+x.second]={p,q};
                    }
                }
            }
        }
        pair<int,int> curr_pos={9,9},req_pos;
        while(curr_pos!=make_pair(i,j))
        {   
            if(lstvisit[curr_pos.first][curr_pos.second]==make_pair(i,j))req_pos=curr_pos;
            curr_pos=lstvisit[curr_pos.first][curr_pos.second];
        }
        return directions[{req_pos.first-i,req_pos.second-j}];
    }
    pair<int,int> strange_quest(int i,int j)        // This prints the nearest location of another strange coins from given position.
    {
        int dist=10000;
        pair<int,int> ans;
        for(auto x:strange_coins)
        {
            int cur_dist=abs(x.first-i)+abs(x.second-i);
            if(dist>cur_dist)
            {
                dist=cur_dist;
                ans=make_pair(x.first,x.second);
            }
        }
        return ans;
    }
    void board_print(int p,int q)       //// Prints your location in the board.
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(i==p and j==q)
                {
                    cout<<'@'<<' ';
                }
                else cout<<'*'<<' ';
            }
            cout<<endl;
        }
        cout<<"\n Here @ represents your location and * represents  cells.";
    }
};

int main()
{
    cout<<"To Start the Game choose any positive number wisely and type it (Strange Hint: Try large numbers like 9999):\n";
    cin>>mod;
    Board b;
    int health = 10000;
    pair<int,int> pos={0,0};
    char c;
    int hint_coin=3;
    intro();
    cout<<"If you have not read the instructions restart the game as without them you can't play."<<endl;
    cout<<"Loading......";
    sleep(5);
    system("cls");
    while(health)
    {
        if(pos.first<0 or pos.first>9 or pos.second<0 or pos.second>9)
        {
            cout<<"You steeped out of Upside Down you are killed by Vecna\n";
            return 0;
        }
        health+=b.board[pos.first][pos.second];
        if(health<=0)
        {
            cout<<"You are defeated by democreatures "<<endl;
            return 0;
        }
        hint_coin+=b.hint_board[pos.first][pos.second];
        b.hint_board[pos.first][pos.second]=0;
        cout<<"Your current position is "<<pos.first<<' '<<pos.second<<endl;
        cout<<"With strange coins equals to "<<hint_coin<<endl;
        cout<<"With health equals to "<<health<<endl;
        if(pos==make_pair(9,9))
        {
            cout<<"Congrats you win!\n";return 0;
        }
        strange_coins.erase(pos);
        if(hint_coin)
        {
            string answer;
            cout<<"Seems You have strange coins,Do you want to use a strange coin ?  Yes/No\n";
            cin>>answer;
            if(answer=="Yes")
            {
                cout<<"A strange coin can be used in two ways:\n";
                cout<<"1: To get direction along which you will get minimum democreatures.\n";
                cout<<"2: To get nearby location of another strange coin.\n";
                cout<<"For what purpose do you want to use? Type id 1/2 corresponding to purpose of use.\n";
                int id;
                cin>>id;
                if(id==1)
                {
                    cout<<"Direction in which you will encounter minimum democreatures is "<<b.shortestpath(pos.first,pos.second,health)<<endl;
                    hint_coin--;
                }
                else
                {
                    pair<int,int> coords=b.strange_quest(pos.first,pos.second);
                    cout<<"Co-ordinates of nearest strange coins are "<<coords.first<<' '<<coords.second<<endl;
                }
            }
        }
        cout<<"Choose direction in which you want to go out of: L,R,U,D :";
        cin>>c;
        if(c=='L')
        {
            pos.second-=1;
        }
        else if(c=='R')
        {
            pos.second+=1;
        }
        else if(c=='U')
        {
            pos.first-=1;
        }
        else 
        {
            pos.first+=1;
        }
        b.board_print(pos.first,pos.second);
        sleep(5);
        system("cls");
    }
    return 0;
}
