#include<bits/stdc++.h>
using namespace std;

vector<int> leaderBoard;
vector<int> winner;

void displayLeaderBoard(){
    cout<<"::::::::::: Score Board :::::::::::"<<endl<<endl;
    int n = leaderBoard.size();
    for(int i=0;i<n;i++){
        cout<<"   Player "<<i+1<<" : "<<leaderBoard[i]<<endl;
    }
    cout<<endl<<"::::::::::::::::::::::::::::::::::::"<<endl;
    n = winner.size();
    if(n > 0){
        cout<<endl<<"::::::::::::: Winners ::::::::::::::"<<endl<<endl;
        for(int i=0;i<n;i++){
            cout<<"   Player "<<winner[i] + 1<<endl;
        }

        cout<<endl<<"::::::::::::::::::::::::::::::::::::"<<endl;
    }
    
}

void initializeTurn(vector<int> &turn){
    int n = turn.size();
    for(int i=0;i<n;i++){
        turn[i] = i;
    }
    for(int i=0;i<n;i++){
        int num = rand() % n;
        swap(turn[i], turn[num]);
    }
}

int main()
{
    
    int n, points, target;
    cout<<"Enter number of Players (Atleast 2 Players): ";
    cin>>n;
    if(n < 2){
        cout<<"Invalid Number of Players"<<endl;
        return 0;
    }
    cout<<"Enter number of points needed to win (Greater than 0): ";
    cin>>points;
    cout<<"Enter target val for double points : ";
    cin>>target;
    if(points <= 0){
        cout<<"!!Invalid Number!!";
        return 0;
    }

    vector<int> lb(n, 0);
    leaderBoard = lb;
    displayLeaderBoard();

    vector<int> turn(n, 0);
    initializeTurn(turn);

    vector<int> lastDiceValue(n, -1);
    int current_turn = turn[0];
    int turnCounter = 0;
    vector<bool> check_turn(n, false);
    vector<pair<int, int>> lastTwoDiceValue(n, {INT_MIN, INT_MIN});
    while(winner.size() < n){
        // for(int i=0;i<last.size();i++){
        //     cout<<last[i]<<" ";
        // }
        // cout<<endl;
        if(turnCounter == n){
            turnCounter = 0;
        }
        current_turn = turn[turnCounter];
        if(leaderBoard[current_turn] >= points){
            turnCounter += 1;
            continue;
        }

        if(check_turn[current_turn]){
            cout<<endl<<"!!! Skipping Player "<<current_turn + 1<<"  !!!"<<endl;
            check_turn[current_turn] = false;
            turnCounter += 1;
            continue;
        }

        cout<<"Player "<<current_turn + 1<<" turn (Press r and enter to roll dice) : ";
        char ch;
        cin>>ch;
        if(ch != 'r'){
            return 0;
        }     
        //int dice = rand()%6 + 1;
        int dice = 4;
        cout<<endl<<"Dice Value   :  "<<dice<<endl;
        int sumthree = dice + lastTwoDiceValue[current_turn].first + lastTwoDiceValue[current_turn].second;
        swap(lastTwoDiceValue[current_turn].first, lastTwoDiceValue[current_turn].second);
        lastTwoDiceValue[current_turn].first = dice; 


        if(lastDiceValue[current_turn] == 1 && dice == 1){
            // Skip Turn
            lastDiceValue[current_turn] = -1;
            check_turn[current_turn] = true;
            leaderBoard[current_turn] += dice;  
        }else if(dice == 6){
            lastDiceValue[current_turn] = 6;
            leaderBoard[current_turn] += dice;
            turnCounter -= 1;
        }else{
            lastDiceValue[current_turn] = dice;
            leaderBoard[current_turn] += dice;   
        }
        if(sumthree == target){
            leaderBoard[current_turn] += dice;
        }
        if(leaderBoard[current_turn] >= points){
            winner.push_back(current_turn);
        }

        displayLeaderBoard();
        turnCounter += 1;
    }


    return 0;
}


