/// \file Server.cc
/*
 *
 * Server.cc source template automatically generated by a class generator
 * Creation date : sam. d�c. 3 2016
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

// -- dqm4hep headers
#include "dqm4hep/Server.h"

// -- std headers
#include <sys/utsname.h>
#include <unistd.h>
#include "dic.hxx"

namespace dqm4hep {

  namespace net {

    Server::Server(const std::string &name) :
        m_name(name),
        m_started(false),
        m_serverInfoHandler(this, "/" + m_name + "/info", this, &Server::handleServerInfoRequest)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Server::~Server()
    {
      this->stop();
      this->clear();
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &Server::name() const
    {
      return m_name;
    }

    //-------------------------------------------------------------------------------------------------

    void Server::start()
    {
      if(m_started)
        return;

      for(auto iter = m_serviceMap.begin(), endIter = m_serviceMap.end() ; endIter != iter ; ++iter)
      {
        if(!iter->second->isServiceConnected())
          iter->second->connectService();
      }

      for(auto iter = m_requestHandlerMap.begin(), endIter = m_requestHandlerMap.end() ; endIter != iter ; ++iter)
      {
        if(!iter->second->isHandlingRequest())
          iter->second->startHandlingRequest();
      }

      for(auto iter = m_commandHandlerMap.begin(), endIter = m_commandHandlerMap.end() ; endIter != iter ; ++iter)
      {
        if(!iter->second->isHandlingCommands())
          iter->second->startHandlingCommands();
      }

      if(!m_serverInfoHandler.isHandlingRequest())
        m_serverInfoHandler.startHandlingRequest();

      DimServer::start(const_cast<char*>(m_name.c_str()));
      m_started = true;
    }

    //-------------------------------------------------------------------------------------------------

    void Server::stop()
    {
      if(!m_started)
        return;

      for(auto iter = m_serviceMap.begin(), endIter = m_serviceMap.end() ; endIter != iter ; ++iter)
      {
        if(iter->second->isServiceConnected())
          iter->second->disconnectService();
      }

      for(auto iter = m_requestHandlerMap.begin(), endIter = m_requestHandlerMap.end() ; endIter != iter ; ++iter)
      {
        if(iter->second->isHandlingRequest())
          iter->second->stopHandlingRequest();
      }

      for(auto iter = m_commandHandlerMap.begin(), endIter = m_commandHandlerMap.end() ; endIter != iter ; ++iter)
      {
        if(iter->second->isHandlingCommands())
          iter->second->stopHandlingCommands();
      }

      if(m_serverInfoHandler.isHandlingRequest())
        m_serverInfoHandler.stopHandlingRequest();

      DimServer::stop();
      m_started = false;
    }

    //-------------------------------------------------------------------------------------------------

    bool Server::isRunning() const
    {
      return m_started;
    }

    //-------------------------------------------------------------------------------------------------

    void Server::clear()
    {
      for(auto iter = m_serviceMap.begin(), endIter = m_serviceMap.end() ; endIter != iter ; ++iter)
        delete iter->second;

      for(auto iter = m_requestHandlerMap.begin(), endIter = m_requestHandlerMap.end() ; endIter != iter ; ++iter)
        delete iter->second;

      for(auto iter = m_commandHandlerMap.begin(), endIter = m_commandHandlerMap.end() ; endIter != iter ; ++iter)
        delete iter->second;

      m_serviceMap.clear();
      m_requestHandlerMap.clear();
      m_commandHandlerMap.clear();
      DimServer::stop();
      m_started = false;
    }

    //-------------------------------------------------------------------------------------------------

    Service *Server::createService(const std::string &name)
    {
      if(name.empty())
        throw std::runtime_error("Server::createService(): service name is invalid");

      auto findIter = m_serviceMap.find(name);

      if(findIter != m_serviceMap.end())
        return findIter->second;

      if(Server::serviceAlreadyRunning(name))
        throw std::runtime_error("Server::createService(): service '" + name + "' already running on network");

      // first insert nullptr, then create the service
      std::pair<ServiceMap::iterator, bool> inserted = m_serviceMap.insert(ServiceMap::value_type(name, nullptr));

      if(inserted.second)
      {
        Service *pService = new Service(this, name);
        inserted.first->second = pService;

        if(this->isRunning())
          pService->connectService();

        return pService;
      }
      else
        throw;
    }

    //-------------------------------------------------------------------------------------------------

    bool Server::isServiceRegistered(const std::string &name) const
    {
      return (m_serviceMap.find(name) != m_serviceMap.end());
    }

    //-------------------------------------------------------------------------------------------------

    bool Server::isRequestHandlerRegistered(const std::string &name) const
    {
      return (m_requestHandlerMap.find(name) != m_requestHandlerMap.end());
    }

    //-------------------------------------------------------------------------------------------------

    bool Server::isCommandHandlerRegistered(const std::string &name) const
    {
      return (m_commandHandlerMap.find(name) != m_commandHandlerMap.end());
    }

    //-------------------------------------------------------------------------------------------------

    void Server::startService(const std::string &name)
    {
      Service *pService = this->service(name);

      if(nullptr != pService && !pService->isServiceConnected())
        pService->connectService();
    }

    //-------------------------------------------------------------------------------------------------

    void Server::stopService(const std::string &name)
    {
      Service *pService = this->service(name);

      if(nullptr != pService && pService->isServiceConnected())
        pService->disconnectService();
    }

    //-------------------------------------------------------------------------------------------------

    void Server::startRequestHandler(const std::string &name)
    {
      RequestHandler *pRequestHandler = this->requestHandler(name);

      if(nullptr != pRequestHandler && !pRequestHandler->isHandlingRequest())
        pRequestHandler->startHandlingRequest();
    }

    //-------------------------------------------------------------------------------------------------

    void Server::stopRequestHandler(const std::string &name)
    {
      RequestHandler *pRequestHandler = this->requestHandler(name);

      if(nullptr != pRequestHandler && pRequestHandler->isHandlingRequest())
        pRequestHandler->stopHandlingRequest();
    }

    //-------------------------------------------------------------------------------------------------

    void Server::startCommandHandler(const std::string &name)
    {
      CommandHandler *pCommandHandler = this->commandHandler(name);

      if(nullptr != pCommandHandler && !pCommandHandler->isHandlingCommands())
        pCommandHandler->startHandlingCommands();
    }

    //-------------------------------------------------------------------------------------------------

    void Server::stopCommandHandler( const std::string &name)
    {
      CommandHandler *pCommandHandler = this->commandHandler(name);

      if(nullptr != pCommandHandler && pCommandHandler->isHandlingCommands())
        pCommandHandler->stopHandlingCommands();
    }

    //-------------------------------------------------------------------------------------------------

    Service *Server::service(const std::string &name) const
    {
      auto findIter = m_serviceMap.find(name);
      return (findIter == m_serviceMap.end() ? nullptr : findIter->second);
    }

    //-------------------------------------------------------------------------------------------------

    RequestHandler *Server::requestHandler(const std::string &name) const
    {
      auto findIter = m_requestHandlerMap.find(name);
      return (findIter == m_requestHandlerMap.end() ? nullptr : findIter->second);
    }

    //-------------------------------------------------------------------------------------------------

    CommandHandler *Server::commandHandler(const std::string &name) const
    {
      auto findIter = m_commandHandlerMap.find(name);
      return (findIter == m_commandHandlerMap.end() ? nullptr : findIter->second);
    }

    //-------------------------------------------------------------------------------------------------

    std::string Server::dnsNode()
    {
      char *pDnsNode = DimServer::getDnsNode();

      if(pDnsNode)
        return pDnsNode;

      pDnsNode = getenv("DIM_DNS_NODE");
      return (pDnsNode ? pDnsNode : "");
    }

    //-------------------------------------------------------------------------------------------------

    int Server::dnsPort()
    {
      return DimServer::getDnsPort();
    }

    //-------------------------------------------------------------------------------------------------

    std::vector<std::string> Server::runningServers()
    {
      std::vector<std::string> runningServers;

      DimBrowser browser;
      browser.getServers();
      char *pServer, *pNode;

      while(browser.getNextServer(pServer, pNode))
      {
        std::string server(pServer);
        runningServers.push_back(server);
      }

      return runningServers;
    }

    //-------------------------------------------------------------------------------------------------

    bool Server::isServerRunning(const std::string &serverName)
    {
      DimBrowser browser;
      browser.getServers();
      char *pServer, *pNode;

      while(browser.getNextServer(pServer, pNode))
      {
        std::string server(pServer);

        if(server == serverName)
          return true;
      }

      return false;
    }

    //-------------------------------------------------------------------------------------------------

    void Server::handleServerInfoRequest(const Buffer &/*request*/, Buffer &response)
    {
      Json::Value responseValue, serverInfo;
      serverInfo["name"] = m_name;
      responseValue["server"] = serverInfo;

      // uname
      struct utsname unameStruct;
      uname(&unameStruct);

      // host name
      char host[256];
      gethostname(host, 256);

      Json::Value hostInfo;
      hostInfo["name"] = host;
      hostInfo["system"] = unameStruct.sysname;
      hostInfo["node"] = unameStruct.nodename;
      hostInfo["release"] = unameStruct.release;
      hostInfo["version"] = unameStruct.version;
      hostInfo["machine"] = unameStruct.machine;
      responseValue["host"] = hostInfo;

      Json::Value serviceList(Json::arrayValue);
      unsigned int index(0);

      for(auto iter = m_serviceMap.begin(), endIter = m_serviceMap.end() ; endIter != iter ; ++iter)
      {
        const std::string &name(iter->second->name());
        serviceList[index] = name;
        ++index;
      }

      responseValue["services"] = serviceList;

      Json::Value requestHandlerList;
      index = 0;

      for(auto iter = m_requestHandlerMap.begin(), endIter = m_requestHandlerMap.end() ; endIter != iter ; ++iter)
      {
        const std::string &name(iter->second->name());
        requestHandlerList[index] = name;
        ++index;
      }

      responseValue["requestHandlers"] = requestHandlerList;

      Json::Value commandHandlerList;
      index = 0;

      for(auto iter = m_commandHandlerMap.begin(), endIter = m_commandHandlerMap.end() ; endIter != iter ; ++iter)
      {
        const std::string &name(iter->second->name());
        commandHandlerList[index] = name;

        ++index;
      }

      responseValue["commandHandlers"] = commandHandlerList;

      Json::StreamWriterBuilder builder;
      std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
      std::ostringstream jsonResponse;
      writer->write(responseValue, &jsonResponse);

      response.adopt(jsonResponse.str().c_str(), jsonResponse.str().size());
    }

    //-------------------------------------------------------------------------------------------------

    bool Server::serviceAlreadyRunning(const std::string &name)
    {
      DimBrowser browser;
      int nServices = browser.getServices(name.c_str());

      if(nServices == 0)
        return false;

      int serviceType;
      char *serviceName, *format;

      while(1)
      {
        serviceType = browser.getNextService(serviceName, format);

        if(serviceType == 0)
          break;

        if(serviceType == DimSERVICE)
          return true;
      }

      return false;
    }

    //-------------------------------------------------------------------------------------------------

    bool Server::requestHandlerAlreadyRunning(const std::string &name)
    {
      DimBrowser browser;
      int nServices = browser.getServices(name.c_str());

      if(nServices == 0)
        return false;

      int serviceType;
      char *serviceName, *format;

      while(1)
      {
        serviceType = browser.getNextService(serviceName, format);

        if(serviceType == 0)
          break;

        if(serviceType == DimRPC)
          return true;
      }

      return false;
    }

    //-------------------------------------------------------------------------------------------------

    bool Server::commandHandlerAlreadyRunning(const std::string &name)
    {
      DimBrowser browser;
      int nServices = browser.getServices(name.c_str());

      if(nServices == 0)
        return false;

      int serviceType;
      char *serviceName, *format;

      while(1)
      {
        serviceType = browser.getNextService(serviceName, format);

        if(serviceType == 0)
          break;

        if(serviceType == DimCOMMAND)
          return true;
      }

      return false;
    }

  }

}
