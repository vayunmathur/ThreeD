#include "EntityComponent.h"
#include "Engine/GraphicsEngine/GraphicsEngine.h"
#include "Engine/GraphicsEngine/DeviceContext.h"

EntityComponent::EntityComponent(vertex* vertex_list, UINT size_list, unsigned int* index_list, UINT size_index_list, void* shader_byte_code, size_t size_shader, Scene* scene)
	:Component(scene)
{
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);
	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	m_mat.setIdentity();
}

EntityComponent::~EntityComponent()
{
}

void EntityComponent::update()
{
}

void EntityComponent::input()
{
}

void EntityComponent::render()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}
