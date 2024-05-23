#ifndef PIPELINE_H
#define PIPELINE_H


#include "HitoriGenerator/BinaryBoard";
#include "HitoriGenerator/ComplexBoard";
#include "HitoriGenerator/TestBoard";

using namespace std;

template<class...Ts>
struct sink:std::function<void(Ts...)>{
  using std::function<void(Ts...)>::function;
};
template<class...Ts>
using source=sink<sink<Ts...>>;
template<class In, class Out>
using process=sink< source<In>, sink<Out> >;
template<class In, class Out>
sink<In> operator|( process< In, Out > a, sink< Out > b ){
  return [a,b]( In in ){
    a( [&in]( sink<In> s )mutable{ s(std::forward<In>(in)); }, b );
  };
}
template<class In, class Out>
source<Out> operator|( source< In > a, process< In, Out > b ){
  return [a,b]( sink<Out> out ){
    b( a, out );
  };
}
 
template<class In, class Mid, class Out>
process<In, Out> operator|( process<In, Mid> a, process<Mid, Out> b ){
  return [a,b]( source<In> in, sink<Out> out ){
    a( in, b|out ); // or b( in|a, out )
  };
}

template<class...Ts>
sink<> operator|( source<Ts...> a, sink<Ts...> b ){
  return[a,b]{ a(b); };
}

namespace HitoriGenerator {

process<int, BinaryBoard> get_solution = []( source<int> in, sink<BinaryBoard> out ){
  in( [&out]( int a ) { out( BinaryBoard(a) ); } );
};
process<BinaryBoard, ComplexBoard> get_quick = []( source<BinaryBoard> in, sink<ComplexBoard> out ){
  in( [&out]( BinaryBoard b ) { out( ComplexBoard(b) ); } );
};
process<ComplexBoard, TestBoard> get_quick = []( source<ComplexBoard> in, sink<TestBoard> out ){
  in( [&out]( ComplexBoard c ) { out( TestBoard(c) ); } );
};
process<TestBoard, HitoriBoard> get_quick = []( source<TestBoard> in, sink<HitoriBoard> out ){
  in( [&out]( TestBoard t ) { out( HitoriBoard(t) ); } );
};
source<int> number = []( sink<int> s ){
  s(9);
};
sink<HitoriBoard> show = []( HitoriBoard h ){c.show();};

}

#endif
