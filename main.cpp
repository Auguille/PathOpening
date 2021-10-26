#include "PO.h"

int main(int argc, char const *argv[])
{
    std::string input, output;
    int L;

    if(argc == 4)
    {
        input = argv[1];
        output = argv[3];
        L = atoi(argv[2]);
    }
    else
    {
        input = "Images/Test.pgm";
        output = "Results/Test-3.pgm";
        L = 3;
    }

    PO path(input);
    for(int i=1; i<5; ++i)
    {
        path.computePO(L,i);
        path.reset();
    }

    path.writeResult(output);
    
    return 0;
}
