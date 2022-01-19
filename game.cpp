#include <iostream>
#include <string>
using namespace std;

enum Color { WHITE, BLACK };
enum Piece { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

class BoardSquare
{
    private:
        int rank;
        int fileNumber;
        char file;

    public:
        bool isEmpty;
        BoardSquare();

        void setRank(int r) { rank = r; }
		void setFileNumber(int); //To Set File Number and Derive the File-Character
        int getRank() { return rank; }
        int getFileNumber() { return fileNumber; }
        char getFile() { return file; }
};

class ChessPiece : public BoardSquare
{
    private:
        Piece id;
        Color color;
        string name;

    public:
        bool pawnMoved; //To Check if the Pawn is Once Moved
        bool captured; //To Check if the Piece is Captured
        ChessPiece();

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
        //void KingCheck();
};

BoardSquare square[8][8]; //ChessBoard Squares
ChessPiece pawn[16], knight[4], bishop[4], rook[4], queen[2], king[2]; //Chess-Pieces
ChessPiece emptyPiece;

void initBoard(); //Initialize the ChessBoard
void PrintBoard(Color); //Print the ChessBoard
char DisplayPiece(int,int); //Display the ChessPiece
ChessPiece* getPiece(int r, int f); //
void Game(); //The Main Game-Sequence
bool turn(); //Player's Turn
bool over(); //To Check if the Game is Over
void PlayAgain(); //The PlayAgain Option

Color player = WHITE; //Default First-Turn
bool gameOver; //Check If the Game is Over
int sourceRank,sourceFile, destinedRank,destinedFile; //The Player Inputs, for Source & Destined Rank/File
ChessPiece* ownPiece; //The Player's Input Source-Piece
BoardSquare *sourceSquare,*destinedSquare; //The Player-Input's Source & Destined Squares
int rankedSteps,filedSteps; //The Difference between Squares's Ranks/Files
char playAgain = 'Y'; //The Default PlayAgain Option

int main()
{
    cout << "\n Welcome to the Haseebullah's Chess! \n" << endl;
    cout << "On your Turn, Enter the Index (File & Rank) of Your Piece "
        << "and the Index (File & Rank) of the Destined-Square. " << endl;

    do {
        initBoard();
        Game();
        PlayAgain();
    }
    while(playAgain == 'Y');
	
	cout << endl << endl;
    cout << "Thanks for Playing. Hope You Enjoyed the Game! \n";
    cout << "It would be very Kind of you, if you give us an Honest Feedback. \n\n";

    cout << "You can Find me in GitHub https://github.com/Haseebullah9012. \n";

    getchar();
    getchar();
    return 0;
}

BoardSquare::BoardSquare()
{
    isEmpty = true; //All Squares are Empty atFirst
}

ChessPiece::ChessPiece()
{
    pawnMoved = false;
    captured = false;
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


void initBoard()
{
    //Chess-Pieces ID, Color & Board-Setup
    for(int i=0; i<16; i++) 
    {
        pawn[i].setID(PAWN);
        pawn[i].pawnMoved = false;
        
        if(i<8) {
            pawn[i].setColor(WHITE);
            pawn[i].setRank(2);
            pawn[i].setFileNumber(i+1);
        }
        else {
            pawn[i].setColor(BLACK);
            pawn[i].setRank(7);
            pawn[i].setFileNumber(i-8+1);
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

                knight[i].setRank(1);
                bishop[i].setRank(1);
                rook[i].setRank(1);
            }
            else {
                knight[i].setColor(BLACK);
                bishop[i].setColor(BLACK);
                rook[i].setColor(BLACK);

                knight[i].setRank(8);
                bishop[i].setRank(8);
                rook[i].setRank(8);
            }

            if(i%2==0) {
                rook[i].setFileNumber(1);
                knight[i].setFileNumber(2);
                bishop[i].setFileNumber(3);    
            }
            else {
                bishop[i].setFileNumber(6);
                knight[i].setFileNumber(7);
                rook[i].setFileNumber(8);
            }
        }
        
        if(i<2)
        {
            queen[i].setID(QUEEN);
            king[i].setID(KING);

            if(i==0) {
                queen[i].setColor(WHITE);
                king[i].setColor(WHITE);

                queen[i].setRank(1);
                king[i].setRank(1);
            }
            else {
                queen[i].setColor(BLACK);
                king[i].setColor(BLACK);

                queen[i].setRank(8);
                king[i].setRank(8);
            }

            queen[i].setFileNumber(4);
            king[i].setFileNumber(5);
        }
    }

    //The Absence of any Piece on the BoadSquare
    emptyPiece.setRank(0);
    emptyPiece.setFileNumber(0);

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
        
        if(gameOver)
            break;
        
        //Next Turn
        if(player == WHITE)
            player = BLACK;
        else
            player = WHITE;
    }

