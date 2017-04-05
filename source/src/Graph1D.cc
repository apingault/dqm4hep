/// \file Graph1D.cc
/*
*
* Graph1D.cc source template automatically generated by a class generator
* Creation date : jeu. f�vr. 2 2017
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


#include "dqm4hep/Graph1D.h"

namespace dqm4hep {

  namespace core {

    Graph1D::Point::Point() :
      m_x(0.f),
      m_xErrLow(0.f),
      m_xErrUp(0.f),
      m_y(0.f),
      m_yErrLow(0.f),
      m_yErrUp(0.f)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Graph1D::Point::Point(float x, float y) :
      m_x(x),
      m_xErrLow(0.f),
      m_xErrUp(0.f),
      m_y(y),
      m_yErrLow(0.f),
      m_yErrUp(0.f)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Graph1D::Point::Point(float x, float y, float ex, float ey) :
      m_x(x),
      m_xErrLow(ex),
      m_xErrUp(ex),
      m_y(y),
      m_yErrLow(ey),
      m_yErrUp(ey)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Graph1D::Point::Point(float x, float y, float exl, float exu, float eyl, float eyu) :
      m_x(x),
      m_xErrLow(exl),
      m_xErrUp(exu),
      m_y(y),
      m_yErrLow(eyl),
      m_yErrUp(eyu)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    Graph1D::Graph1D() :
      MonitorObject(),
      m_minimum(std::numeric_limits<float>::max()),
      m_maximum(std::numeric_limits<float>::min())
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Graph1D::~Graph1D()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    Graph1D *Graph1D::create(const Json::Value &value)
    {
      Graph1D *pGraph = new Graph1D();
      pGraph->fromJson(value);
      return pGraph;
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::setTitle(const std::string &title)
    {
      m_title = title;
      m_updateCache.set(TITLE, true);
      this->updated(TITLE);
    }

    //-------------------------------------------------------------------------------------------------

    const std::string &Graph1D::getTitle() const
    {
      return m_title;
    }

    //-------------------------------------------------------------------------------------------------

    float Graph1D::getMaximum() const
    {
      return m_maximum;
    }

    //-------------------------------------------------------------------------------------------------

    float Graph1D::getMinimum() const
    {
      return m_minimum;
    }

    //-------------------------------------------------------------------------------------------------

    int Graph1D::addPoint(const Graph1D::Point &point)
    {
      if(point.m_y > m_maximum)
        m_maximum = point.m_y;

      if(point.m_y < m_minimum)
        m_minimum = point.m_y;

      m_points.push_back(point);

      m_updateCache.set(POINTS, true);
      this->updated(POINTS);

      return m_points.size()-1;
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::setPoint(int index, const Graph1D::Point &point)
    {
      if(index < 0 || index >= m_points.size())
        throw std::out_of_range("Graph1D::setPoint(index, point)");

      if(point.m_y > m_maximum)
        m_maximum = point.m_y;

      if(point.m_y < m_minimum)
        m_minimum = point.m_y;

      m_points.at(index) = point;

      m_updateCache.set(POINTS, true);
      this->updated(POINTS);
    }

    //-------------------------------------------------------------------------------------------------

    const Graph1D::Point &Graph1D::getPoint(int index) const
    {
      return m_points.at(index);
    }

    //-------------------------------------------------------------------------------------------------

    const Graph1D::PointSet &Graph1D::getPoints() const
    {
      return m_points;
    }

    //-------------------------------------------------------------------------------------------------

    unsigned int Graph1D::getNPoints() const
    {
      return m_points.size();
    }

    //-------------------------------------------------------------------------------------------------

    float Graph1D::getPointX(int index) const
    {
      if(index < 0 || index >= m_points.size())
        throw std::out_of_range("Graph1D::getPointX(index)");

      return m_points.at(index).m_x;
    }

    //-------------------------------------------------------------------------------------------------

    float Graph1D::getPointY(int index) const
    {
      if(index < 0 || index >= m_points.size())
        throw std::out_of_range("Graph1D::getPointX(index)");

      return m_points.at(index).m_x;
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::getPointErrors(int index, float &errorXLow, float &errorXUp, float &errorYLow, float &errorYUp) const
    {
      if(index < 0 || index >= m_points.size())
        throw std::out_of_range("Graph1D::getPointX(index)");

      const Point point(m_points.at(index));

      errorXLow = point.m_xErrLow;
      errorXUp = point.m_xErrUp;
      errorYLow = point.m_yErrLow;
      errorYUp = point.m_yErrUp;
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::clear()
    {
      m_points.clear();
      m_minimum = std::numeric_limits<float>::max();
      m_maximum = std::numeric_limits<float>::min();

      m_xAxisAttributes.reset();
      m_yAxisAttributes.reset();
      m_title.clear();

      m_markerAttributes.reset();
      m_lineAttributes.reset();

      // set up cache for next streaming
      m_updateCache.set(POINTS, true); this->updated(POINTS);
      m_updateCache.set(AXIS_X, true); this->updated(AXIS_X);
      m_updateCache.set(AXIS_Y, true); this->updated(AXIS_Y);
      m_updateCache.set(MARKER, true); this->updated(MARKER);
      m_updateCache.set(LINE, true); this->updated(LINE);
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::setLineAttributes(const LineAttributes &attributes)
    {
      m_updateCache.set(LINE, true);
      m_lineAttributes = attributes;
      this->updated(LINE);
    }

    //-------------------------------------------------------------------------------------------------

    const LineAttributes &Graph1D::getLineAttributes() const
    {
      return m_lineAttributes;
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::setMarkerAttributes(const MarkerAttributes &attributes)
    {
      m_updateCache.set(MARKER, true);
      m_markerAttributes = attributes;
      this->updated(MARKER);
    }

    //-------------------------------------------------------------------------------------------------

    const MarkerAttributes &Graph1D::getMarkerAttributes() const
    {
      return m_markerAttributes;
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::setXAxisAttributes(const AxisAttributes &attributes)
    {
      m_xAxisAttributes = attributes;
      m_updateCache.set(AXIS_X, true);
      this->updated(AXIS_X);
    }

    //-------------------------------------------------------------------------------------------------

    const AxisAttributes &Graph1D::getXAxisAttributes() const
    {
      return m_xAxisAttributes;
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::setYAxisAttributes(const AxisAttributes &attributes)
    {
      m_yAxisAttributes = attributes;
      m_updateCache.set(AXIS_Y, true);
      this->updated(AXIS_Y);
    }

    //-------------------------------------------------------------------------------------------------

    const AxisAttributes &Graph1D::getYAxisAttributes() const
    {
      return m_yAxisAttributes;
    }

    //-------------------------------------------------------------------------------------------------

    bool Graph1D::isUpToDate() const
    {
      return m_updateCache.none();
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::fromJson(const Json::Value &value)
    {
      m_title = value.get("title", m_title).asString();

      // axis, marker, line and fill attributes
      Json::Value xAxis = value.get("xaxis", Json::Value());
      Json::Value yAxis = value.get("yaxis", Json::Value());
      Json::Value marker = value.get("marker", Json::Value());
      Json::Value line = value.get("line", Json::Value());

      if(!xAxis.empty())
        m_xAxisAttributes.fromJson(xAxis);

      if(!yAxis.empty())
        m_yAxisAttributes.fromJson(yAxis);

      if(!marker.empty())
        m_markerAttributes.fromJson(marker);

      if(!line.empty())
        m_lineAttributes.fromJson(line);

      const std::string readMode(value.get("mode", "full").asString());
      Json::Value pointsValue = value.get("points", Json::Value());

      for(unsigned int p=0 ; p<pointsValue.size() ; p++)
      {
        Point point;
        Json::Value pointValue(pointsValue[p]);

        point.m_x = pointValue[0].asFloat();
        point.m_y = pointValue[1].asFloat();
        point.m_xErrLow = pointValue[2].asFloat();
        point.m_xErrUp = pointValue[3].asFloat();
        point.m_yErrLow = pointValue[4].asFloat();
        point.m_yErrUp = pointValue[5].asFloat();

        this->addPoint(point);
      }

      m_updateCache.reset();
    }

    //-------------------------------------------------------------------------------------------------

    void Graph1D::toJson(Json::Value &value, bool full, bool resetCache)
    {
      value["mode"] = full ? "full" : "update";

      if(full || m_updateCache.test(TITLE))
        value["title"] = m_title;

      if(full)
      {
        value["min"] = m_minimum;
        value["max"] = m_maximum;
      }

      if(full || m_updateCache.test(AXIS_X))
      {
        Json::Value axis;
        m_xAxisAttributes.toJson(axis);
        value["xaxis"] = axis;
      }

      if(full || m_updateCache.test(AXIS_Y))
      {
        Json::Value axis;
        m_yAxisAttributes.toJson(axis);
        value["yaxis"] = axis;
      }

      if(full || m_updateCache.test(MARKER))
      {
        Json::Value marker;
        m_markerAttributes.toJson(marker);
        value["marker"] = marker;
      }

      if(full || m_updateCache.test(LINE))
      {
        Json::Value line;
        m_lineAttributes.toJson(line);
        value["line"] = line;
      }

      if(full || m_updateCache.test(POINTS))
      {
        Json::Value pointsValue(Json::arrayValue);
        unsigned int index(0);

        for(auto &p : m_points)
        {
          Json::Value pointValue(Json::arrayValue);
          pointValue[0] = p.m_x;
          pointValue[1] = p.m_y;
          pointValue[2] = p.m_xErrLow;
          pointValue[3] = p.m_xErrUp;
          pointValue[4] = p.m_yErrLow;
          pointValue[5] = p.m_yErrUp;

          pointsValue[index] = pointValue;
          index++;
        }

        value["points"] = pointsValue;
      }

      if(resetCache)
        m_updateCache.reset();
    }

    //-------------------------------------------------------------------------------------------------

    MonitorObjectType Graph1D::getType() const
    {
      return GRAPH_1D;
    }

  }

}
