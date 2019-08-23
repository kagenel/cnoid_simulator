#include "sampleRTC.h"

// Module specification
static const char* samplertc_spec[] =
  {
    "implementation_id", "SampleRTC",
    "type_name",         "SampleRTC",
    "description",       "Robot Controller component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Generic",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };

SampleRTC::SampleRTC(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_angleIn("q", m_angle),
    m_torqueOut("tau", m_torque)
{
}

SampleRTC::~SampleRTC()
{
}

RTC::ReturnCode_t SampleRTC::onInitialize()
{
  RTC::Properties& prop = getProperties();
  m_instanceName = prop["instance_name"];
  std::cout << m_instanceName << " : onInitialize" << std::endl;


  addInPort("q", m_angleIn);
  addOutPort("tau", m_torqueOut);
 
  return RTC::RTC_OK;
}

RTC::ReturnCode_t SampleRTC::onActivated(RTC::UniqueId ec_id)
{
  std::cout << m_instanceName << " : onActivated" << std::endl;
  // initialize torque size
  m_angleIn.read();
  m_torque.data.length(m_angle.data.length());
  for(size_t i=0; i<m_angle.data.length(); ++i) {
    m_torque.data[i] = 0.;
  }
  
  return RTC::RTC_OK;
}

RTC::ReturnCode_t SampleRTC::onDeactivated(RTC::UniqueId ec_id)
{
  std::cout << m_instanceName << " : onDeactivated" << std::endl;

  return RTC::RTC_OK;
}

RTC::ReturnCode_t SampleRTC::onExecute(RTC::UniqueId ec_id)
{
  for( int i = 0; i < m_angle.data.length(); i++) {
    m_torque.data[0] = 1.0;
  }
  m_torqueOut.write();
  return RTC::RTC_OK;
}

extern "C"
{

  void SampleRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(samplertc_spec);
    manager->registerFactory(profile,
                             RTC::Create<SampleRTC>,
                             RTC::Delete<SampleRTC>);
  }

};
