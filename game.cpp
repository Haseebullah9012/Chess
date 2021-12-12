#include <iostream>
#include <string>
using namespace std;

class Square
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

Square square[8][8]; //ChessBoard Squares

void PrintBoard(string); //Print the ChessBoard

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
                cout << " | " << square[r][f].getFile(); /* Print Square Here */
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
                cout << " | " << square[r][f].getRank(); /* Print Square Here */
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
