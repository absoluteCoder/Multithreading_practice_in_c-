#include<mutex>
#include<thread>
#include<iostream>
#include<chrono>
using namespace std;
/*
0. std::try_lock() tries to lock all the mutexes passed in it one by one in given order.
1. On success this function returns -1 otherwise it will return 0-based mutex index number which it could not lock.
2. If it fails to lock any of the mutex then it will release all the mutex it locked before.
3. If a call to try_lock results in an exception, unlock is called for any locked objects before re-throwing.

*/

int X= 0, Y = 0;
mutex m1, m2;

void doSomeWorkForSeconds(int seconds){
  this_thread::sleep_for(chrono::seconds(seconds));
}

void incrementXY(int &XorY, mutex &m, const char *desc){
  for(int i = 0; i < 5; i++){
    m.lock();
      ++XorY;
      cout<<desc<<" "<<XorY<<"\n";
    m.unlock();
    doSomeWorkForSeconds(1);
  }
}
void consumeYX(){
  int useCount = 5;
  int xy = 0;
  int outside = 0;
  while(1){
    int x = try_lock(m1,m2);
    if(x == -1){
      if(X != 0 && Y!= 0){
        xy += X+Y;
        X = Y = 0;
        cout<<xy<<" whole value\n";
        useCount--;
      }
      outside++;
      m1.unlock();
      m2.unlock();
    }
    if(useCount == 0) break;
  }
  cout<<"\noutside value:: "<<outside<<"\n";
}
/*
we can see X and Y both are incremented parallely
Y X 1
1
2 whole value
Y 1
X 1
4 whole value
X Y 1
1
6 whole value
Y X 1
1
8 whole value
X 1
Y 1
10 whole value
*/
int main(){
  thread t1(incrementXY, ref(X), ref(m1), "X");
  thread t2(incrementXY, ref(Y), ref(m2), "Y");
  thread t3(consumeYX);
  t1.join();
  t2.join();
  t3.join();
  
  return 0;
}