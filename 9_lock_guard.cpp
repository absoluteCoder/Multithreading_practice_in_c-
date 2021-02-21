/*
TOPIC: std::lock_guard In C++
 
NOTES:
0. It is very light weight wrapper for owning mutex on scoped basis i.e 
  It automatically removes the lock while goes out of scope..
1. It acquires mutex lock the moment you create the object of lock_guard.
2. You can not explicitly unlock the lock_guard.
3. You can not copy lock_guard.
*/
#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

std::mutex m;
int buffer = 0;
void func(char c){
  lock_guard<mutex> o(m);
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
  return 0;
}