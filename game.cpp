#include <iostream>
#include <string>
using namespace std;

enum Color { WHITE, BLACK };
enum Piece { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

class BoardSquare;

class ChessPiece
{
    private:
        Piece id;
        Color color;
        string name;

    public:
        bool pawnMoved; //To Check if the Pawn is Once Moved

        void setID(Piece); //To Set ID and Derive the Piece-Name
		void setColor(Color c) { color = c; }
		Piece getID() { return id; }
        Color getColor() { return color; }
        string getName() { return name; }

        bool Move(); //To Move the ChessPiece
    
    private:
        bool movePawn();
        bool moveKnight();
        bool moveBishop();
        bool moveRook();
        bool moveQueen();
        bool moveKing();
};

class BoardSquare
{
    private:
        int rank;
        int fileNumber;
        char file;
        ChessPiece piece;

    public:
        bool isEmpty;
        BoardSquare();

        void setRank(int r) { rank = r; }
		void setFileNumber(int); //To Set File Number and Derive the File-Character
        int getRank() { return rank; }
        int getFileNumber() { return fileNumber; }
        char getFile() { return file; }
        
        void setPiece(ChessPiece p) { piece = p; }
		ChessPiece getPiece() { return piece; }
        ChessPiece* getPieceReference() { return &piece; }
};

BoardSquare square[8][8]; //ChessBoard Squares
ChessPiece pawn[16], knight[4], bishop[4], rook[4], queen[2], king[2]; //Chess-Pieces

void initBoard(); //Initialize the ChessBoard
void PrintBoard(Color); //Print the ChessBoard
char DisplayPiece(int,int); //Display the ChessPiece
void Game(); //The Main Game-Sequence
bool turn(); //Player's Turn
bool over(); //To Check if the Game is Over

Color player = WHITE; //Default First-Turn
char fc1,fc2; //The Player Inputs, for Source & Destined Files
int r1,r2; //The Player Inputs, for Source & Destined Ranks

BoardSquare *sourceSquare,*destinedSquare; //The Player-Input's Source & Destined Squares
int sourceRank,sourceFile; //Derive Source-Square's Rank/File
int destinedRank,destinedFile; //Derive Destined-Square's Rank/File
int rankedSteps,filedSteps; //The Difference between Squares's Ranks/Files

int main()
{
    cout << "\n Welcome to the Haseebullah's Chess! \n" << endl;
    cout << "On your Turn, Enter the Index (File & Rank) of Your Piece "
        << "and the Index (File & Rank) of the Destined-Square. " << endl;

    initBoard();
    Game();

    getchar();
    return 0;
}

void initBoard()
{
    //Board-Squares File & Rank
    for(int r=0; r<8; r++) {
        for(int f=0; f<8; f++) {
            square[r][f].setFileNumber(f+1);
            square[r][f].setRank(r+1);
        }
    }

    //Chess-Pieces ID & Color
    //Also Chess-Pieces Board-Setup
    for(int i=0; i<16; i++) 
    {
        pawn[i].setID(PAWN);
        pawn[i].pawnMoved = false;
        
        if(i<8) {
            pawn[i].setColor(WHITE);
            for(int f=0; f<8; f++)
                square[1][f].setPiece(pawn[i]);
        }
        else {
            pawn[i].setColor(BLACK);
            for(int f=0; f<8; f++)
                square[6][f].setPiece(pawn[i]);
        }
        
        if(i<4)
        {
            knight[i].setID(KNIGHT);
            bishop[i].setID(BISHOP);
            rook[i].setID(ROOK);

            if(i<2) {
                knight[i].setColor(WHITE);
                bishop[i].setColor(WHITE);
                rook[i].setColor(WHITE);

                square[0][0].setPiece(rook[i]);
                square[0][1].setPiece(knight[i]);
                square[0][2].setPiece(bishop[i]);
                square[0][5].setPiece(bishop[i]);
                square[0][6].setPiece(knight[i]);
                square[0][7].setPiece(rook[i]);
            }
            else {
                knight[i].setColor(BLACK);
                bishop[i].setColor(BLACK);
                rook[i].setColor(BLACK);

                square[7][0].setPiece(rook[i]);
                square[7][1].setPiece(knight[i]);
                square[7][2].setPiece(bishop[i]);
                square[7][5].setPiece(bishop[i]);
                square[7][6].setPiece(knight[i]);
                square[7][7].setPiece(rook[i]);
            }
        }
        
        if(i<2)
        {
            queen[i].setID(QUEEN);
            king[i].setID(KING);

            if(i==0) {
                queen[i].setColor(WHITE);
                king[i].setColor(WHITE);

                square[0][3].setPiece(queen[i]);
                square[0][4].setPiece(king[i]);
            }
            else {
                queen[i].setColor(BLACK);
                king[i].setColor(BLACK);

                square[7][3].setPiece(queen[i]);
                square[7][4].setPiece(king[i]);
            }
        }
    }
    
    //Chess-Pieces Squares are Now Occupied
    for(int rw=0,rb=6; rw<2 && rb<8; rw++,rb++) {
        for(int f=0; f<8; f++) {
            square[rw][f].isEmpty = false;
            square[rb][f].isEmpty = false;
        }
    }
}

void Game()
{
    while(true) 
    {
        PrintBoard(player);
        
        if(player == WHITE)
            cout << "White's Turn: ";
        else 
            cout << "Black's Turn: ";

        //While the Player's Input is Invalid, Continue Inputing the Move
        while(!turn())
            cout << "Move Again: ";
        
        if(over())
            break;

        //Next Turn
        if(player == WHITE)
            player = BLACK;
        else
            player = WHITE;
    }
}

void PrintBoard(Color player)
{
    cout << endl << endl;

    if(player == WHITE)
    {
        cout << "      a   b   c   d   e   f   g   h      \n";
    
        for(int r=7; r>=0; r--) {
            cout << "     --- --- --- --- --- --- --- ---     \n";
            cout << " " << r+1 << " ";
            
            for(int f=0; f<8; f++) {     
                cout << " | " << DisplayPiece(r,f); /* Print Square Here */
            }
            
            cout << " | " << " " << r+1 << " \n";
        }
        
        cout << "     --- --- --- --- --- --- --- ---     \n";
        cout << "      a   b   c   d   e   f   g   h      \n";
    }
    else if(player == BLACK)
    {
        cout << "      h   g   f   e   d   c   b   a      \n";
    
        for(int r=0; r<8; r++) {
            cout << "     --- --- --- --- --- --- --- ---     \n";
            cout << " " << r+1 << " ";
            
            for(int f=7; f>=0; f--) {     
                cout << " | " << DisplayPiece(r,f); /* Print Square Here */
            }
            
            cout << " | " << " " << r+1 << " \n";
        }
        
        cout << "     --- --- --- --- --- --- --- ---     \n";
        cout << "      h   g   f   e   d   c   b   a      \n";
    }

    cout << "\n^!_!^\n";
}

char DisplayPiece(int r, int f)
{
    ChessPiece piece = square[r][f].getPiece();
    string name = piece.getName();

    if(name == "Knight")
        name = "Night"; //K-Silent (Knight represented by N)

    if(!square[r][f].isEmpty) {
        if(piece.getColor() == WHITE)
            return toupper(name[0]);
        else if(piece.getColor() == BLACK)
            return tolower(name[0]);
    }
    else {
        return ' '; //Empty Square
    }

    return '-'; //Non-Executable
}

bool turn()
{
    cin >> fc1 >> r1 >> fc2 >> r2;

    if(fc1<'a'||fc1>'h' || fc2<'a'||fc2>'h') {
		cout << "Invalid File Character! ";
        return false;
	}
    else if(r1<1||r1>8 || r2<1||r2>8) {
        cout << "Invalid Rank Number! ";
        return false;
    }

    //Set File & Rank for Array-Index
    r1--, r2--;
    int f1 = fc1 - 'a';
    int f2 = fc2 - 'a';
    
    sourceSquare = &square[r1][f1];
    destinedSquare = &square[r2][f2];
    
    if(sourceSquare->isEmpty) {
        cout << "There's No Piece! ";
        return false;
    }
    else if(sourceSquare->getPiece().getColor() != player) {
        cout << "That's Not Your Piece! ";
        return false;
    }
    
    ChessPiece ownPiece = sourceSquare->getPiece();
    return ownPiece.Move();
}

bool over()
{
    return false;
}


BoardSquare::BoardSquare()
{
    isEmpty = true; //All Squares are Empty atFirst
}

void BoardSquare::setFileNumber(int f)
{
    fileNumber = f;
    file = fileNumber-1 + 'a';
}

void ChessPiece::setID(Piece p)
{
    id = p;

    switch (id)
    {
        case PAWN: name = "Pawn"; break;
        case KNIGHT: name = "Knight"; break;
        case BISHOP: name = "Bishop"; break;
        case ROOK: name = "Rook"; break;
        case QUEEN: name = "Queen"; break;
        case KING: name = "King"; break;
    }
}


bool ChessPiece::Move()
{
    if(!destinedSquare->isEmpty) {
        ChessPiece targetPiece = destinedSquare->getPiece();

        if(color == targetPiece.getColor()) {
            cout << "Invalid Move! Cannot Land on Own Piece. ";
            return false;
        }
    }
    
    sourceRank = sourceSquare->getRank();
	sourceFile = sourceSquare->getFileNumber();
	destinedRank = destinedSquare->getRank();
	destinedFile = destinedSquare->getFileNumber();
    
    rankedSteps = destinedRank-sourceRank;
    filedSteps = destinedFile-sourceFile;
    
    bool valid;
    switch(id)
    {
        case PAWN: valid = movePawn(); break;
        case KNIGHT: valid = moveKnight(); break;
        case BISHOP: valid = moveBishop(); break;
        case ROOK: valid = moveRook(); break;
        case QUEEN: valid = moveQueen(); break;
        case KING: valid = moveKing(); break;
    }

    if(valid) {
        destinedSquare->setPiece(sourceSquare->getPiece());
        sourceSquare->isEmpty = true;             
        destinedSquare->isEmpty = false;
    }
    else
        cout << "Invalid Move! " << name << " Cannot Move Like This. ";

    return valid;
}

bool ChessPiece::movePawn()
{
    bool valid;
    ChessPiece* ownPiece = sourceSquare->getPieceReference();
    
    if(player==BLACK)
        rankedSteps = -rankedSteps;
    
    bool stepStraight = (filedSteps==0 && rankedSteps==1) && destinedSquare->isEmpty;
    bool stepDiagonal = (abs(filedSteps)==1 && rankedSteps==1) && (!destinedSquare->isEmpty);
    bool doubleStep = (filedSteps==0 && rankedSteps==2) && !ownPiece->pawnMoved;
    
    if(stepStraight || stepDiagonal)
        valid = true;
    else if(doubleStep)
    {
        valid = true;
        
        int r=1;
        if(player==BLACK)
            r=-1;
        
        if(!square[sourceRank+r-1][sourceFile-1].isEmpty)
            valid = false;
    }
    else
        valid = false;
    
    if(valid && !ownPiece->pawnMoved)
        ownPiece->pawnMoved = true;
    
    return valid;
}

bool ChessPiece::moveKnight()
{
    bool valid;
    bool rankedMovement = abs(rankedSteps)==2 && abs(filedSteps)==1;
    bool filedMovement = abs(filedSteps)==2 && abs(rankedSteps)==1;
    
    if(rankedMovement || filedMovement)
        valid = true;
    else
        valid = false;
    
    return valid;
}

bool ChessPiece::moveBishop()
{
    bool valid;
    bool diagonalMovement = abs(rankedSteps)==abs(filedSteps);
    
    if(diagonalMovement) 
    {
        valid = true;
        int stepR = rankedSteps/abs(rankedSteps);
        int stepF = filedSteps/abs(filedSteps);
        for(int r=stepR,f=stepF; abs(r)<abs(rankedSteps); r+=stepR,f+=stepF) {
            if(!square[sourceRank+r-1][sourceFile+f-1].isEmpty) {
                valid = false;
                break;
            }
        }
    }
    else
        return false;
    
    return valid;
}

bool ChessPiece::moveRook()
{
    bool valid;
    bool rankedMovement = destinedFile==sourceFile;
    bool filedMovement = destinedRank==sourceRank;

    if(rankedMovement)
    {
        valid = true;
        int step = rankedSteps/abs(rankedSteps);
        for(int r=step; abs(r)<abs(rankedSteps); r+=step) {
            if(!square[sourceRank+r-1][sourceFile-1].isEmpty) {
                valid = false;
                break;
            }
        }
    }
    else if(filedMovement)
    {
        valid = true;
        int step = filedSteps/abs(filedSteps);
        for(int f=step; abs(f)<abs(filedSteps); f+=step) {
            if(!square[sourceRank-1][sourceFile+f-1].isEmpty) {
                valid = false;
                break;
            }
        }
    }
    else
        return false;
    
    return valid;
}

bool ChessPiece::moveQueen()
{
    bool valid;
    bool diagonalMovement = abs(rankedSteps)==abs(filedSteps);
    bool rankedMovement = destinedFile==sourceFile;
    bool filedMovement = destinedRank==sourceRank;

    if(rankedMovement)
    {
        valid = true;
        int step = rankedSteps/abs(rankedSteps);
        for(int r=step; abs(r)<abs(rankedSteps); r+=step) {
            if(!square[sourceRank+r-1][sourceFile-1].isEmpty) {
                valid = false;
                break;
            }
        }
    }
    else if(filedMovement)
    {
        valid = true;
        int step = filedSteps/abs(filedSteps);
        for(int f=step; abs(f)<abs(filedSteps); f+=step) {
            if(!square[sourceRank-1][sourceFile+f-1].isEmpty) {
                valid = false;
                break;
            }
        }
    }
    else if(diagonalMovement)
    {
        valid = true;
        int stepR = rankedSteps/abs(rankedSteps);
        int stepF = filedSteps/abs(filedSteps);
        for(int r=stepR,f=stepF; abs(r)<abs(rankedSteps); r+=stepR,f+=stepF) {
            if(!square[sourceRank+r-1][sourceFile+f-1].isEmpty) {
                valid = false;
                break;
            }
        }
    }
    else
        valid = false;
    
    return valid;
}

bool ChessPiece::moveKing()
{
    bool valid;
    bool stepMovement = abs(rankedSteps)==1 || abs(filedSteps)==1;

    if(stepMovement)
        valid = true;
    else
        valid = false;

    return valid;
}
