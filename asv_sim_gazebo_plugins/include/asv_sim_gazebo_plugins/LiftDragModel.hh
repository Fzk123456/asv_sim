// Copyright (C) 2019  Rhys Mainwaring
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef _ASV_SIM_GAZEBO_PLUGINS_LIFT_DRAG_MODEL_HH_
#define _ASV_SIM_GAZEBO_PLUGINS_LIFT_DRAG_MODEL_HH_

#include <ignition/math/Pose3.hh>
#include <ignition/math/Vector3.hh>

#include <sdf/sdf.hh>

#include <memory>

namespace asv
{
  class LiftDragModelPrivate;

  /// \brief A class to calculate lift / drag.
  class LiftDragModel
  {
    /// \brief Destructor.
    public: virtual ~LiftDragModel();

    /// \brief Constructor.
    public: LiftDragModel();
 
    /// \brief Create a new LiftDragModel from SDF.
    /// \param[in] _sdf A pointer to an SDF element containing parameters.
    public: static LiftDragModel* Create(const sdf::ElementPtr& _sdf);

    /// \brief Compute the lift and drag forces in the world frame.
    /// param[in] _velU     Free-stream velocity vector.
    /// param[out] _lift    Lift vector.
    /// param[out] _drag    Drag vector.
    public: void Compute(
      const ignition::math::Vector3d& _velU,
      const ignition::math::Pose3d& _bodyPose,
      ignition::math::Vector3d& _lift,
      ignition::math::Vector3d& _drag) const;

    /// \brief Compute the lift and drag forces in the world frame.
    /// param[in] _velU     Free-stream velocity vector.
    /// param[out] _lift    Lift vector.
    /// param[out] _drag    Drag vector.
    /// param[out] _alpha   Angle of attack in radians.
    /// param[out] _u       Free-stream speed in the lift/drag plane.
    /// param[out] _cd      Lift coefficient.
    /// param[out] _cd      Drag coefficient.
    public: void Compute(
      const ignition::math::Vector3d& _velU,
      const ignition::math::Pose3d& _bodyPose,
      ignition::math::Vector3d& _lift,
      ignition::math::Vector3d& _drag,
      double& _alpha,
      double& _u,
      double& _cl,
      double& _cd
      ) const;

    /// \brief The lift coefficient as a function of the angle of attack.
    /// \param[in] _alpha Angle of attack in radians.
    public: double LiftCoefficient(double _alpha) const;

    /// \brief The drag coefficient as a function of the angle of attack.
    /// \param[in] _alpha Angle of attack in radians.
    public: double DragCoefficient(double _alpha) const;

    /// \internal
    /// \brief Constructor, ownership transferred from data.
    private: LiftDragModel(std::unique_ptr<LiftDragModelPrivate>& data);

    /// \internal
    /// \brief Pointer to the class private data.
    private: std::unique_ptr<LiftDragModelPrivate> data;
  };

} // namespace asv

#endif // _ASV_SIM_GAZEBO_PLUGINS_LIFT_DRAG_MODEL_HH_
