/*    Copyright (c) 2010-2012, Delft University of Technology
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without modification, are
 *    permitted provided that the following conditions are met:
 *      - Redistributions of source code must retain the above copyright notice, this list of
 *        conditions and the following disclaimer.
 *      - Redistributions in binary form must reproduce the above copyright notice, this list of
 *        conditions and the following disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *      - Neither the name of the Delft University of Technology nor the names of its contributors
 *        may be used to endorse or promote products derived from this software without specific
 *        prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 *    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      101111    E. Iorfida        Creation of code.
 *      101126    E. Iorfida        Virtual void "solve" added.
 *      101206    E. Iorfida        setInitialLambertState added, protected variables added.
 *      101207    E. Iorfida        Set single variables, change variables names in more
 *                                  understandable ones.
 *      110113    E. Iorfida        Added necessary elements to build pointer-to-member-function to
 *                                  RootFinderAlgorithms and NewtonRaphsonMethod classes.
 *      110124    E. Iorfida        Added necessary piece of code to be able to use the last
 *                                  version of Newton-Raphson code.
 *      110130    J. Melman         Simplified variable names, e.g., 'normOfVelocityVector' became
 *                                  'speed'. Also corrected 'tangential' to 'transverse'.
 *      110201    E. Iorfida        Added pointerToCelestialBody and modified variable names
 *                                  (from heliocentric, to inertial).
 *      110208    E. Iorfida        Added CartesianPositionElements objects as input and
 *                                  CartesianVelocityElements objects as output.
 *      120326    D. Dirkx          Changed raw pointers to shared pointers.
 *      120620    T. Secretin       Adapted and moved code from LambertTargeter.h.
 *
 *    References
 *
 *    Notes
 *
 */

#ifndef TUDAT_LAMBERT_TARGETER_GOODING_H
#define TUDAT_LAMBERT_TARGETER_GOODING_H

#include <boost/shared_ptr.hpp>

#include "Tudat/Astrodynamics/MissionSegments/lambertTargeter.h"
#include "Tudat/Mathematics/RootFindingMethods/newtonRaphson.h"

namespace tudat
{
namespace mission_segments
{

//! Gooding Lambert targeting algorithm class.
/*!
 * Implementation of the Gooding Lambert targeting algorithm in Tudat.
 */
class LambertTargeterGooding : public LambertTargeter
{
public:

    //! Constructor with imediate definition of parameters and execution of the algorithm.
    /*!
     * Constructor with imediate definition of parameters and execution of the algorithm.
     */
    LambertTargeterGooding( const Eigen::Vector3d cartesianPositionAtDeparture,
                            const Eigen::Vector3d cartesianPositionAtArrival,
                            const double timeOfFlight,
                            const double gravitationalParameter,
                            boost::shared_ptr< NewtonRaphson > newtonRaphson
                            = boost::shared_ptr< NewtonRaphson >( new NewtonRaphson ),
                            const double convergenceTolerance = 1e-9,
                            const int maximumNumberOfIterations = 50.0 )
        : LambertTargeter( cartesianPositionAtDeparture,
                           cartesianPositionAtArrival,
                           timeOfFlight,
                           gravitationalParameter ),
          newtonRaphson_( newtonRaphson ),
          convergenceTolerance_( convergenceTolerance ),
          maximumNumberOfIterations_( maximumNumberOfIterations )
    {
        // Execute algorithm.
        execute( );
    }

    //! Get radial velocity at departure.
    /*!
     * Returns the radial velocity at departure.
     * \return Radial velocity at departure.
     */
    double getRadialVelocityAtDeparture( );

    //! Get radial velocity at arrival.
    /*!
     * Returns the radial velocity at arrival.
     * \return Radial velocity at arrival.
     */
    double getRadialVelocityAtArrival( );

    //! Get transverse velocity at departure.
    /*!
     * Returns the transverse velocity at departure.
     * \return Transverse velocity at departure.
     */
    double getTransverseVelocityAtDeparture( );

    //! Get transverse velocity at arrival.
    /*!
     * Returns the transverse velocity at arrival.
     * \return Transverse velocity at arrival.
     */
    double getTransverseVelocityAtArrival( );

    //! Get semi-major axis.
    /*!
     * Returns the semi-major axis of the computed conic.
     * \return Semi-major axis.
     */
    double getSemiMajorAxis( );

protected:

    //! Execute Lambert targeting algorithm.
    /*!
     * Executes the Lambert targeting algorithm.
     */
    void execute( );

private:

    //! Newton-Raphson object.
    /*!
     * Newton-Raphson object needed for root-finding procedure in solveLambertProblemGooding().
     */
    const boost::shared_ptr< NewtonRaphson > newtonRaphson_;

    //! Convergence tolerance.
    /*!
     * Convergence tolerance for the root-finding process.
     */
    const double convergenceTolerance_;

    //! Maximum number of iterations.
    /*!
     * Maximum number of iterations for the root-finding process.
     */
    const double maximumNumberOfIterations_;
};

} // namespace mission_segments
} // namespace tudat

#endif // TUDAT_LAMBERT_TARGETER_IZZO_H
