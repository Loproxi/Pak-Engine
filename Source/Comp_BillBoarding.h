#ifndef __COMP_BILLBOARDING_H__
#define __COMP_BILLBOARDING_H__

#include "Component.h"
#include "MathGeoLib/include/Math/MathAll.h"

enum BILLBOARDTYPE
{
    NO_ALIGN,
    SCREENALIGN,
    WORLDALIGN,
    AXISALIGN,
};

class Application;

class Comp_BillBoarding :
    public Component
{
public:

    Comp_BillBoarding(GameObject* go);

    ~Comp_BillBoarding();

    void Update() override;

    void OnUIController() override;

    void ScreenAlignBBoard();

    void WorldAlignBBoard();

    void AxisAlignBBoard();

private:


    BILLBOARDTYPE typeofBBoard;

    std::string BBtype[4] = { "Screen Align","World Align","Axis Align","No Align"};

    Application* app;

    bool staticYAxisBillboard;

    float3 zBBoardAxis;
    float3 yBBoardAxis;
    float3 xBBoardAxis;


};

#endif // !__COMP_BILLBOARDING_H__
