#include <iostream>
using namespace std;

void PrintBoard(); //Print the ChessBoard

int main()
{
    cout << "\n Haseebullah's Chess! \n\n";

    PrintBoard();
    
    getchar();
    return 0;
}

void PrintBoard()
{
    cout << "      a   b   c   d   e   f   g   h      \n";
    
    for(int r=7; r>=0; r--) {
        cout << "     --- --- --- --- --- --- --- ---     \n";
        cout << " " << r+1 << " ";
        
        for(int f=0; f<8; f++) {     
            cout << " | " << " "; /* Print Square Here */
        }
        
        cout << " | " << " " << r+1 << " \n";
    }
    
    cout << "     --- --- --- --- --- --- --- ---     \n";
    cout << "      a   b   c   d   e   f   g   h      \n";
}
