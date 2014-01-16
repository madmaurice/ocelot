#define BT_NO_SIMD_OPERATOR_OVERLOADS

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "gtest/gtest.h"

#if 0
class BulletBoxApp : public Application
{
public:
    BulletBoxApp(HINSTANCE h_Inst);
    virtual ~BulletBoxApp();

    virtual bool init();

private:
    virtual void update(float dt);

    void render();

    XMFLOAT4X4 m_view;

    std::vector<std::unique_ptr<Box> > m_boxes;
    std::unique_ptr<Ground> m_ground;
    std::unique_ptr<ColorEffect> m_effect;
    PhysicSystem m_physic;
};

BulletBoxApp::BulletBoxApp(HINSTANCE h_Inst) 
    : Application(h_Inst, "BulletBox")
    , m_effect(nullptr)
{
    XMMATRIX I = XMMatrixTranslation(0,0, -5);
    XMStoreFloat4x4(&m_view, I);

    m_boxes.resize(50);
}

BulletBoxApp::~BulletBoxApp()
{
}

bool BulletBoxApp::init()
{
    if(!Application::init())
        return false;

    m_physic.init();

    m_renderer.setIAPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_effect.reset(new ColorEffect(m_renderer));

    int i=0;
    for (auto& box : m_boxes)
    {
        box.reset(new Box(2, XMVectorSet(0, 10+(5*i), -10+i, 0)));
        box->getRenderComponent().createBuffer(m_renderer);
        m_physic.addObject(&box->getPhysicComponent());
        ++i;
    }

    m_ground.reset(new Ground(100, XMVectorSet(0, 0, 0, 0)));
    m_ground->getRenderComponent().createBuffer(m_renderer);

    m_physic.addObject(&m_ground->getPhysicComponent());

    return true;
}

void BulletBoxApp::update(float dt)
{
    m_physic.update(m_timer.DeltaTime());

    for (auto& box : m_boxes)
    {
        box->update();
    }
    m_ground->update();

    render();
}

void BulletBoxApp::render()
{
    m_renderer.clear(oc::Colors::Silver);

    XMVECTOR pos     = XMVectorSet(0.0f, 5.0f, -40.0f, 0.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up     = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX world;
    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
    XMMATRIX proj = m_renderer.getProjection();

    for (auto& box : m_boxes)
    {
        RenderComponent& rc = box->getRenderComponent();
        world = XMLoadFloat4x4(&rc.getTransform());

        m_effect->setWorldViewProj(world*view*proj);
        m_effect->apply(m_renderer);
        m_renderer.draw(rc);
    }

    RenderComponent& rcGround = m_ground->getRenderComponent();
    world = XMLoadFloat4x4(&rcGround.getTransform());

    m_effect->setWorldViewProj(world*view*proj);
    m_effect->apply(m_renderer);
    m_renderer.draw(rcGround);

    const XMFLOAT4X4& dbgWorld = rcGround.getTransform();
    std::stringstream sstream;
    sstream << "render ground height : " << dbgWorld(3,1) << std::endl;
    OutputDebugString(sstream.str().c_str());

    m_renderer.present();
}

int WINAPI WinMain(HINSTANCE h_Inst, HINSTANCE h_PrevInst, LPSTR lpcmdline, int ncmdshow)
{
    OC_DBG_CONFIG();

    BulletBoxApp app(h_Inst);

    int ret = app.run();
    app.shutdown();

    return ret;
}
#else

TEST(SimpleTest, aTest) {
    EXPECT_EQ(1, 1);
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    int toto;
    std::cin >> toto;
    return 0;
}
#endif