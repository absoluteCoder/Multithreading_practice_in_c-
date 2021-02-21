#include<iostream>
#include<chrono>
#include<thread>
/*

Mutex: Mutual Exclusion

RACE CONDITION:
0. Race condition is a situation where two or more threads/process happens to change a common data at the same time.
1. If there is a race condition then we have to protect it and the protected section is  called critical section/region.

MUTEX:
0. Mutex is used to avoid race condition.
1. We use lock() , unlock() on mutex to avoid race condition.
*/
int money = 0;
std::mutex m;
void addMoney(){
  m.lock();
  // other tx will be blocked
 for(int i = 0; i < 1000; i++){
   money++;
 }
 m.unlock();
}
//
int main(){

  std::thread t1(addMoney);
  std::thread t2(addMoney);
  std::thread t3(addMoney);
  std::thread t4(addMoney);
  std::thread t5(addMoney);
  std::thread t6(addMoney);
  std::thread t7(addMoney);
  std::thread t8(addMoney);
  std::thread t9(addMoney);
  std::thread t10(addMoney);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  t10.join();
  //8222came back after processing if no lock and  unlock
  // but now 10000
  std::cout<<money<<"came back after processing\n";
  return 0;
}