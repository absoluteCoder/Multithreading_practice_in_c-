

#include<iostream>
#include<thread>

void using_lamda_demo(){
  /*
    auto lambda_func_name = [](int argument){
      while(argument-- > 0){
        std::cout<<argument<<" ";
      }
      std::cout<<"end of function\n";
    };
  */  
  // decalring lambda in that itself
  std::thread t1([](int argument){
    while(argument-- > 0){
      std::cout<<argument<<" ";
    }
    std::cout<<"end of function\n";
  }, 10);
  t1.join();
}

class A{
  public: 
    void operator()(int x){
      while(x-->0){
        std::cout<<x<<" ";
      }
      std::cout<<"end of functor\n";
    }
};
void demo_of_functors(){ // function object
  std::thread t(A(), 10); // here Base() is functor  i.e. operator
  t.join();
}

class B{
  public:
    void non_static_member_function(int x){
      while(x-- > 0){
        std::cout<<x<<" ";
      }
      std::cout<<" End of non_static_member fucntions\n";
    }
};
void demo_of_non_static_member_function(){
  B obj;
  std::thread t(&B::non_static_member_function, &obj, 10);
  t.join();
}
class C{
  public:
    static void static_member_function(int x){
      while(x-- > 0){
        std::cout<<x<<" ";
      }
      std::cout<<" End of static_member_function\n";
    }
};
void demo_of_static_member_function(){
  std::thread t(C::static_member_function, 10);
  t.join();
}


int main(){
  using_lamda_demo();
  demo_of_functors();
  demo_of_non_static_member_function();
  demo_of_static_member_function();
  return 0;
}