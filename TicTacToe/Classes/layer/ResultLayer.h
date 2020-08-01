#pragma once

#include "BaseLayer.h"
#include "Definitions.h"

class ResultLayer : public BaseLayer
{
public:

	static ResultLayer* createResultLayer(E_RESULT i_result);

    virtual bool init(E_RESULT i_result);
    
    void menuCloseCallback(cocos2d::Ref* i_pSender);
    
  //  CREATE_FUNC(ResultLayer);
};

