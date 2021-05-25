#include "surface.h"

namespace engine {
	std::vector<glm::u8vec2> quad_vertexes = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};

	Array quad_array;
	ArrayBuffer quad_vertex_array;

	Material* texture_material;
	Material* mstexture_material;


	void QuadRenderer::init() {
		quad_array._new();
		quad_vertex_array._new();

		quad_array.set_attribute(0, quad_vertex_array, Type::uint8, 2);

		quad_vertex_array.set_data(quad_vertexes.size(), quad_vertexes.data(), BufferType::Static);

		texture_material = new Material("sprite"s);
		mstexture_material = new Material("multisample_sprite"s);
	}

	void QuadRenderer::deinit() {
		quad_array._delete();
		quad_vertex_array._delete();

		delete texture_material;
		delete mstexture_material;
	}

	void QuadRenderer::draw() {
		quad_array.draw(DrawType::Strip, 4);
	}

	void SurfaceBase::resize(const glm::uvec2& size) {
		this->size = size;
	}

	void SurfaceBase::clear() {
		frame.use_cleared();
	}

	void SurfaceBase::use() {
		frame.use();
		set_viewport({ 0, 0 }, size);
	}

	const glm::uvec2 SurfaceBase::get_size() {
		return size;
	}

	void SurfaceBase::draw(TextureBuffer& texture, const glm::vec2& position, const glm::vec2& scale, float rotation) {
		frame.use();

		texture_material->use();
		texture_material->set("pos", position);
		texture_material->set("scale", scale);
		texture_material->set("rot", rotation);
		texture_material->set("surface_size", get_size());

		texture.use(0);
		mstexture_material->set("texture_size", texture.get_size());

		QuadRenderer::draw();
	}

	void SurfaceBase::draw(MSTextureBuffer& texture, const glm::vec2& position, const glm::vec2& scale, float rotation) {
		frame.use();

		mstexture_material->use();
		mstexture_material->set("pos", position);
		mstexture_material->set("scale", scale);
		mstexture_material->set("rot", rotation);
		mstexture_material->set("surface_size", get_size());

		texture.use(0);
		mstexture_material->set("texture_size", texture.get_size());
		mstexture_material->set("texture_samples", texture.get_samples());

		QuadRenderer::draw();
	}
	
	Surface::Surface(const glm::uvec2& size) : texture(size) {
		frame.set_attachment(texture, 0); 
	}

	void Surface::resize(const glm::uvec2& size) {
		SurfaceBase::resize(size);
		texture.resize(size);
	}
	
	Surface3D::Surface3D(const glm::uvec2& size, glm::uint32 samples) : texture(size, samples), depth(size, samples) {
		frame.set_attachment(texture, 0);
		frame.set_attachment(depth);
	}

	void Surface3D::resize(const glm::uvec2& size, glm::uint32 samples) {
		SurfaceBase::resize(size);
		texture.resize(size, samples);
		depth.resize(size, samples);
	}
}