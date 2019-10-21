#include "Sequencer.h"
#include <iostream>

//first example
int main()
{
    Base::SequencerLauncher seq("my text", 10);
    for (int i=0; i<10; i++)
    {
        std::cout << "do some work";
       // do something
        seq.next ();
    }
    return 0;
}