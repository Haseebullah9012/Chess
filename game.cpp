#include <iostream>
#include <string>
using namespace std;

class BoardSquare
{
    private:
        int rank;
        int file;

    public:
        
        //Get & Set Funtions of each Data Member
        void setRank(int r) { rank = r; }
		void setFile(int f) { file = f; }
		int getRank() { return rank; }
        int getFile() { return file; }
};

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

BoardSquare square[8][8]; //ChessBoard Squares
ChessPiece piece[32]; //Chess Pieces

void PrintBoard(string); //Print the ChessBoard
char DisplayPiece(int,int); //Display the ChessPiece

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
    }
    for(int w=0,b=16; w<2 && b<18; w++,b++) {
        piece[w].setPiece(Knight);
        piece[b].setPiece(Knight);
    }
    for(int w=2,b=18; w<4 && b<20; w++,b++) {
        piece[w].setPiece(Bishop);
        piece[b].setPiece(Bishop);
    }
    for(int w=4,b=20; w<6 && b<22; w++,b++) {
        piece[w].setPiece(Rook);
        piece[b].setPiece(Rook);
    }
    for(int w=6,b=22; w<7 && b<23; w++,b++) {
        piece[w].setPiece(Queen);
        piece[b].setPiece(Queen);
    }
    for(int w=7,b=23; w<8 && b<24; w++,b++) {
        piece[w].setPiece(King);
        piece[b].setPiece(King);
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
    if(r==0) 
    {
        if(f==0 || f==7)
            return 'R';
        if(f==1 || f==6)
            return 'N';
        if(f==2 || f==5)
            return 'B';
        if(f==3)
            return 'Q';
        if(f==4)
            return 'K';
    }
    else if(r==1) 
    {
        for(int w=0; w<8; w++)
            return 'P';
    }
    else if(r==6) 
    {
        for(int b=0; b<8; b++)
            return 'p';
    }
    else if(r==7) 
    {
        if(f==0 || f==7)
            return 'r';
        if(f==1 || f==6)
            return 'n';
        if(f==2 || f==5)
            return 'b';
        if(f==3)
            return 'q';
        if(f==4)
            return 'k';
    }
    
    return ' ';
}
