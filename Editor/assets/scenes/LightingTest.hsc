Scene: Scene Name
Environment:
  AssetPath: assets\env\birchwood_4k.hdr
  Light:
    Direction: [-0.788999975, 0.777999997, -0.782999992]
    Radiance: [1, 0.999989986, 0.999989986]
    Multiplier: 0.651000023
Entities:
  - Entity: 6605693014656896610
    TagComponent:
      Tag: Sky Light
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [1, 0, 0, 0]
      Scale: [1, 1, 1]
    SkyLightComponent:
      EnvironmentAssetPath: assets\env\birchwood_4k.hdr
      Intensity: 1
      Angle: 0
  - Entity: 3370882484222092056
    TagComponent:
      Tag: Directional Light
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [0.716385961, 0.690598726, 0.0715050101, -0.0689316615]
      Scale: [0.99999541, 0.999995649, 0.999997437]
    DirectionalLightComponent:
      Radiance: [1, 1, 1]
      CastShadows: true
      SoftShadows: true
      LightSize: 0.5
  - Entity: 11293686930003950360
    TagComponent:
      Tag: Scene
    TransformComponent:
      Position: [0, 0, 0]
      Rotation: [1, 8.88205631e-16, 2.98023224e-08, -2.64705906e-23]
      Scale: [9.14999962, 9.14999962, 9.14999962]
    MeshComponent:
      AssetPath: assets\meshes\CubeScene.fbx
  - Entity: 7475399290764333888
    TagComponent:
      Tag: Sphere
    TransformComponent:
      Position: [-1.3215456, 3.63098383, -5.82201385]
      Rotation: [1, 0, 0, 0]
      Scale: [2.6935997, 2.6935997, 2.6935997]
    MeshComponent:
      AssetPath: assets\meshes\Sphere1m.fbx