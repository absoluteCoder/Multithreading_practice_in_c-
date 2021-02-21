/*
  knowledge:
  ways to create thread 
  1: Static Member functions 
  2: Member functions
  3: Functors
  4: Lambda Functions
  5: Fucntions Pointers
*/


// in this we are using function pointer i.e. just function name itself
#include<iostream>

// for getting time
// http://www.cplusplus.com/reference/chrono/

// with explanation all three type in this 
// https://en.cppreference.com/w/cpp/chrono
#include<chrono>

// main thread library
#include<thread>

//#include<algorithm>

typedef unsigned long long ll;


ll odd_sum = 0;
ll even_sum = 0;

void calculate_odd_sum(int l, int r){
  for(int i = l; i <= r; i++){
    if(i&1){
      odd_sum += i;
    }  
  }
}
void calculate_even_sum(int l, int r){
  for(int i = l; i <= r; i++){
    if((i&1) == 0){
      even_sum += i;
    } 
  }
}

int main(){
  ll rangeFrom =0, rangeTo = 19e8;
  auto startTime = std::chrono::high_resolution_clock::now();
  
  std::thread t1(calculate_even_sum, rangeFrom, rangeTo);
  t1.join();
  std::thread t2(calculate_odd_sum, rangeFrom, rangeTo);
  
  t2.join();

  auto endTime = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds> (endTime-startTime);

  std::cout<<odd_sum<<" \n "<<even_sum<<"\n";
  std::cout<<"Execution time"<<duration.count()/10000<<"\n";


}
