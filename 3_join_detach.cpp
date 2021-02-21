#include<iostream>
#include<chrono>
#include<thread>
/*

DETACH NOTES
0. This is used to detach newly created thread from the parent thread.
1. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and 
   double detach() will result into program termination.
2. If we have detached thread and main function is returning then the detached thread execution is suspended.

NOTES:
Either join() or detach() should be called on thread object, otherwise during thread object�s destructor it will 
terminate the program. Because inside destructor it checks if thread is still joinable? if yes then it terminates the program.
*/

void run(int x){

  while(x-- > 0){
    std::cout<<x<<" ";
  }
  std::cout<<"printing done";
  std::this_thread::sleep_for(std::chrono::seconds(10));
}
int main(){

  std::thread t(run, 10);
  std::cout<<"hey main\n";
  //std::thread t2(run, 10);
  if(t.joinable())
    t.join(); 
  ///t2.join(); 
  // t.detach(); // it will say that don't need to wait for to complete it also suspend its execution
  std::cout<<"came back after processing\n";
  return 0;
}