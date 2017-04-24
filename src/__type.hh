/*
 * Authors: Augustus Liu
 * Sun Mar 27 21:59:48 2016
 */
#ifndef CPUEMULATOR_TYPE_HH_
#define CPUEMULATOR_TYPE_HH_

#include <cstdio>
#include <cstdlib>

namespace Enum {
enum {
  enum_CS = 0,
  enum_SS,
  enum_DS,
  enum_ES,
  enum_FS,
  enum_GS,
};

enum {
  enum_EAX = 0,
  enum_ECX,
  enum_EDX,
  enum_EBX,
  enum_ESP,
  enum_EBP,
  enum_ESI,
  enum_EDI,
};
}

namespace CpuRegisterType {
typedef u_int32_t u32;
typedef u_int16_t u16;
typedef u_int8_t u8;

// When a Fundamentaldatatype is set up, an underlying class if created which
// holds
// the actual data. This class inherits from it, and privides the
// implementations for various operators.
// Setting things up this way prevents having to redefine these functions in
// every different Fundamentaldatatype.
namespace FundamentalDataTypeBackend {
template <class Type, class Base>
class FundamentalDataTypeOperators : public Base {
public:
  FundamentalDataTypeOperators() = default;

  FundamentalDataTypeOperators(Type const &_data) { Base::__data = _data; }

  operator const Type() const { return Base::__data; }

  Type &operator=(Type const &_data) {
    Base::__data = _data;
    return Base::__data;
  }

  Type &operator=(FundamentalDataTypeOperators const &other) {
    Base::__data = other;
    return Base::__data;
  }

  Type &operator--() {
    --(Base::__data);
    return Base::__data;
  }

  Type &operator--(int) { (Base::__data)--; }

  Type &operator++() { ++(Base::__data); }

  Type &operator++(int) { (Base::__data)++; }

  Type &operator+=(FundamentalDataTypeOperators const &other) {
    Base::__data += other;
    return Base::__data;
  }

  Type &operator-=(FundamentalDataTypeOperators const &other) {
    Base::__data -= other;
    return Base::__data;
  }
};
}

#define __FundamentalDataTypes(type, name)                                     \
  class FundamentalDataTypeUnderlyingClass##name {                             \
  public:                                                                      \
    type __data;                                                               \
    typedef type __DataType;                                                   \
    FundamentalDataTypeUnderlyingClass##name() = default;                      \
  };                                                                           \
  typedef FundamentalDataTypeBackend::FundamentalDataTypeOperators<            \
      FundamentalDataTypeUnderlyingClass##name::__DataType,                    \
      FundamentalDataTypeUnderlyingClass##name>                                \
      name;

// Use this to define a Fundamentaldatatype like Dword, Byte, etc.
#define DataType(type, name) __FundamentalDataTypes(type, name)

DataType(u32, Dword);
DataType(u16, Word);
DataType(u8, Byte);

class Register {
public:
  union {
    Dword erx;
    union {
      Word rx;
      Byte rl;
      Byte rh;
    };
    Word idle;
  };

  Register() { erx = 0; }
};
}

#endif
