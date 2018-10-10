/*
 * Copyright (c) 2018 Isetta
 */
#include "Custom/ExampleLevel.h"
#include "Core/Color.h"
#include "Core/Config/Config.h"
#include "Core/Math/Vector3.h"
#include "ExampleComponent.h"
#include "Graphics/AnimationComponent.h"
#include "Graphics/CameraComponent.h"
#include "Graphics/LightComponent.h"
#include "Graphics/MeshComponent.h"
#include "Scene/Entity.h"

namespace Isetta {

using LightProperties = LightComponent::LightProperties;
using CameraProperties = CameraComponent::CameraProperties;

void ExampleLevel::LoadLevel() {
  Entity* pushEntity{AddEntity("PushAnim")};
  MeshComponent* pushMesh =
      pushEntity->AddComponent<MeshComponent>(true, "push/Pushing.scene.xml");
  pushEntity->SetTransform(Math::Vector3{-200, -100, 0},
                           Math::Vector3{0, 90, 0}, Math::Vector3::one);
  AnimationComponent* ani =
      pushEntity->AddComponent<AnimationComponent>(true, pushMesh);
  ani->AddAnimation("push/Pushing.anim", 0, "", false);

  Entity* lightEntity{AddEntity("Light")};
  LightComponent* lightComp = lightEntity->AddComponent<LightComponent>(
      true, "materials/light.material.xml", "LIGHT_1");
  lightEntity->SetTransform(Math::Vector3{0, 200, 600}, Math::Vector3::zero,
                            Math::Vector3::one);
  lightComp->SetProperties<LightProperties::LIGHT_RADIUS>(2500);
  lightComp->SetProperties<LightProperties::FIELD_OF_VIEW>(180);
  lightComp->SetProperties<LightProperties::COLOR>(Color::white);
  lightComp->SetProperties<LightProperties::COLOR_MULTIPLIER>(1.0f);
  lightComp->SetProperties<LightProperties::SHADOW_MAP_COUNT>(1);
  lightComp->SetProperties<LightProperties::SHADOW_MAP_BIAS>(0.01f);

  Entity* cameraEntity{AddEntity("Camera")};
  CameraComponent* camComp =
      cameraEntity->AddComponent<CameraComponent>(true, "Camera");
  cameraEntity->SetTransform(Math::Vector3{0, 50, 600}, Math::Vector3::zero,
                             Math::Vector3::one);
  camComp->SetProperties<CameraProperties::FIELD_OF_VIEW>(
      Config::Instance().renderConfig.fieldOfView.GetVal());
  camComp->SetProperties<CameraProperties::NEAR_CLIPPING_PLANE>(
      Config::Instance().renderConfig.nearClippingPlane.GetVal());
  camComp->SetProperties<CameraProperties::FAR_CLIPPING_PLANE>(
      Config::Instance().renderConfig.farClippingPlane.GetVal());

  Entity* customEntity{AddEntity("custom")};
  ExampleComponent* customComponent =
      customEntity->AddComponent<ExampleComponent>(true);
}
}  // namespace Isetta