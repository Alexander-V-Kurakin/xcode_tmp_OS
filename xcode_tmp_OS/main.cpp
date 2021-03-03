//
//  main.cpp
//  xcode_tmp_OS
//
//  Created by MUC-StarChild-Mercury on 27.08.19.
//  Copyright © 2019 - 2021 MUC-StarChild-Mercury. All rights reserved.
//

#include <iostream>
#include <setjmp.h>

using namespace std;

#define TRACE(x) (cout << #x << " = " << x << endl)

#define ANY_VALUE 1         // ANY_VALUE != 0

static jmp_buf env_buf;     // Space to preserve the stack (environment) frame

void f2() {
    cout << "f2() is called" << endl;
    longjmp( env_buf, ANY_VALUE );      // Jumps back to where setjmp() was called,
                                        // making setjmp() now return ANY_VALUE
}

void f1() {
    f2();
    cout << "f1() is called" << endl;   // Not reached
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, C++14 World!" << endl;
    
    if ( !setjmp( env_buf ))    // setjmp() returns 0
                                // When longjmp() jumps back,
                                // setjmp() returns ANY_VALUE
        f1();
    else
        cout << "Back to main()" << endl;
    
    exit( 0 );
}
