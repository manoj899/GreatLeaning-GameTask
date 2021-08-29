#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include<unordered_map>
#include<utility>
#include <unordered_set>
#include<bits/stdc++.h>

using namespace std;

int getNum(vector<int>& arr)
{
    int n = arr.size();

    srand(time(NULL));

    int position = rand() % n;
    int number = arr[position];

    swap(arr[position], arr[n - 1]);
    arr.pop_back();

    return number;
}
 
// Generating first random sequence for n players
void generateRandom(queue<int>& PlayerTurn,int n)
{
    vector<int> v(n);

    for (int i = 0; i < n; i++)
        v[i] = i + 1;
 
    // While vector has elements
    // get a random number from the vector and print it
    while (v.size()) {
        PlayerTurn.push(getNum(v));
    }
}

unordered_map<int,int> RankMap; 

//sorting PlayerRank array based on 
bool sortFirst(const pair<int,int> &a,
                   const pair<int,int> &b)
{
       if(RankMap.find(a.second) != RankMap.end()  && RankMap.find(b.second) != RankMap.end()){
           return RankMap[a.second]<RankMap[b.second];
       }else if(RankMap.find(a.second) != RankMap.end()){
           return true;
       }else if(RankMap.find(b.second) != RankMap.end()){
           return false;
       }
       return a.first>b.first;
}

void PrintRank(int PlayerScore[],int N){
    int Rank = 1;
    vector<pair<int,int>> PlayerRank;//

    for(int i = 1 ; i <= N; i++){
        PlayerRank.push_back({PlayerScore[i],i});
    }    

    sort(PlayerRank.begin(), PlayerRank.end(), sortFirst);

    cout<<"Rank  Player  Score"<<endl;
    for(int i = 0 ; i < PlayerRank.size() ; i++){
        cout<<Rank++<<"  Player-"<<PlayerRank[i].second<<"    "<<PlayerRank[i].first<<endl;
    }
    cout<<"----------------------------------------------"<<endl;

}

void RollTheDice(int N, int M){

    int Rank = 1;
    unordered_set<int> isTurnSkip;
    int PlayerScore[N+1];
   
    for(int i = 0 ; i < N+1; i++){
        PlayerScore[i] = 0;
    }

    queue<int> PlayerTurn;
    vector<int> PrevDiceValue(N+1,-1);

    //randomly arrange
    generateRandom(PlayerTurn,N);

    int lastDice = -1; // dice previous value

    while(!PlayerTurn.empty()){

        int CurrPlayer = PlayerTurn.front();
        
        // to check whether previously 1 occur or not
        if(isTurnSkip.find(CurrPlayer) != isTurnSkip.end()){
            cout<<"Your current turn skipped"<<endl;
            PlayerTurn.push(CurrPlayer);
            PrevDiceValue[CurrPlayer] = -1;
            isTurnSkip.erase(CurrPlayer);
            continue;
        }

         char ch;

         if(lastDice!=6)
         cout<<"Player - "<<CurrPlayer<<" its your turn. (Press 'r') to roll the dice"<<endl;
         else
            cout << "You have one more turn"<<endl; // if one get 6 , get one more chance to throw dice
         cin>>ch;

         while(ch != 'r'){
             cout<<"Please Enter 'r' to roll the Dice";
             cin>>ch;
         }


         int diceNumber = (rand() % (6)) + 1; // randomly generate dice number

         cout<<"Current Dice Number is : "<<diceNumber<<endl;

        lastDice = diceNumber;
        PlayerScore[CurrPlayer] += diceNumber;

        //if any player surpass M, then it completed its game 
        if(PlayerScore[CurrPlayer]>=M){
            cout << "You have completed the game with rank: " <<Rank++<<endl;
            PrintRank(PlayerScore, N);
            PlayerTurn.pop();
            RankMap.insert(make_pair(CurrPlayer,Rank-1));
            lastDice = 0;
            continue;
        }

        if(diceNumber != 6){
            PlayerTurn.pop();
            PlayerTurn.push(CurrPlayer);
            if(diceNumber == 1 && PrevDiceValue[CurrPlayer] == 1){
                isTurnSkip.insert(CurrPlayer); 
            }
        }
 
        PrevDiceValue[CurrPlayer] = diceNumber; 
        PrintRank(PlayerScore, N);      
    }
}

int main()
{
    RankMap.clear();// to get first random sequence of player in game,after each run its gonna clear sequence

    int NumberOfPlayer;
    int Points;

    cout<<"Enter Numbers of Players To Play Game:";
    cin>>NumberOfPlayer;
    cout<<endl;

    cout<<"Enter Numbers of Points need to reach to Complete Game:";
    cin>>Points;
    cout<<endl;

    RollTheDice(NumberOfPlayer, Points);
    return 0;
}