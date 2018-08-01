#include<iostream>
#include<vector>
using namespace std;

// Imagine these are class private members
int upDog = 0, sideDog = 0;

void saveMoves(int up, int side){
    upDog = up;
    sideDog = side;
}


// Checks edges of BFS for dirty block
bool checkEdges(int r, int c, vector <string> board, int radius){
    
    // Matrix Max Values
    int maxRows = board.size(), maxColumns = board[0].size();
    
    // Set Bounds
    int  upBound    = ((r - radius >= 0)?         r - radius : 0),
         downBound  = ((r + radius < maxRows)?    r + radius : maxRows - 1),
         leftBound  = ((c - radius >= 0)?         c - radius : 0),
         rightBound = ((c + radius < maxColumns)? c + radius : maxColumns - 1);
    
    /*cout << "r "     << r          << endl
         << "c "     << c          << endl
         << "up "    << upBound    << endl
         << "down "  << downBound  << endl
         << "left "  << leftBound  << endl
         << "right " << rightBound << endl;*/
    
    // Top Row
    if(upBound < r){ //cout <<1<<endl;
        for(int i = leftBound; i<= rightBound; i++)
            if(board[upBound][i] == 'd'){saveMoves(r - upBound, i - c);return true;}
    }
    
    // Left Side
    if(leftBound < c){ //cout <<2<<endl;
        for(int i = upBound; i <= downBound; i++)
            if(board[i][leftBound] == 'd'){saveMoves(r - i, leftBound - c);return true;}
    }
    
    // Right Side
    if(rightBound > c){ //cout <<3<<endl;
        for(int i = upBound; i <= downBound; i++)
            if(board[i][rightBound] == 'd'){saveMoves(r - i, rightBound - c);return true;}
    }
    
    // Bottom Row
    if(downBound > r){ //cout <<4<<endl;
        for(int i = leftBound; i <= rightBound; i++)
            if(board[downBound][i] == 'd'){saveMoves(r - downBound, i - c);return true;}
    }
    
    return false;
    
}

// Returns true if saved move completed and returns false if no saved moves.
bool savedMoves(){
    
    //cout << "Updog = " << upDog << "  sideDog = " << sideDog << endl;
    
    if(upDog > 0){cout<<"UP\n"; upDog--; return true;}
    else if(upDog < 0){cout<<"DOWN\n"; upDog++; return true;}
    else if(sideDog > 0){cout<<"RIGHT\n"; sideDog--; return true;}
    else if(sideDog < 0){cout<<"LEFT\n"; sideDog++; return true;}
    else return false;
    
}

void findNextMoveBFS(int r, int c, vector <string> board){
    
    int maxRows = board.size(), maxColumns = board[0].size();
    
    // Missing Rows or Columns check
    if(maxRows == 0 || maxColumns == 0){return;}
    
    // Out of bounds check
    if(r >= maxRows || c >= maxColumns){return;}
    
    /* Example radius: Upper, Left, Right, Down
        
        UUUUU
        L   R
        L   R
        L   R
        DDDDD
    
     */
    int radius = 1, row_pos, col_pos;
    
    bool upBound, leftBound, rightBound, downBound;
    
    while(radius < maxRows || radius < maxColumns){
        
        if(checkEdges(r, c, board, radius)) 
            break;
        
        //cout << 1 << endl;
        
        radius++;
    }
    
    bool saveStatus = savedMoves();
    
}

// Checks if it can clean the current cell, if it cant it checks for any saved moves or calls the saveMoves method
void next_move(int r, int c, vector <string> board) {
    
    // Missing Rows or Columns check
    if(board.size() == 0 || board[0].size() == 0){return;}
    
    // Out of bounds check
    if(r >= board.size() || c >= board[0].size()){return;}
    
    if(board[r][c] == 'd'){cout << "CLEAN\n"; return;}
    else if(savedMoves()){return;}
    else{findNextMoveBFS(r, c, board);}
    
}

int main(void) {
    int pos[2];
    vector <string> board;
    cin>>pos[0]>>pos[1];
    for(int i=0;i<5;i++) {
        string s;cin >> s;
        board.push_back(s);
    }
    next_move(pos[0], pos[1], board);
    return 0;
}
