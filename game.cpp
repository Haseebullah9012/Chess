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
        void setID(Piece p) { id = p; }
		void setColor(Color c) { color = c; }
		Piece getID() { return id; }
        Color getColor() { return color; }
        
        string getName();
};

class BoardSquare
{
    private:
        int rank;
        int file;
        ChessPiece piece;

    public:
        bool isEmpty;
        BoardSquare();

        //Get & Set Funtions of each Data Member
        void setRank(int r) { rank = r; }
		void setFile(int f) { file = f; }
        int getRank() { return rank; }
        int getFile() { return file; }
        
        void setPiece(ChessPiece p) { piece = p; }
		ChessPiece getPiece() { return piece; }
};

BoardSquare square[8][8]; //ChessBoard Squares
ChessPiece Pawn[16];
ChessPiece Knight[4];
ChessPiece Bishop[4];
ChessPiece Rook[4];
ChessPiece Queen[2];
ChessPiece King[2];

void initBoard(); //Initialize the ChessBoard
void PrintBoard(Color); //Print the ChessBoard
char DisplayPiece(int,int); //Display the ChessPiece

int main()
{
    cout << "\n Haseebullah's Chess! \n";

    initBoard();

    cout << "\n White's Turn! \n\n";
    PrintBoard(WHITE);

    cout << endl << endl;
    
    cout << "\n Black's Turn! \n\n";
    PrintBoard(BLACK);
    
    getchar();
    return 0;
}

void initBoard()
{
    //Board-Squares File & Rank
    for(int r=0; r<8; r++) {
        for(int f=0; f<8; f++) {
            square[r][f].setFile(f+1);
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

void PrintBoard(Color player)
{
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


BoardSquare::BoardSquare()
{
    isEmpty = true; //All Squares are Empty atFirst
}

string ChessPiece::getName()
{
    switch (id)
    {
        case PAWN: return "Pawn"; break;
        case KNIGHT: return "Knight"; break;
        case BISHOP: return "Bishop"; break;
        case ROOK: return "Rook"; break;
        case QUEEN: return "Queen"; break;
        case KING: return "King"; break;
    }
    
    return "-"; //Non-Executeable
}
