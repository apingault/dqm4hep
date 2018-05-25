// \file AnalysislHelper.h
/*
 *
 * AnalysisHelper.h header template automatically generated by a class generator
 * Creation date : ???
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Tom Coates
 * @copyright CNRS , IPNL
 */

#ifndef DQM4HEP_ANALYSISHELPER_H
#define DQM4HEP_ANALYSISHELPER_H

// Need to include ROOT headers so that it can interpret things like TH1 etc.

// -- dqm4hep headers
#include <dqm4hep/StatusCodes.h>
#include <dqm4hep/Internal.h>
#include <dqm4hep/Logging.h>
#include <dqm4hep/MonitorElement.h>

// -- root headers
#include <TH1.h>
#include <TMath.h>

namespace dqm4hep {

  namespace core {

    /** analysis helper class
     */
    class AnalysisHelper
    {
    public:

      static float mean(MonitorElementPtr pMonitorElement, float percentage = 1.0);

      static float mean90(MonitorElementPtr pMonitorElement);

      static float rms(MonitorElementPtr pMonitorElement, float percentage = 1.0);

      static float rms90(MonitorElementPtr pMonitorElement);

      static float median(MonitorElementPtr pMonitorElement);

    };

  }

}

#endif // DQM4HEP_ANALYSISHELPER_H
