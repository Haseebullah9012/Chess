#include <iostream>
#include <string>
using namespace std;

enum Color { WHITE, BLACK };
enum Piece { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

class ChessPiece
{
    private:
        Piece id;
        Color color;
        string name;

    public:
        
        //Get & Set Funtions of each Data Member
        void setID(Piece); //TO Set ID and Derive the Piece-Name
		void setColor(Color c) { color = c; }
		Piece getID() { return id; }
        Color getColor() { return color; }
        string getName() { return name; }
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

        //Get & Set Funtions of each Data Member
        void setRank(int r) { rank = r; }
		void setFileNumber(int); //To Set File Number and Derive the File-Character
        int getRank() { return rank; }
        int getFileNumber() { return fileNumber; }
        char getFile() { return file; }
        
        void setPiece(ChessPiece p) { piece = p; }
		ChessPiece getPiece() { return piece; }
};

BoardSquare square[8][8]; //ChessBoard Squares
ChessPiece Pawn[16], Knight[4], Bishop[4], Rook[4], Queen[2], King[2]; //Chess-Pieces

void initBoard(); //Initialize the ChessBoard
void PrintBoard(Color); //Print the ChessBoard
char DisplayPiece(int,int); //Display the ChessPiece
void Game(); //The Main Game-Sequence
void turn(); //Player's Turn
bool over(); //To Check if the Game is Over

void movePawn(BoardSquare* sourceSquare, BoardSquare* destinedSquare) {}
void moveKnight(BoardSquare* sourceSquare, BoardSquare* destinedSquare) {}
void moveBishop(BoardSquare* sourceSquare, BoardSquare* destinedSquare) {}
void moveRook(BoardSquare* sourceSquare, BoardSquare* destinedSquare) {}
void moveQueen(BoardSquare* sourceSquare, BoardSquare* destinedSquare) {}
void moveKing(BoardSquare* sourceSquare, BoardSquare* destinedSquare) {}

Color player = WHITE; //Default First-Turn
char fc1,fc2; //The Player Inputs, for Source & Destined Files
int r1,r2; ////The Player Inputs, for Source & Destined Ranks

int main()
{
    cout << "\n Welcome to the Haseebullah's Chess! \n" << endl;
    cout << "On your Turn, Enter the Index (File & Rank) of Your Piece "
        << "and the Index (File & Rank) of the Destined-Square (Separated by Spaces). " << endl;

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
        Pawn[i].setID(PAWN);
        
        if(i<8) {
            Pawn[i].setColor(WHITE);
            for(int f=0; f<8; f++)
                square[1][f].setPiece(Pawn[i]);
        }
        else {
            Pawn[i].setColor(BLACK);
            for(int f=0; f<8; f++)
                square[6][f].setPiece(Pawn[i]);
        }
        
        if(i<4)
        {
            Knight[i].setID(KNIGHT);
            Bishop[i].setID(BISHOP);
            Rook[i].setID(ROOK);

            if(i<2) {
                Knight[i].setColor(WHITE);
                Bishop[i].setColor(WHITE);
                Rook[i].setColor(WHITE);

                square[0][0].setPiece(Rook[i]);
                square[0][1].setPiece(Knight[i]);
                square[0][2].setPiece(Bishop[i]);
                square[0][5].setPiece(Bishop[i]);
                square[0][6].setPiece(Knight[i]);
                square[0][7].setPiece(Rook[i]);
            }
            else {
                Knight[i].setColor(BLACK);
                Bishop[i].setColor(BLACK);
                Rook[i].setColor(BLACK);

                square[7][0].setPiece(Rook[i]);
                square[7][1].setPiece(Knight[i]);
                square[7][2].setPiece(Bishop[i]);
                square[7][5].setPiece(Bishop[i]);
                square[7][6].setPiece(Knight[i]);
                square[7][7].setPiece(Rook[i]);
            }
        }

        if(i<2)
        {
            Queen[i].setID(QUEEN);
            King[i].setID(KING);

            if(i==0) {
                Queen[i].setColor(WHITE);
                King[i].setColor(WHITE);

                square[0][3].setPiece(Queen[i]);
                square[0][4].setPiece(King[i]);
            }
            else {
                Queen[i].setColor(BLACK);
                King[i].setColor(BLACK);

                square[7][3].setPiece(Queen[i]);
                square[7][4].setPiece(King[i]);
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

        turn();
        
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

void turn()
{
    cin >> fc1 >> r1 >> fc2 >> r2;
    
    if(fc1<'a'||fc1>'h' || fc2<'a'||fc2>'h') {
		cout << "Invalid File Character! Move Again: ";
        turn();
	}
    else if(r1<1||r1>8 || r2<1||r2>8) {
        cout << "Invalid Rank Number! Move Again: ";
        turn();
    }

    //Set File & Rank for Array-Index
    r1--, r2--;
    int f1 = fc1 - 'a';
    int f2 = fc2 - 'a';
    
    BoardSquare* sourceSquare = &square[r1][f1];
    BoardSquare* destinedSquare = &square[r2][f2];
    
    if(sourceSquare->isEmpty) {
        cout << "There's No Piece! Move Again: ";
        turn();
    }
    else if(sourceSquare->getPiece().getColor() != player) {
        cout << "That's Not Your Piece! Move Again: ";
        turn();
    }
    
    ChessPiece ownPiece = sourceSquare->getPiece();
    if(!destinedSquare->isEmpty) {
        ChessPiece targetPiece = destinedSquare->getPiece();

        if(ownPiece.getColor() == targetPiece.getColor()) {
            cout << "Invalid Move! Cannot Land on Own Piece. Move Again: ";
            turn();
        }
    }
    
    switch(ownPiece.getID()) 
    {
        case PAWN: movePawn(sourceSquare,destinedSquare); break;
        case KNIGHT: moveQueen(sourceSquare,destinedSquare); break;
        case BISHOP: moveBishop(sourceSquare,destinedSquare); break;
        case ROOK: moveRook(sourceSquare,destinedSquare); break;
        case QUEEN: moveQueen(sourceSquare,destinedSquare); break;
        case KING: moveKing(sourceSquare,destinedSquare); break;
    }
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
