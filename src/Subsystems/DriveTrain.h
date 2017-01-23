///////////////////////////////////////////////////////////////////////////////
//
// DriveTrain.h
//
//  Created on: Jan 7, 2017
//      Author: Silas A.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include <Commands/Subsystem.h>
#include <RobotDrive.h>
#include <CANTalon.h>
#include <Solenoid.h>

#include "../ExtSubsystem.h"

// Summary:
//	Class to manage the drive base of the robot
class DriveTrain : public frc::Subsystem, public ExtSubsystem
{
private:
	frc::RobotDrive* m_drive;

	// Slaves
	CANTalon* m_lf;
	CANTalon* m_rf;
	// Masters
	CANTalon* m_lb;
	CANTalon* m_rb;

	frc::Solenoid* m_shifter;
	bool m_shiftState;

	double m_targetSpeed = 0;

	bool m_reverse = false;

public:
	DriveTrain();
	~DriveTrain();
	void InitDefaultCommand();

	void Initialize() override;

	// Drive the bot in Arcade Drive (invert doesn't work)
	void ArcadeDrive(double move, double rotate);

	// Drive the bot in Tank Drive
	void TankDrive(double left, double right);

	// Sets which side is the front of the robot
	void Reverse(bool reverse);
	bool IsReversed() { return m_reverse; }

	// Toggles high/low gear
	void Shift();
};

#endif // DRIVE_TRAIN_H
