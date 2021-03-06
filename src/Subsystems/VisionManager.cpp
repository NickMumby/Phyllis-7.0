#include "VisionManager.h"
#include "../RobotMap.h"

VisionManager::VisionManager() :
	frc::Subsystem("Vision Manager")
{
	m_currentCam = -1;
}

void VisionManager::InitDefaultCommand()
{
	// SetDefaultCommand(new MySpecialCommand());
}

void VisionManager::Initialize()
{
	m_currentCam = 0;
	m_pegCam = m_cs->StartAutomaticCapture();
}

void VisionManager::SetCamera(int camera)
{
	switch (camera)
	{
	default:
	case 0:
		m_pegCam = m_cs->StartAutomaticCapture(camera);
		break;
	case 1:
		m_shootCam = m_cs->StartAutomaticCapture(camera);
		break;
	}
	m_currentCam = camera;
}
