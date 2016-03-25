#ifndef CPUEMULATOR_SRC_CMODEL_H
#define CPUEMULATOR_SRC_CMODEL_H
class UopBase
{
public:
  UopBase();
  virtual ~UopBase();
};
void opcode_run();
#endif //CPUEMULATOR_SRC_CMODEL_H
