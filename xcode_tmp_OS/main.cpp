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

#define ANY_VALUE 1     // ANY_VALUE != 0

jmp_buf main_task_env, child_task_env;  // Space to preserve the stack (environment) frame

void child_task() {
    int cc;     // Completion code
    
    while ( true ) {
        cout << "Child process entering" << endl;
            
        if ( !( cc = setjmp( child_task_env ))) {
            TRACE(cc);
            longjmp( main_task_env, ANY_VALUE );
        }
        
        TRACE(cc);

        cout << "Child process end" << endl;

        if ( !( cc = setjmp( child_task_env ))) {
            TRACE(cc);
            longjmp( main_task_env, ANY_VALUE );
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int cc;     // Completion code
    
    cout << "Hello, C++14 World!" << endl;
    
    if ( !( cc = setjmp( main_task_env ))) {    // setjmp() returns 0
                                                // When longjmp() jumps back,
                                                // setjmp() returns ANY_VALUE
        TRACE(cc);
        child_task();
    }
    
    TRACE(cc);
    
    for ( int i = 0; i < 5; i++ ) {           // Limited for debugging purpose
    //while ( true ) {
        cout << "Parent process" << endl;
            
        if ( !( cc = setjmp( main_task_env ))) {
            TRACE(cc);
            longjmp( child_task_env, ANY_VALUE );
        }
        
        TRACE(cc);
    }
    
    //exit( 0 );    // Code will never be executed. Instead, the flag should be set
                    // to indicate the end of context switching process and then
                    // longjmp( main_task_env, ANY_VALUE ) etc.
}

/*  Output:
 
 Hello, C++14 World!
 cc = 0
 Child process entering
 cc = 0
 cc = 1
 Parent process
 cc = 0
 cc = 1
 Child process end
 cc = 0
 cc = 1
 Parent process
 cc = 0
 Child process entering
 cc = 0
 cc = 1
 Parent process
 cc = 0
 cc = 1
 Child process end
 cc = 0
 cc = 1
 Parent process
 cc = 0
 Child process entering
 cc = 0
 cc = 1
 Parent process
 cc = 0
 cc = 1
 Child process end
 cc = 0
 cc = 1
 Program ended with exit code: 0
*/
