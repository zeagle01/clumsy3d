
module;

#include "glad/glad.h"

#include <iostream>
#include <array>
#include <memory>

module clumsy.render;

import :shader;
import :vertex_array;

namespace clumsy
{

	class renderer::imp
	{
	public:

		void init(void* window, void* proc_addr)
		{
			set_window(window);
			setup_proc_address(proc_addr);

			compile_shader();
			create_vertex_array();
		}

		void clear_screen()
		{
			glClearColor(0.3, 0.2, 0.1, 1.);//default color;
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void add_triangles(const float* x, const int* triangles, int vNum, int tNum, float* vp)
		{
			add_triangles(x, triangles, vNum, tNum, vp, { 1,0,0 });
		}

		void add_triangles(const float* x, const int* triangles, int vNum, int tNum, float* vp, const std::array<float, 3>& color)
		{

			m_vertex_array->bind();
			m_vertex_array->set_index_buffer(triangles, tNum * 3);
			m_vertex_array->set_vertex_attribute_data(m_attribute_name_position, x, vNum);

			std::array<float, 16> identity
			{
				1.f,0.f,0.f,0.f,
				0.f,1.f,0.f,0.f,
				0.f,0.f,1.f,0.f,
				0.f,0.f,0.f,1.f
			};

			m_shader->bind();
			m_shader->upload_uniform_mat4("u_view_projection", vp);
			m_shader->upload_uniform_mat4("u_model_matrix", identity.data());

			bool m_is_enable_fill = true;
			if (m_is_enable_fill)
			{
				set_polygon_mode(false);
				m_shader->upload_uniform_vec3("u_obj_color", color);
				draw_iendxes(GL_TRIANGLES);
			}

			bool m_is_enable_wireframe = true;
			if (m_is_enable_wireframe)
			{
				set_polygon_mode(true);
				m_shader->upload_uniform_vec3("u_obj_color", { 0,1,0 });
				draw_iendxes(GL_TRIANGLES);
			}

		}

	private:
		void compile_shader()
		{
			//glEnable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			auto src =
				R"(
				#shader_type vertex
				#version 330 core

				layout(location = 0) in vec3 v_position;
				layout(location = 1) in vec3 v_normal;

				uniform mat4 u_view_projection;

				out vec3 frag_normal;
				out vec3 frag_position;

				void main()
				{
					gl_Position = u_view_projection * vec4(v_position, 1.0);
					frag_normal = v_normal;
					//frag_position=v_position;
				}



				//-------------------------------
				#shader_type fragment
				#version 330 core

				in vec3 frag_normal;
				in vec3 frag_position;

				uniform vec3 u_eye_pos;
				uniform vec3 u_light_pos;
				uniform vec3 u_obj_color;
				uniform vec3 u_light_color;
				uniform float u_ka;
				uniform float u_ks;
				uniform float u_kd;
				uniform float u_specular_steep;

				out vec4 color;

				void main()
				{
					//ambient
					vec3 ambient_color = u_ka * u_light_color * u_obj_color;

					//diffuse
					vec3 light_dir = normalize(u_light_color - frag_position);
					float diffuse = max(dot(frag_normal, light_dir), 0.);
					vec3 diffuse_color = u_kd * diffuse * u_light_color * u_obj_color;

					//specular
					vec3 eye_dir = normalize(u_eye_pos - frag_position);
					vec3 specular_dir = normalize(light_dir + eye_dir);
					float specular = pow(max(dot(specular_dir, frag_normal), 0), u_specular_steep);
					vec3 specular_color = u_ks * specular * u_light_color * u_obj_color;

					color = vec4(ambient_color + diffuse_color + specular_color, 1.0);
				}
			)";


			m_shader = std::make_unique<shader>();

			m_shader->read_shader_src("clumsy_shader", src);

			m_shader->bind();
			m_shader->upload_uniform_vec3("u_light_pos", { 10.f, 10.f, 10.f });
			m_shader->upload_uniform_vec3("u_obj_color", { 1,0,0 });
			m_shader->upload_uniform_vec3("u_eye_pos", { 0.f,0.f,0.f });
			m_shader->upload_uniform_vec3("u_light_color", { 1.f, 1.f, 1.f });
			m_shader->upload_uniform_float("u_ka", 0.3f);
			m_shader->upload_uniform_float("u_ks", 0.5f);
			m_shader->upload_uniform_float("u_kd", 0.5f);
			m_shader->upload_uniform_float("u_specular_steep", 40.f);
		}

		void create_vertex_array()
		{
			m_vertex_array = std::make_unique<vertex_array>();

			m_vertex_array->add_vertex_attribute(shader_type_enum::Float3, m_attribute_name_position);
		}

		void set_window(void* window)
		{
			m_window = window;
		}

		void setup_proc_address(void* proc_addr)
		{
			if (!gladLoadGLLoader((GLADloadproc)proc_addr))
			{
				printf("glad load failed\n");
			}
			else
			{
				printf("glad load succend\n");
			}
			printf("gl version %s\n", glGetString(GL_VERSION));
		}
	private:
		void draw_iendxes(int mode)
		{
			glDrawElements(mode, m_vertex_array->get_index_count(), GL_UNSIGNED_INT, nullptr);
		}

		void set_polygon_mode(bool v)
		{
			if (v)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
	private:
		void* m_window;
	private:
		std::unique_ptr<shader>			m_shader;
		std::unique_ptr<vertex_array>	m_vertex_array;
		const std::string m_attribute_name_position = "v_position";
	};

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	renderer::renderer() : m_imp(std::make_unique<imp>()) { }
	renderer::~renderer() = default;

	void renderer::init(void* window, void* proc_addr)
	{
		m_imp->init(window, proc_addr);
	}

	void renderer::clear_screen()
	{
		m_imp->clear_screen();
	}

	void renderer::add_triangles(const float* x, const int* triangles, int vNum, int tNum, float* vp)
	{
		m_imp->add_triangles(x, triangles, vNum, tNum, vp);
	}

	void renderer::add_triangles(const float* x, const int* triangles, int vNum, int tNum,float* vp, const std::array<float, 3>& color)
	{
		m_imp->add_triangles(x, triangles, vNum, tNum, vp, color);
	}

}
