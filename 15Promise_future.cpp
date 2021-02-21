/*

*/
#include<iostream>
#include<thread>
#include<future>

using namespace std;
#define ll long long int
void getSum(promise <ll> p, ll l, ll r){
  ll sum = 0;
  for(ll i = l; i < r; i++){
    sum += i;
  }
  this_thread::sleep_for(std::chrono::seconds(2));
  p.set_value(sum);
}

/*
DESCRIPTION :
Here we will learn std::async and its usage like how to create task. There are three different launch policy for creating task using std::async are as follows:
1. std::launch::async
2. std::launch::deffered
3. std::launch::async | std::launch::deffered

With the help of above policies std::async decides to create task as asynchronous or synchronous. Please go through video for more details.


Producer Consumer OR Bounded Buffer Problem

THE PROBLEM STATEMENT:
 1. Producer will produce and consumer will consume with synchronization of a common buffer.
 2. Until producer thread produces any data consumer thread can't consume.
 3. Threads will use condition_variable to notify each other.
 4. We need mutex if we use condition_variable because CV waits on mutex.
 5. This is one of the example of producer consumer there are many.

PRODUCER thread steps:
 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
 2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.
 3. insert item in buffer.
 4. unlock mutex. 
 5. notify consumer.

CONSUMER thread steps:
 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
 2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not thean go ahead and consume.
 3. consume item from buffer.
 4. unlock mutex.
 5. notify producer.

IMP:
 Producer and Consumer have to notify each other upon comletion of their job.
*/
int main(){
  promise <ll> sum;
  future<ll> sumFuture = sum.get_future();
  thread t(getSum, move(sum), 1, 10000000);

  cout<<"is calculating we can do here our thing\n";
  cout<<"sum is "<<sumFuture.get()<<"\n";
  cout<<"completed\n";
  t.join();
  return 0;
}