//=============================================================================================================
/**
* @file     computematerial.cpp
*
* @brief    ComputeMaterial class definition.
*
*/


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "computematerial.h"
#include <iostream>

//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QByteArray>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <Qt3DCore/QBuffer>
#include <Qt3DRender/QGraphicsApiFilter>

//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace COMPUTESHADER;
using namespace Qt3DRender;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE GLOBAL METHODS
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

ComputeMaterial::ComputeMaterial(Qt3DCore::QNode *parent)
: QMaterial(parent)
    // , m_fParticleStep(0.4f)
    // , m_fFinalCollisonFactor(0.2f)
    // , m_iParticleCount(0)
    , m_pEffect(new QEffect)
    , m_pParticleStepParameter(new QParameter(QStringLiteral("particleStep"), m_fParticleStep.value()))
    , m_pCollisionParameter(new QParameter(QStringLiteral("finalCollisionFactor"), m_fFinalCollisonFactor.value()))
    , m_pParticleCountParameter(new QParameter(QStringLiteral("particleCount"), m_iParticleCount.value()))
    , m_pComputeShader(new QShaderProgram)
    , m_pComputeRenderPass(new QRenderPass)
    , m_pParticlesParameter(new QParameter)
    , m_pComputeFilterKey(new QFilterKey)
    , m_pComputeTechnique(new QTechnique)
    , m_pDrawShader(new QShaderProgram)
    , m_pDrawRenderPass(new QRenderPass)
    , m_pDrawFilterKey(new QFilterKey)
    , m_pDrawTechnique(new QTechnique)
{
    this->init();

    connect(this, &ComputeMaterial::particleStepChanged, this, [this]() {
        m_pParticleStepParameter->setValue(m_fParticleStep.value());
    });

    connect(this, &ComputeMaterial::finalCollisionFactorChanged, this, [this]() {
        m_pCollisionParameter->setValue(m_fFinalCollisonFactor.value());
    });

    connect(this, &ComputeMaterial::particleCountChanged, this, [this]() {
        m_pParticleCountParameter->setValue(m_iParticleCount.value());
    });
}


//*************************************************************************************************************

void ComputeMaterial::setVertexBuffer(Qt3DCore::QBuffer *inBuffer, uint particleCount)
{
    m_pParticlesParameter->setName(QStringLiteral("Particles"));
    
    //Set the buffer as parameter data
    m_pParticlesParameter->setValue(QVariant::fromValue(inBuffer));
    m_pComputeRenderPass->addParameter(m_pParticlesParameter);


    m_iParticleCount = particleCount;
    // m_pParticleCountParameter->setValue(particleCount);
    m_pComputeRenderPass->addParameter(m_pParticleCountParameter);
}



//*************************************************************************************************************

void ComputeMaterial::init()
{
    //Compute part
    //Set shader
    m_pComputeShader->setComputeShaderCode(QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shader/particles.comp"))));
    m_pComputeRenderPass->setShaderProgram(m_pComputeShader);

    //Set OpenGL version
    m_pComputeTechnique->graphicsApiFilter()->setApi(QGraphicsApiFilter::RHI);
    m_pComputeTechnique->graphicsApiFilter()->setMajorVersion(1);
    m_pComputeTechnique->graphicsApiFilter()->setMinorVersion(0);
    m_pComputeTechnique->graphicsApiFilter()->setProfile(QGraphicsApiFilter::NoProfile);

    //Set filter Keys
    m_pComputeFilterKey->setName(QStringLiteral("type"));
    m_pComputeFilterKey->setValue(QStringLiteral("compute"));

    //Add to technique
    m_pComputeTechnique->addFilterKey(m_pComputeFilterKey);
    m_pComputeTechnique->addRenderPass(m_pComputeRenderPass);

    //Draw part
    //Set shader
    m_pDrawShader->setVertexShaderCode(QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shader/particles.vert"))));
    m_pDrawShader->setFragmentShaderCode(QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shader/particles.frag"))));

    m_pDrawRenderPass->setShaderProgram(m_pDrawShader);

    //Set OpenGL version
    m_pDrawTechnique->graphicsApiFilter()->setApi(QGraphicsApiFilter::RHI);
    m_pDrawTechnique->graphicsApiFilter()->setMajorVersion(1);
    m_pDrawTechnique->graphicsApiFilter()->setMinorVersion(0);
    m_pDrawTechnique->graphicsApiFilter()->setProfile(QGraphicsApiFilter::NoProfile);

    //Set filter Keys
    m_pDrawFilterKey->setName(QStringLiteral("type"));
    m_pDrawFilterKey->setValue(QStringLiteral("draw"));

    //Add to technique
    m_pDrawTechnique->addFilterKey(m_pDrawFilterKey);
    m_pDrawTechnique->addRenderPass(m_pDrawRenderPass);

    //Effect
    //Link shader and uniforms
    m_pEffect->addTechnique(m_pComputeTechnique);
    m_pEffect->addTechnique(m_pDrawTechnique);

    //Add to material
    this->addParameter(m_pParticleStepParameter);
    this->addParameter(m_pCollisionParameter);

    this->setEffect(m_pEffect);
}


//*************************************************************************************************************
