/*
1. Condition variables allow us to synchronize threads via notifications.
   a. notify_one();
   b. notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronize two or more threads.
4. Best use case of condition variable is Producer/Consumer problem.
5. Condition variables can be used for two purposes:
    a. Notify other threads
    b. Wait for some condition

For more please watch full video and do let me know if you have any doubts in the comment section.

for dead long in any locking mechanism comes because of ordering of lock sequence in different-different functions

lock(m1, m2, m3, m4) is lock each or none
and also after locking all by std::lock()
we also need to perform unlock on each.

 */
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;
// so 
condition_variable cv;
mutex m;
int money = 0;
void credit(int amount){
  cout<<"in credit"<<"\n";
  lock_guard<mutex> o(m);
  money += amount;
  cout<<amount<<" credit\n";
  cv.notify_one();
}

void debit(int amount){
  cout<<"in debit\n";
  unique_lock<mutex> o(m);
  cv.wait(o, [](){ return money != 0; });
  if(money < amount){
    cout<<"not possible to get money as "<<money<<" and "<<amount<<"\n";
  }
  else {
    money -= amount;
    cout<<"you got you money ok";
  }
}

int main(){
  thread t1(debit, 100);
  thread t2(credit, 100);
  t1.join();
  t2.join();
  return 0;
}
