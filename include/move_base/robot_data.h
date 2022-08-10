#pragma once

#include <geometry_msgs/PoseStamped.h>
#include <tf2/utils.h>

class RobotData {
public:
    RobotData(
        const geometry_msgs::PoseStamped& robot_pose,
        const geometry_msgs::PoseStamped& robot_vel,
        double obstacle_distance,
        double exec_time
    ): RobotData(robot_pose.pose, robot_vel.pose, obstacle_distance, exec_time) {}

    RobotData(
        const geometry_msgs::Pose& robot_pose,
        const geometry_msgs::Pose& robot_vel,
        double obstacle_distance,
        double exec_time
    ):
        pose_(robot_pose),
        vel_(robot_vel),
        obstacle_distance_(obstacle_distance),
        local_plan_exec_time_(exec_time)
    {}

	inline geometry_msgs::Pose getPose() const {
		return pose_;
	}

	inline geometry_msgs::Point getPosition() const {
		return pose_.position;
	}

	inline geometry_msgs::Quaternion getOrientation() const {
		return pose_.orientation;
	}

	inline double getPositionX() const {
		return pose_.position.x;
	}

	inline double getPositionY() const {
		return pose_.position.y;
	}

	inline double getPositionZ() const {
		return pose_.position.z;
	}

	inline double getOrientationYaw() const {
		return tf2::getYaw(pose_.orientation);
	}

	inline geometry_msgs::Pose getVelocity() const {
		return vel_;
	}

	inline double getVelocityX() const {
		return vel_.position.x;
	}

	inline double getVelocityY() const {
		return vel_.position.y;
	}

	inline double getVelocityZ() const {
		return vel_.position.z;
	}

	inline double getVelocityTheta() const {
		return tf2::getYaw(vel_.orientation);
	}

    inline double getDistToObstacle() const {
        return obstacle_distance_;
    }

    /// Returns duration of local plan computations
    inline double getLocalPlanningTime() const {
        return local_plan_exec_time_;
    }

protected:
    geometry_msgs::Pose pose_;
    geometry_msgs::Pose vel_;
    double obstacle_distance_;
    double local_plan_exec_time_;
};
