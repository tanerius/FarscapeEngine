#pragma once

#include <glm/glm.hpp>

namespace Farscape {

	enum class EMatrixType : unsigned short
	{
		E_Projection = 0,
		E_View,
		E_ViewProjection
	};

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		void SetPosition(const glm::vec3& position);
		void SetRotation(const float rotation);

		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		const glm::mat4& GetMatrix(EMatrixType type) const; 
		void UpdateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}
