/*
TOPIC: Timed Mutex In C++ Threading (std::timed_mutex)
We have learned Mutex, Race Condition, Critical Section in previous videos.

NOTES:
0. std::timed_mutex is blocked till timeout_time or the lock is aquired and returns true if success 
   otherwise false.
1. Member Function:
   a. lock 
   b. try_lock
   c. try_lock_for    ---\ 
                          \
                           > These two functions makes it different from mutex.
                          /
   d. try_lock_until  ---/ 
   e. unlock

EXAMPLE: try_lock_for();
Waits until specified timeout_duration has elapsed or the lock is acquired, whichever comes first.
On successful lock acquisition returns true, otherwise returns false.

wait till 10PM or something
try_lock_until(x)
*/
#include<mutex>
#include<thread>
#include<iostream>
#include<chrono>
using namespace std;
int global_var = 0;

timed_mutex m;
void waitForSecond(int sec){
  this_thread::sleep_for(chrono::seconds(sec));
}
void func(int threadNo){
  /*
  if below second is 2:
    able to enter for thread2
    finishing 2
    able to enter for thread1
    finishing 1
    2 value at end
  else if 1:
      able to enter for thread2
      finishing 2
      could not able to get lock in that second
      1 value at end
  */
  // m.try_lock_until(some fix time till what it wait)
  if(m.try_lock_for(chrono::seconds(1))){
    global_var++;
    cout<<"able to enter for thread"<<threadNo<<"\n";
    waitForSecond(1);
    cout<<"finishing "<<threadNo<<"\n";
    m.unlock();
  }
  else{
    cout<<"could not able to get lock in that second\n";
  }
}

int main(){
  thread t1(func, 1);
  thread t2(func, 2);
  t1.join();
  t2.join();
  cout<<global_var<<" value at end\n";
}

