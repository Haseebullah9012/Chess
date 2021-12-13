#include <iostream>
#include <string>
using namespace std;

enum Color { White, Black };
enum Piece { Pawn, Knight, Bishop, Rook, Queen, King};

class ChessPiece
{
    private:
        Color color;
        Piece piece;

    public:

        //Get & Set Funtions of each Data Member
        void setColor(Color c) { color = c; }
		void setPiece(Piece p) { piece = p; }
		Color getColor() { return color; }
        Piece getPiece() { return piece; }
};

class BoardSquare
{
    private:
        int rank;
        int file;
        ChessPiece piece;

    public:
        
        //Get & Set Funtions of each Data Member
        void setRank(int r) { rank = r; }
		void setFile(int f) { file = f; }
        void setPiece(ChessPiece p) { piece = p; }
		int getRank() { return rank; }
        int getFile() { return file; }
        ChessPiece getPiece() { return piece; }
};

BoardSquare square[8][8]; //ChessBoard Squares
ChessPiece piece[32]; //Chess Pieces

void PrintBoard(string); //Print the ChessBoard
char DisplayPiece(int,int); //Display the ChessPiece
string PiecetoString(Piece); //Convert Enumeration Value to String

int main()
{
    cout << "\n Haseebullah's Chess! \n";

    //Initialize the Board-Squares
    for(int r=0; r<8; r++) {
        for(int f=0; f<8; f++) {
            square[r][f].setFile(f+1);
            square[r][f].setRank(r+1);
        }
    }

    //Initialize the Chess Pieces
    for(int w=0,b=16; w<16 && b<32; w++,b++) {
        piece[w].setColor(White);
        piece[b].setColor(Black);
    }
    
    for(int w=8,b=24; w<16 && b<32; w++,b++) {
        piece[w].setPiece(Pawn);
        piece[b].setPiece(Pawn);
        for(int f=0; f<8; f++) {
            square[1][f].setPiece(piece[w]);
            square[6][f].setPiece(piece[b]);
        }
    }
    for(int w=0,b=16; w<2 && b<18; w++,b++) {
        piece[w].setPiece(Knight);
        piece[b].setPiece(Knight);
        square[0][1].setPiece(piece[w]);
        square[0][6].setPiece(piece[w]);
        square[7][1].setPiece(piece[b]);
        square[7][6].setPiece(piece[b]);
    }
    for(int w=2,b=18; w<4 && b<20; w++,b++) {
        piece[w].setPiece(Bishop);
        piece[b].setPiece(Bishop);
        square[0][2].setPiece(piece[w]);
        square[0][5].setPiece(piece[w]);
        square[7][2].setPiece(piece[b]);
        square[7][5].setPiece(piece[b]);
    }
    for(int w=4,b=20; w<6 && b<22; w++,b++) {
        piece[w].setPiece(Rook);
        piece[b].setPiece(Rook);
        square[0][0].setPiece(piece[w]);
        square[0][7].setPiece(piece[w]);
        square[7][0].setPiece(piece[b]);
        square[7][7].setPiece(piece[b]);
    }
    for(int w=6,b=22; w<7 && b<23; w++,b++) {
        piece[w].setPiece(Queen);
        piece[b].setPiece(Queen);
        square[0][3].setPiece(piece[w]);
        square[7][3].setPiece(piece[b]);
    }
    for(int w=7,b=23; w<8 && b<24; w++,b++) {
        piece[w].setPiece(King);
        piece[b].setPiece(King);
        square[0][4].setPiece(piece[w]);
        square[7][4].setPiece(piece[b]);
    }
    
    for(int r=2; r<6; r++) {
        for(int f=0; f<8; f++) {
            ChessPiece noPiece;
            square[r][f].setPiece(noPiece);
        }
    }
    
    cout << "\n White's Turn! \n\n";
    PrintBoard("White");

    cout << endl << endl;
    
    cout << "\n Black's Turn! \n\n";
    PrintBoard("Black");
    
    getchar();
    return 0;
}

void PrintBoard(string player)
{
    if(player == "White")
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
    else if(player == "Black")
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
    else
    {
        cout << "\n\n Invalid Player \n\n"; //Error
    }
}

char DisplayPiece(int r, int f)
{
    ChessPiece piece = square[r][f].getPiece();
    
    Piece id = piece.getPiece();
    string name = PiecetoString(id);

    if(piece.getColor() == White) {
        return toupper(name[0]);
    }
    else if(piece.getColor() == Black) {
        return tolower(name[0]);
    }
    else {
        return ' ';
    }

    return '-';
}

string PiecetoString(Piece p)
{
    switch (p)
    {
        case Pawn: return "Pawn"; break;
        case Knight: return "Night"; break;
        case Bishop: return "Bishop"; break;
        case Rook: return "Rook"; break;
        case Queen: return "Queen"; break;
        case King: return "King"; break;
        default: return " ";
    }
    
    return "-";
}