    cout << endl << endl;
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
    ChessPiece* piece = getPiece(r+1,f+1);
    string name = piece->getName();

    if(name == "Knight")
        name = "Night"; //K-Silent (Knight represented by N)

    if(!square[r][f].isEmpty) {
        if(piece->getColor() == WHITE)
            return toupper(name[0]);
        else if(piece->getColor() == BLACK)
            return tolower(name[0]);
    }
    else {
        return ' '; //Empty Square
    }

    return '-'; //Non-Executable
}

ChessPiece* getPiece(int r, int f)
{
    for(int i=0; i<16; i++)
    {
        if(pawn[i].getRank()==r && pawn[i].getFileNumber()==f)
            return &pawn[i];

        if(i<4)
        {
            if(knight[i].getRank()==r && knight[i].getFileNumber()==f)
                return &knight[i];
            else if(bishop[i].getRank()==r && bishop[i].getFileNumber()==f)
                return &bishop[i];
            else if(rook[i].getRank()==r && rook[i].getFileNumber()==f)
                return &rook[i];
        }

        if(i<2)
        {
            if(queen[i].getRank()==r && queen[i].getFileNumber()==f)
                return &queen[i];
            else if(king[i].getRank()==r && king[i].getFileNumber()==f)
                return &king[i];
        }
    }

    return &emptyPiece;
}

bool turn()
{
    char sourceFile_char,destinedFile_char;
    cin >> sourceFile_char >> sourceRank >> destinedFile_char >> destinedRank;

    if(sourceFile_char<'a'||sourceFile_char>'h' || destinedFile_char<'a'||destinedFile_char>'h') {
		cout << "Invalid File Character! ";
        return false;
	}
    else if(sourceRank<1||sourceRank>8 || destinedRank<1||destinedRank>8) {
        cout << "Invalid Rank Number! ";
        return false;
    }

    //Set File & Rank for Array-Index
    sourceFile = (sourceFile_char - 'a')+1;
    destinedFile = (destinedFile_char - 'a')+1;
    
    sourceSquare = &square[sourceRank-1][sourceFile-1];
    destinedSquare = &square[destinedRank-1][destinedFile-1];
    
    if(sourceSquare->isEmpty) {
        cout << "There's No Piece! ";
        return false;
    }
    
    ownPiece = getPiece(sourceRank,sourceFile);
    if(ownPiece->getColor() != player) {
        cout << "That's Not Your Piece! ";
        return false;
    }
    else if(!destinedSquare->isEmpty) {
        ChessPiece* targetPiece = getPiece(destinedRank,destinedFile);
        if(targetPiece->getColor() == player) {
            cout << "Invalid Move! Cannot Land on Own Piece. ";
            return false;
        }
    }
    
    return ownPiece->Move();
}

bool ChessPiece::Move()
{
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
        if(!destinedSquare->isEmpty) {
            ChessPiece* targetPiece = getPiece(destinedRank,destinedFile);
            targetPiece->setRank(0);
            targetPiece->setFileNumber(0);
            targetPiece->captured = true;
            
            /*
            if(targetPiece->getName() == "King") {
                cout << "King Captured. ";
                if(player == WHITE)
                    cout << "White Won! ";
                else 
                    cout << "Black Won! ";
                
                cout << endl;
                gameOver = true;
            }
            */
        }

        ownPiece->setRank(destinedRank);
        ownPiece->setFileNumber(destinedFile);
        sourceSquare->isEmpty = true;
        destinedSquare->isEmpty = false;
    }
    else
        cout << "Invalid Move! " << name << " Cannot Move Like This. ";

    //King Captured
    if(king[1].captured) {
        cout << "King Captured. White Won! " << endl;
        gameOver = true;
    }
    else if(king[0].captured) {
        cout << "King Captured. Black Won! " << endl;
        gameOver = true;
    }

    return valid;
}


bool ChessPiece::movePawn()
{
    bool valid;
    
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


void PlayAgain()
{
	cout << "Do You Want to Play Again (Y/N): ";
	cin >> playAgain;
	playAgain = toupper(playAgain);
	
	if(playAgain == 'Y') {
		if(player == WHITE)
            player = BLACK;
        else 
            player = WHITE;
	}
	else {
		cout << "   Oops! Its not a legal Response. \n\n";
		cout << "Again, ";
		PlayAgain();
	}
}
