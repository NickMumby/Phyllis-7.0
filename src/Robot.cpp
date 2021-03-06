///////////////////////////////////////////////////////////////////////////////
//
// Robot.cpp
//
//  Created on: Jan 7, 2017
//      Author: Silas A.
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "CommandBase.h"

#include "Commands/Shoot.h"

class Robot: public frc::IterativeRobot
{
private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;

public:
	void InitializeSubsystems()
	{
		CommandBase::drive.get()->Initialize();
		CommandBase::shooter.get()->Initialize();
		CommandBase::gearCollector.get()->Initialize();
		CommandBase::climber.get()->Initialize();
		CommandBase::fuelCollector.get()->Initialize();
	}

	void RobotInit() override
	{
		InitializeSubsystems();

		//chooser.AddDefault("Default Auto", new ExampleCommand());
		// chooser.AddObject("My Auto", new MyAutoCommand());
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
	}

	void RobotPeriodic() override
	{

	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override
	{

	}

	void DisabledPeriodic() override
	{
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override
	{
		autonomousCommand.reset(chooser.GetSelected());

		if (autonomousCommand.get() != nullptr)
		{
			autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic() override
	{
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override
	{
		if (autonomousCommand != nullptr)
		{
			autonomousCommand->Cancel();
		}
		autonomousCommand = std::make_unique<Shoot>();
		autonomousCommand.get()->Start();
	}

	void TeleopPeriodic() override
	{
		frc::Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override
	{
		frc::LiveWindow::GetInstance()->Run();
	}


};

START_ROBOT_CLASS(Robot)
