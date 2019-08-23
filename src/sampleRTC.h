#ifndef SAMPLERTC_H
#define SAMPLERTC_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

class SampleRTC : public RTC::DataFlowComponentBase
{
public:
  SampleRTC(RTC::Manager* manager);
  ~SampleRTC();
  virtual RTC::ReturnCode_t onInitialize();
  virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
  virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
  virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

protected:
  // m_hoge;               // 入出力用の変数
  // InPort<> m_hogeIn;    // 入力ポートから入力
  // OutPort<> m_hogeOut;  // 出力ポートへの出力
  RTC::TimedDoubleSeq m_angle;
  RTC::InPort<RTC::TimedDoubleSeq> m_angleIn;
  
  RTC::TimedDoubleSeq m_torque;
  RTC::OutPort<RTC::TimedDoubleSeq> m_torqueOut;

private:
  std::string m_instanceName;
};

extern "C"
{
  DLL_EXPORT void SampleRTCInit(RTC::Manager* manager);
};

#endif
