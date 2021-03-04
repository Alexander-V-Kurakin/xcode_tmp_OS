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

#define EXCEPTION_TYPE_1 1
#define EXCEPTION_TYPE_2 2

static jmp_buf exception_env;   // Space to preserve the stack (environment) frame
static int exception_type;

void f2() {
    cout << "Entering f2()" << endl;

    exception_type = EXCEPTION_TYPE_2;
    longjmp( exception_env, exception_type );   // Jumps back to where setjmp() was called,
                                                // making setjmp() now return exception_type
}

void f1() {
    jmp_buf tmp_env;
    
    cout << "Entering f1()" << endl;
    
    memcpy( tmp_env, exception_env, sizeof( tmp_env ));

    switch ( setjmp( exception_env )) {
            
            // Normal, desired operation
            case 0:
                cout << "Calling f2()" << endl;
                f2();
                
            case EXCEPTION_TYPE_2:
                cout << "f2() failed, exception type: " << exception_type << ", " << "remapping to type 1" << endl;
                exception_type = EXCEPTION_TYPE_1;

            default:
                memcpy( exception_env, tmp_env, sizeof( exception_env ));   // Restore exception stack and
                longjmp( exception_env, exception_type );                   // continue handling the exception
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, C++14 World!" << endl;
    
    if ( setjmp( exception_env ))   // setjmp() returns 0
                                    // When longjmp() jumps back,
                                    // setjmp() returns exception_type
        
        cout << "f1() failed, exception type: " << exception_type << endl;
    
    else {
        cout << "Calling f1()" << endl;
        f1();
        cout << "f1() called" << endl;   // Not reached
    }
    
    exit( 0 );
}

/*  Output:
 
 Hello, C++14 World!
 Calling f1()
 Entering f1()
 Calling f2()
 Entering f2()
 f2() failed, exception type: 2, remapping to type 1
 f1() failed, exception type: 1
 Program ended with exit code: 0
*/
