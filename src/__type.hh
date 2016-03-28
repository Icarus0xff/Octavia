/* 
 * Authors: Augustus Liu 
 * Sun Mar 27 21:59:48 2016
 */
#ifndef CPUEMULATOR_TYPE_HH_
#define CPUEMULATOR_TYPE_HH_

#include <cstdio>
#include <cstdlib>

namespace CpuRegisterType
{
  typedef u_int32_t u32;
  typedef u_int16_t u16;
  typedef u_int8_t u8;

  namespace FundamentalDataTypeBackend{
    template <class Type, class Base>
    class FundamentalDataTypeOperators : public Base
    {
    public:
      FundamentalDataTypeOperators(Type const & _data)
      {
	Base::__data = _data;
      }

      Type &
      operator=(Type const & _data)
      {
	Base::__data = _data;
	return Base::__data;
      }
      
      Type &
      operator=(FundamentalDataTypeOperators const & other)
      {
	Base::__data = other;
	return Base::__data;
      }
      
      FundamentalDataTypeOperators() {};
    };
  }

#define __FundamentalDataTypes(type, name) \
  class FundamentalDataTypeUnderlyingClass##name \
  { \
  public: \
    type __data; \
    typedef type __DataType; \
    FundamentalDataTypeUnderlyingClass##name() {}; \
  }; \
  typedef FundamentalDataTypeBackend::FundamentalDataTypeOperators< \
    FundamentalDataTypeUnderlyingClass##name::__DataType, \
    FundamentalDataTypeUnderlyingClass##name> name;       								   

//Use this to define a Fundamentaldatatype like Dword, Byte, etc.
#define DataType(type, name) __FundamentalDataTypes(type, name)

  
  DataType(u32, Dword);
  DataType(u16, Word);
  DataType(u8, Byte);

  //Todo add ‘operator=’ func.
  //
  class Register
  {
  public:
    Register() {};
    union
    {
      Dword erx;
      union
      {
	Word rx;
	Byte rl;
	Byte rh;
      };
      Word idle;
    };
  };
}
#endif
