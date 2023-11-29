//=============================================================================================================
/**
* @file     computematerial.h
* @author   Lars Debor <lars.debor@tu-ilmenau.de>;
*
* @brief     ComputeMaterial class declaration.
*
*/

#ifndef COMPUTESHADER_COMPUTEMATERIAL_H
#define COMPUTESHADER_COMPUTEMATERIAL_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <Qt3DCore>
#include <Qt3DRender/QMaterial>
#include <QQmlEngine>


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

namespace Qt3DRender {
    class QEffect;
    class QParameter;
    class QShaderProgram;
    class QFilterKey;
    class QTechnique;
    class QRenderPass;
    class QBuffer;
}

namespace QtCore {
    class QByteArray;
}


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE COMPUTESHADER
//=============================================================================================================

namespace COMPUTESHADER {


//*************************************************************************************************************
//=============================================================================================================
// COMPUTESHADER FORWARD DECLARATIONS
//=============================================================================================================


//=============================================================================================================
/**
* This class is special material for compute shader use.
*
* @brief Compute shader material.
*/

class ComputeMaterial : public Qt3DRender::QMaterial
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(float particleStep READ particleStep WRITE setParticleStep BINDABLE bindableParticleStep)
    Q_PROPERTY(float finalCollisionFactor READ finalCollisionFactor WRITE setFinalCollisionFactor BINDABLE bindableFinalCollisionFactor)
    Q_PROPERTY(int particleCount READ particleCount WRITE setParticleCount BINDABLE bindableParticleCount)


public:
    //=========================================================================================================
    /**
    * Constructs a ComputeMaterial object.
    */
    explicit ComputeMaterial(Qt3DCore::QNode *parent = 0);
    
    //=========================================================================================================
    /**
     * Set the vertex buffer that is used with the name Particles in shaders
     *
     * @param inBuffer
     */
    void setVertexBuffer(Qt3DCore::QBuffer *inBuffer, uint particleCount);

    float particleStep() const { return m_fParticleStep.value(); }
    void setParticleStep(float step) { m_fParticleStep = step; }
    QBindable<float> bindableParticleStep() { return &m_fParticleStep; }

    float finalCollisionFactor() const { return m_fFinalCollisonFactor.value(); }
    void setFinalCollisionFactor(float factor) { m_fFinalCollisonFactor = factor; }
    QBindable<float> bindableFinalCollisionFactor() { return &m_fFinalCollisonFactor; }

    int particleCount() const { return m_iParticleCount.value(); }
    void setParticleCount(int count) { m_iParticleCount = count; }
    QBindable<int> bindableParticleCount() { return &m_iParticleCount; }

signals:
    void particleStepChanged();
    void finalCollisionFactorChanged();
    void particleCountChanged();

protected:


private:
    //=========================================================================================================
    /**
     * Init the ComputeMaterial class
     */
    void init();

    QByteArray buildShaderStorage();

    //declare bindable property for float m_fParticleStep
    // float m_fParticleStep;
    // float m_fFinalCollisonFactor;
    // int m_iParticleCount;

    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(ComputeMaterial, float, m_fParticleStep, 0.4f, &ComputeMaterial::particleStepChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(ComputeMaterial, float, m_fFinalCollisonFactor, 0.2f, &ComputeMaterial::finalCollisionFactorChanged)
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(ComputeMaterial, int, m_iParticleCount, 0, &ComputeMaterial::particleCountChanged)

    QPointer<Qt3DRender::QEffect> m_pEffect;

    QPointer<Qt3DRender::QParameter> m_pParticleStepParameter;
    QPointer<Qt3DRender::QParameter> m_pCollisionParameter;
    QPointer<Qt3DRender::QParameter> m_pParticleCountParameter;

    //Compute Part
    QPointer<Qt3DRender::QShaderProgram> m_pComputeShader;
    QPointer<Qt3DRender::QRenderPass> m_pComputeRenderPass;
    QPointer<Qt3DRender::QParameter> m_pParticlesParameter;
    QPointer<Qt3DRender::QFilterKey> m_pComputeFilterKey;
    QPointer<Qt3DRender::QTechnique> m_pComputeTechnique;

    //Draw Part
    QPointer<Qt3DRender::QShaderProgram> m_pDrawShader;
    QPointer<Qt3DRender::QRenderPass> m_pDrawRenderPass;
    QPointer<Qt3DRender::QFilterKey> m_pDrawFilterKey;
    QPointer<Qt3DRender::QTechnique> m_pDrawTechnique;

};


//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================


} // namespace COMPUTESHADER

#endif // COMPUTESHADER_COMPUTEMATERIAL_H
