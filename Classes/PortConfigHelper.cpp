//
//  ConfigHelper.cpp
//  coastline
//
//  Created by 荣徽 贺 on 14-7-22.
//
//
#include "cocos2d.h"
#include "PortConfigHelper.h"
USING_NS_CC;

PortConfigHelper::PortConfigHelper()
{
    _m_Document = new tinyxml2::XMLDocument();
}

PortConfigHelper::~PortConfigHelper()
{
    delete _m_Document;
}

XMLError PortConfigHelper::Init(const std::string &strFilePath)
{
    XMLError ret;
    _m_ConfFilePath.clear();
    _m_ConfFilePath = strFilePath;
    ret = _m_Document->LoadFile(_m_ConfFilePath.c_str());
    if(ret > 0){
        _m_ConfFilePath.clear();
    }
    return ret;
}

const char* PortConfigHelper::GetPortNameByCoord(const std::string& strCoordString)
{
    //Check if initialized
    if(_m_ConfFilePath.empty()){
        return NULL;
    }

    XMLElement* root_element = _m_Document->RootElement();
    XMLElement* coord_element;
    XMLElement* port_name_element;
    
    //Find first node of the parent
    if(root_element){
        coord_element = root_element->FirstChildElement(strCoordString.c_str());
        if(coord_element){
            port_name_element = coord_element->FirstChildElement("PortName");
            if(port_name_element){
                return port_name_element->GetText();
            }
        }
    }
    return NULL;
}

const char* PortConfigHelper::GetPortImgStrByCoord(const std::string& strCoordString)
{
    //Check if initialized
    if(_m_ConfFilePath.empty()){
        return NULL;
    }

    XMLElement* root_element = _m_Document->RootElement();
    XMLElement* coord_element;
    XMLElement* port_name_element;
    
    //Find first node of the parent
    if(root_element){
        coord_element = root_element->FirstChildElement(strCoordString.c_str());
        if(coord_element){
            port_name_element = coord_element->FirstChildElement("PortImg");
            if(port_name_element){
                return port_name_element->GetText();
            }
        }
    }
    return NULL;
}

const char* PortConfigHelper::GetPortIntroByCoord(const std::string& strCoordString)
{
    //Check if initialized
    if(_m_ConfFilePath.empty()){
        return NULL;
    }

    XMLElement* root_element = _m_Document->RootElement();
    XMLElement* coord_element;
    XMLElement* port_name_element;
    
    //Find first node of the parent
    if(root_element){
        coord_element = root_element->FirstChildElement(strCoordString.c_str());
        if(coord_element){
            port_name_element = coord_element->FirstChildElement("PortIntro");
            if(port_name_element){
                return port_name_element->GetText();
            }
        }
    }
    return NULL;
}



