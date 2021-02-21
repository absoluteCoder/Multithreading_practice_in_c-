/*
NOTES:
1. The class unique_lock is a mutex ownership wrapper.
2. It Allows:
    a. Can Have Different Locking Strategies
    b. time-constrained attempts at locking (try_lock_for, try_lock_until)
    c. recursive locking
    d. transfer of lock ownership (move not copy)
    e. condition variables. (See this in coming videos)

Locking Strategies
   TYPE           EFFECTS(S)
1. defer_lock  do not acquire ownership of the mutex.
2. try_to_lock  try to acquire ownership of the mutex without blocking.
3. adopt_lock  assume the calling thread already has ownership of the mutex.
*/

#include<iostream>
#include<mutex>
#include<thread>
#include<vector>
using namespace std;

std::mutex m;
int buffer = 0;
void func(char c){
  unique_lock<mutex> o(m);
  for(int i = 0; i < 10; i++){
    buffer++;
    cout<<buffer<<" "<<c<<"\n";
  }
}

void func2(char c){
  unique_lock<mutex> o(m, std::defer_lock);
  o.lock();
  for(int i = 0; i < 10; i++){
    buffer++;
    cout<<buffer<<" "<<c<<"\n";
  }
}

int main(){
  thread t1(func, '1');
  thread t2(func, '2');
  t1.join();
  t2.join();
  thread t3(func2, '3');
  thread t4(func2, '4');
  t3.join();
  t4.join();

  return 0;
}