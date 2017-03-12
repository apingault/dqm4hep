/// \file ServiceHandler.cc
/*
 *
 * ServiceHandler.cc source template automatically generated by a class generator
 * Creation date : dim. d�c. 4 2016
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
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#include "dqm4hep/ServiceHandler.h"
#include "dqm4hep/Service.h"

namespace dqm4hep {

  namespace net {

    BaseServiceHandler::BaseServiceHandler(Client *pClient, const std::string &name) :
        m_pClient(pClient),
        m_name(name)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    BaseServiceHandler::~BaseServiceHandler()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &BaseServiceHandler::name() const
    {
      return m_name;
    }

    //-------------------------------------------------------------------------------------------------

    Client *BaseServiceHandler::client() const
    {
      return m_pClient;
    }

  }

}
