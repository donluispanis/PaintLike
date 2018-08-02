#include "PaintLike.h"

int main()
{

    PaintLike p;

    if(!p.Init(1920,1040))
        return -1;
        
    p.Run();

    return 0;
}