#include <iostream>
#include <string>
using namespace std;

void PrintBoard(string); //Print the ChessBoard

int main()
{
    cout << "\n Haseebullah's Chess! \n";

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
                cout << " | " << " "; /* Print Square Here */
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
                cout << " | " << " "; /* Print Square Here */
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
