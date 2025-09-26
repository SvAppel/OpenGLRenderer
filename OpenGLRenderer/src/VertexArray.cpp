#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "TriangleRenderer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const std::vector<VertexBufferElement> elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++) 
	{
		const VertexBufferElement& element = elements[i];
		glEnableVertexAttribArray(i);
		//This connects the vertex attributes (here the vertex positions) of the currently bound VBO to the currently bound VAO
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
