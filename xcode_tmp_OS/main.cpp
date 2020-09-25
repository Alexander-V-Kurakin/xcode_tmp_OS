//
//  main.cpp
//  xcode_tmp_OS
//
//  Created by MUC-StarChild-Mercury on 27.08.19.
//  Copyright © 2019 MUC-StarChild-Mercury. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#define TRACE(x) (cout << #x << " = " << x << endl)

pid_t pid;

// Create and initialise the mutex for use
pthread_mutex_t loop_counter_mutex = PTHREAD_MUTEX_INITIALIZER;

// The global resource the mutex is to protect
int loop_counter;


void* thread_func(void* arg)
{
    pthread_mutex_lock(&loop_counter_mutex);
    
    for (loop_counter = 0; loop_counter < 10; loop_counter++)
        cout << "I'm a " << (char*)arg << "loop counter " << loop_counter << endl;
    
    pthread_mutex_unlock(&loop_counter_mutex);
    
    return NULL;
}

void do_child_thing()
{
    cout << "I'm a child w/ pid = " << pid << ", my parent pid = " << getpid() << endl;
    
    pthread_t idThread1, idThread2;
    
    pthread_create(&idThread1, NULL, thread_func, (void*) "thread's 1 ");
    pthread_join(idThread1, NULL);
    pthread_create(&idThread2, NULL, thread_func, (void*) "thread's 2 ");
    pthread_join(idThread2, NULL);
}

void do_parent_thing()
{
    cout << "I'm a parent w/ pid = " << pid << ", my parent pid = " << getppid() << endl;
    //    TRACE(getppid());    // returns the id of the calling process
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, C++14 World!" << endl;
    
    switch ( pid = fork() ){
        case -1:
            cout << "fork() failed" << endl;
            break;
            
        case 0:
            do_child_thing();
            break;
            
        default:
            do_parent_thing();
    }
    
    exit( 0 );
}
