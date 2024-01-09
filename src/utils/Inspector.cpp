// #include "Inspector.h"
// #include <imgui.h>

// namespace RavenEngine {

// void Inspector::Draw(SceneNode* selectedNode) {
//     if (!selectedNode) return;

//     ImGui::Begin("Inspector");

//     if (auto* transform = selectedNode->GetComponent<TransformComponent>()) {
//         DrawTransformComponent(transform);
//     }

//     // Draw other components or properties

//     ImGui::End();
// }

// void Inspector::DrawTransformComponent(TransformComponent* transform) {
//     // Use ImGui to draw and manipulate transform properties
//     // Example: ImGui::DragFloat3("Position", transform->GetPositionPtr());
// }

// } // namespace RavenEngine
