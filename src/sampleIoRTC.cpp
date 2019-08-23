
#include <cnoid/BodyIoRTC>
#include <cnoid/AccelerationSensor>
#include <cnoid/RateGyroSensor>
#include <cnoid/Light>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

using namespace std;
using namespace cnoid;

namespace {

class SampleIoRTC : public BodyIoRTC
{
public:
    SampleIoRTC(RTC::Manager* manager);
    ~SampleIoRTC();

    virtual bool initializeIO(ControllerIO* io) override;
    virtual bool initializeSimulation(ControllerIO* io) override;
    virtual void inputFromSimulator() override;
    virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;
    virtual void outputToSimulator() override;

    BodyPtr ioBody;

    RTC::TimedDoubleSeq m_angle;
    RTC::InPort<RTC::TimedDoubleSeq> m_angleIn;

    RTC::TimedDoubleSeq m_torque;
    RTC::OutPort<RTC::TimedDoubleSeq> m_torqueOut;

};


const char* spec[] =
{
    "implementation_id", "SampleIoRTC",
    "type_name",         "SampleIoRTC",
    "description",       "Sample3R I/O",
    "version",           "1.0",
    "vendor",            "AIST",
    "category",          "Generic",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "10",
    "language",          "C++",
    "lang_type",         "compile",
    ""
};

}

SampleIoRTC::SampleIoRTC(RTC::Manager* manager)
    : BodyIoRTC(manager),
      m_angleIn("mq", m_angle),
      m_torqueOut("tau", m_torque)
{

}


SampleIoRTC::~SampleIoRTC()
{

}


bool SampleIoRTC::initializeIO(ControllerIO* io)
{
    std::cout << " : initializeIO" << std::endl;

    // Set InPort buffers
    addInPort("mq", m_angleIn);
    
    // Set OutPort buffer
    addOutPort("tau", m_torqueOut);

    return true;
}

// port設定の役割
bool SampleIoRTC::initializeSimulation(ControllerIO* io)
{
  std::cout << " : initializeSimulation" << std::endl;

    ioBody = io->body();
    
    // JointR = ioBody->link("R_JOINT_1");
    // JointR->setActuationMode(Link::JOINT_TORQUE);

    // std::cout << " : " << ioBody->numJoints()  << std::endl;

    for(auto joint : ioBody->joints()){
        if(joint->isRevoluteJoint() || joint->isPrismaticJoint()){
            joint->setActuationMode(Link::JOINT_TORQUE);
        }
    }

    return true;
}


void SampleIoRTC::inputFromSimulator()
{
  std::cout << " : inputFromSimulator" << std::endl;

  // angles.data[0] = turretY->q();
  // angles.data[1] = turretP->q();
  
  // auto dv = accelSensor->dv();
  // accel.data.ax = dv.x();
  // accel.data.ay = dv.y();
  // accel.data.az = dv.z();
  
  // auto w = gyro->w();
  // angularVelocity.data.avx = w.x();
  // angularVelocity.data.avy = w.y();
  // angularVelocity.data.avz = w.z();

  if(m_angleIn.isNew()){
    m_angleIn.read();
    int n = m_angle.data.length();
    for(int i=0; i < n; ++i){
      if(i < ioBody->numJoints()){
        m_angle.data[i] = ioBody->joint(i)->q();
      }
    }
  }
  

}


RTC::ReturnCode_t SampleIoRTC::onExecute(RTC::UniqueId ec_id)
{
  std::cout << " : onExecute" << std::endl;

    // anglesOut.write();
    // accelOut.write();

  // for( int i = 0; i < m_angle.data.length(); i++) {
  //   m_torque.data[0] = 1.0;
  // }


      
    // if(torquesIn.isNew()){
    //     torquesIn.read();
    // }
    // if(velocitiesIn.isNew()){
    //     velocitiesIn.read();
    // }
    // if(light && lightSwitchIn.isNew()){
    //     lightSwitchIn.read();
    // }
    return RTC::RTC_OK;
}


void SampleIoRTC::outputToSimulator()
{
  std::cout << " : outputToSimulator" << std::endl;

  for(auto joint : ioBody->joints()){
    int index = joint->jointId();
    // m_torque.data[index] = joint->u();
    // m_torque.data[index] = 1.0;
  }

  ioBody->joint(0)->u() = 1.0;

  m_torqueOut.write();

}


extern "C"
{
    DLL_EXPORT void SampleIoRTCInit(RTC::Manager* manager)
    {
        coil::Properties profile(spec);
        manager->registerFactory(
            profile, RTC::Create<SampleIoRTC>, RTC::Delete<SampleIoRTC>);
    }
};
