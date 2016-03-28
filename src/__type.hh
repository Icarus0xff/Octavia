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

#define __FundamentalDataTypes(type, name) \
  class FundamentalDataTypeUnderlyingClass##name \
  { \
  public: \
    type __data; \
  }; \
  typedef FundamentalDataTypeUnderlyingClass##name name;


  __FundamentalDataTypes(u32, Dword)
  __FundamentalDataTypes(u16, Word)
  __FundamentalDataTypes(u8, Byte)

  //Todo add ‘operator=’ func.
  //
  class Register
  {
  public:
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
