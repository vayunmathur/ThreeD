#pragma once
#include "Component.h"
#include "Engine/GraphicsEngine/VertexBuffer.h"
#include "Engine/GraphicsEngine/IndexBuffer.h"
#include "Engine/Math/Vector.h"

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

class EntityComponent : public Component
{
public:
	EntityComponent(vertex* vertex_list, UINT size_list, unsigned int* index_list, UINT size_index_list, void* shader_byte_code, size_t size_shader, Scene* scene);
	~EntityComponent();
	mat4 getTransformationMatrix() { return m_mat; }
public:
	// Inherited via Component
	virtual void update() override;
	virtual void input() override;
	virtual void render() override;
private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	mat4 m_mat;
};

