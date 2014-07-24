//
//  ConfigHelper.h
//  coastline
//
//  Created by 荣徽 贺 on 14-7-22.
//
//

#ifndef __coastline__ConfigHelper__
#define __coastline__ConfigHelper__

#include <iostream>
//#include "cocos-ext.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

class PortConfigHelper
{
public:
    PortConfigHelper();
    ~PortConfigHelper();
    XMLError Init(const std::string& FilePath);
    const char* GetPortNameByCoord(const std::string& strCoordString);
    const char* GetPortImgStrByCoord(const std::string& strCoordString);
    const char* GetPortIntroByCoord(const std::string& strCoordString);
    //const char* GetFirstChildByText(const std::string& strParentText);
    //const char* GetChildByText(const std::string& strParentText, const std::string& strChildText);
    //const char* GetSiblingNodeByText(const std::string& strParentText);

private:
    std::string _m_ConfFilePath;
    XMLDocument* _m_Document;
};

#endif /* defined(__coastline__ConfigHelper__) */
