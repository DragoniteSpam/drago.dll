#ifndef __DRAGO_TERRAIN_OP
#define __DRAGO_TERRAIN_OP "1.0.2"

#include "main/core.h"
#include "SpriteOperations/spriteops.h"
#include <cmath>
#include <sstream>
#include <format>

#define DATA_INDEX(x, y, h) ((x) * (h) + (y))

namespace terrainops {
	extern bool save_all;
	extern float save_water_level;
	extern bool save_swap_zup;
	extern bool save_swap_uv;
	extern bool save_centered;
	extern int save_density;
	extern float save_scale;
	extern float save_tex_size;
	extern float save_color_scale;
	extern Vector2 save_start;
	extern float save_smooth_normals;
	extern Vector2 save_end;
	extern unsigned int save_format;
	extern unsigned int* save_texture_map;
	extern unsigned int* save_colour_map;

	extern float* cursor_output;

	extern unsigned int* deform_brush_texture;
	extern Vector3 deform_brush_size;
	extern Vector3 deform_brush_position;
	extern float deform_velocity;
	extern float deform_radius;

	extern float* mutate_noise;
	extern Vector3 mutate_noise_data;
	extern unsigned int* mutate_texture;
	extern Vector3 mutate_texture_data;

	extern float* data;
	extern Vector3 data_size;
	extern float* vertex;
	extern float* vertex_lod;

	extern const int cell_size;
	extern const int lod_reduction;

	const char* version();

	// general
	void set_active_data(float*, int, int);
	void set_active_vertex_data(float*);
	void set_lod_vertex_data(float*);
	void to_heightmap(unsigned int*);
	void from_heightmap(unsigned int*, float);
	float max_height(float*, unsigned int);
	float min_height(float*, unsigned int);

	void set_cursor_location_output(float*);
	void get_intersecting_triangle(float, float, float, float, float, float);

	// deformation
	void flatten(float);
	void apply_scale(float);
	void deform_brush(unsigned int*, float, float);
	void deform_brush_settings(float, float);
	void deform_brush_set_position(float, float);
	// the deformation functions still use the data pointers, because theyre
	// called many times
	void deform_mold(float*, float*, float*, int, int, int, int, float, float, float, int, int);
	void deform_average(float*, float*, float*, int, int, int, int, float, float, float, int, int);
	void deform_zero(float*, float*, float*, int, int, int, int, float, float, float, int, int);

	// mutation
	void mutate_set_noise(float*, int, int, float);
	void mutate_set_texture(unsigned int*, int, int, float);
	void mutate();

	// build vertex data
	void build_settings(bool, bool, bool, bool, int, float, float, float, unsigned int, float, bool);
	void build_texture(unsigned int*);
	void build_vertex_colour(unsigned int*);
	void build_bounds(int, int, int, int);
	void generate_internal(float*);
	void generate_lod_internal(float*);

	void build(float*, std::stringstream*, long long*, int*);
	long long build_obj(float*, unsigned int, float*);
	long long build_d3d(float*, unsigned int, float*);
	long long build_vbuff(float*, unsigned int, float*);

	void build_write_vertex_internal(float*, long long, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float);
	void build_write_vertex_vbuff(float*, long long, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float);
	void build_write_vertex_d3d(std::stringstream, float, float, float, float, float, float, float, float, unsigned int);
	
	// helper functions
	void invoke_deformation(bool, void(float*, float*, float*, int, int, int, int, float, float, float, int, int));

	inline float get_z(float*, int, int, int);
	inline void add_z(float*, float*, float*, int, int, int, int, float, int, int);
	inline void set_z(float*, float*, float*, int, int, int, int, float, int, int);
	inline void get_normal(float*, Vector3*, int, int, int, int, int, int, int, int);
	inline void get_normal_smooth(float*, Vector3*, int, int, int, int, int, int, int);
	inline void get_texcoord(unsigned int*, Vector2*, int, int, int, int, bool);
	inline unsigned int get_colour(unsigned int*, int, int, int, int, float);
	inline unsigned int get_vertex_index(int, int, int, int, int, int);
	inline bool ray_tri(Vector3*, Vector3*, Vector3*, Vector3*, Vector3*);

	inline float get_z(float* data, int x, int y, int h) {
		return data[DATA_INDEX(x, y, h)];
	}

	inline void add_z(float* data, float* vertex, float* lod, int x, int y, int w, int h, float value, int reduction, int cell_size) {
		set_z(data, vertex, lod, x, y, w, h, value + get_z(data, x, y, h), reduction, cell_size);
	}

	inline void set_z(float* data, float* vertex, float* lod, int x, int y, int w, int h, float value, int reduction, int cell_size) {
		data[DATA_INDEX(x, y, h)] = value;

		bool is_corner_vertex = (x % reduction == 0) && (y % reduction == 0);

		if (x > 0 && y > 0) {
			vertex[get_vertex_index(cell_size, x - 1, y - 1, w, h, 2) + 2] = value;
			vertex[get_vertex_index(cell_size, x - 1, y - 1, w, h, 3) + 2] = value;
			if (is_corner_vertex) {
				lod[get_vertex_index(cell_size / reduction, x / reduction - 1, y / reduction - 1, w / reduction, h / reduction, 2) + 2] = value;
				lod[get_vertex_index(cell_size / reduction, x / reduction - 1, y / reduction - 1, w / reduction, h / reduction, 3) + 2] = value;
			}
		}

		if (x < w && y > 0) {
			vertex[get_vertex_index(cell_size, x, y - 1, w, h, 4) + 2] = value;
			if (is_corner_vertex) {
				lod[get_vertex_index(cell_size / reduction, x / reduction, y / reduction - 1, w / reduction, h / reduction, 4) + 2] = value;
			}
		}

		if (x > 0 && y < h - 1) {
			vertex[get_vertex_index(cell_size, x - 1, y, w, h, 1) + 2] = value;
			if (is_corner_vertex) {
				lod[get_vertex_index(cell_size / reduction, x / reduction - 1, y / reduction, w / reduction, h / reduction, 1) + 2] = value;
			}
		}

		if (x < w && y < h - 1) {
			vertex[get_vertex_index(cell_size, x, y, w, h, 0) + 2] = value;
			vertex[get_vertex_index(cell_size, x, y, w, h, 5) + 2] = value;
			if (is_corner_vertex) {
				lod[get_vertex_index(cell_size / reduction, x / reduction, y / reduction, w / reduction, h / reduction, 0) + 2] = value;
				lod[get_vertex_index(cell_size / reduction, x / reduction, y / reduction, w / reduction, h / reduction, 5) + 2] = value;
			}
		}
	}

	inline void get_normal(float* data, Vector3* results, int x1, int y1, int x2, int y2, int x3, int y3, int w, int h) {
		float z1 = get_z(data, std::min(x1, w - 1), std::min(y1, h - 1), h);
		float z2 = get_z(data, std::min(x2, w - 1), std::min(y2, h - 1), h);
		float z3 = get_z(data, std::min(x3, w - 1), std::min(y3, h - 1), h);

		Vector3 e1{ }, e2{ };
		e1.x = (float)(x2 - x1);
		e1.y = (float)(y2 - y1);
		e1.z = (float)(z2 - z1);
		e2.x = (float)(x3 - x1);
		e2.y = (float)(y3 - y1);
		e2.z = (float)(z3 - z1);

		CROSS(*results, e1, e2);
		NORMALIZE(*results);
	}

	inline void append_triangle_normal(float* data, Vector3* results, Triangle triangle, int w, int h) {
		// the abc members of Vector3s are integers, which is occasionally useful
		float z1 = get_z(data, std::min(triangle.a.a, w - 1), std::min(triangle.a.b, h - 1), h);
		float z2 = get_z(data, std::min(triangle.b.a, w - 1), std::min(triangle.b.b, h - 1), h);
		float z3 = get_z(data, std::min(triangle.c.a, w - 1), std::min(triangle.c.b, h - 1), h);

		Vector3 e1{ }, e2{ }, n{ };
		e1.x = triangle.b.a - triangle.a.a;
		e1.y = triangle.b.b - triangle.a.b;
		e1.z = z2 - z1;
		e2.x = triangle.c.a - triangle.a.a;
		e2.y = triangle.c.b - triangle.a.b;
		e2.z = z3 - z1;

		CROSS(n, e1, e2);
		NORMALIZE(n);

		results->x += n.x;
		results->y += n.y;
		results->z += n.z;
	}

	inline void get_normal_smooth(float* data, TerrainCell* results, int x, int y, int corner, int w, int h) {
		Triangle ta{ }, tb{ }, tc{ }, td{ }, te{ }, tf{ }, tg{ }, th{ }, ti{ }, tj{ }, tk{ }, tl{ }, tm{ }, tn{ }, tone{ }, ttwo{ };
		if (x > 0) {
			tn.a.a = x - 1;
			tn.a.b = y;
			tn.b.a = x;
			tn.b.b = y + 1;
			tn.c.a = x - 1;
			tn.c.b = y + 1;

			ta.a.a = x - 1;
			ta.a.b = y;
			ta.b.a = x;
			ta.b.b = y;
			ta.c.a = x;
			ta.c.b = y + 1;
		}

		if (x > 0 && y > 0) {
			tb.a.a = x - 1;
			tb.a.b = y - 1;
			tb.b.a = x;
			tb.b.b = y;
			tb.c.a = x - 1;
			tb.c.b = y;

			tc.a.a = x - 1;
			tc.a.b = y - 1;
			tc.b.a = x;
			tc.b.b = y - 1;
			tc.c.a = x;
			tc.c.b = y;
		}

		if (y > 0) {
			td.a.a = x;
			td.a.b = y - 1;
			td.b.a = x + 1;
			td.b.b = y;
			td.c.a = x;
			td.c.b = y;

			te.a.a = x;
			te.a.b = y - 1;
			te.b.a = x + 1;
			te.b.b = y - 1;
			te.c.a = x + 1;
			te.c.b = y;
		}

		if (x < w - 1 && y > 0) {
			tf.a.a = x + 1;
			tf.a.b = y - 1;
			tf.b.a = x + 2;
			tf.b.b = y;
			tf.c.a = x + 1;
			tf.c.b = y;
		}

		if (x < w - 1) {
			tg.a.a = x + 1;
			tg.a.b = y;
			tg.b.a = x + 2;
			tg.b.b = y;
			tg.c.a = x + 2;
			tg.c.b = y + 1;

			th.a.a = x + 1;
			th.a.b = y;
			th.b.a = x + 2;
			th.b.b = y + 1;
			th.c.a = x + 1;
			th.c.b = y + 1;
		}

		if (x < w - 1 && y < h - 1) {
			ti.a.a = x + 1;
			ti.a.b = y + 1;
			ti.b.a = x + 2;
			ti.b.b = y + 1;
			ti.c.a = x + 2;
			ti.c.b = y + 2;

			tj.a.a = x + 1;
			tj.a.b = y + 1;
			tj.b.a = x + 2;
			tj.b.b = y + 2;
			tj.c.a = x + 1;
			tj.c.b = y + 2;
		}

		if (y < h - 1) {
			tk.a.a = x;
			tk.a.b = y + 1;
			tk.b.a = x + 1;
			tk.b.b = y + 1;
			tk.c.a = x + 1;
			tk.c.b = y + 2;

			tl.a.a = x;
			tl.a.b = y + 1;
			tl.b.a = x + 1;
			tl.b.b = y + 2;
			tl.c.a = x;
			tl.c.b = y + 2;
		}

		if (x > 0 && y < h - 1) {
			tm.a.a = x;
			tm.a.b = y + 2;
			tm.b.a = x - 1;
			tm.b.b = y + 1;
			tm.c.a = x;
			tm.c.b = y + 1;
		}

		tone.a.a = x;
		tone.a.b = y;
		tone.b.a = x + 1;
		tone.b.b = y;
		tone.c.a = x + 1;
		tone.c.b = y + 1;

		ttwo.a.a = x + 1;
		ttwo.a.b = y + 1;
		ttwo.b.a = x;
		ttwo.b.b = y + 1;
		ttwo.c.a = x;
		ttwo.c.b = y;

		// northwest
		if (x > 0) append_triangle_normal(data, &(results->nw), ta, w, h);
		if (x > 0 && y > 0) append_triangle_normal(data, &(results->nw), tb, w, h);
		if (x > 0 && y > 0) append_triangle_normal(data, &(results->nw), tc, w, h);
		if (y > 0) append_triangle_normal(data, &(results->nw), td, w, h);
		append_triangle_normal(data, &(results->nw), tone, w, h);
		append_triangle_normal(data, &(results->nw), ttwo, w, h);

		// northeast
		if (y > 0) append_triangle_normal(data, &(results->ne), td, w, h);
		if (y > 0) append_triangle_normal(data, &(results->ne), te, w, h);
		if (x < w - 1 && y > 0) append_triangle_normal(data, &(results->ne), tf, w, h);
		if (x < w - 1) append_triangle_normal(data, &(results->ne), tg, w, h);
		if (x < w - 1) append_triangle_normal(data, &(results->ne), th, w, h);
		append_triangle_normal(data, &(results->ne), tone, w, h);
		
		// southeast
		if (x < w - 1) append_triangle_normal(data, &(results->se), th, w, h);
		if (x < w - 1 && y < h - 1) append_triangle_normal(data, &(results->se), ti, w, h);
		if (x < w - 1 && y < h - 1) append_triangle_normal(data, &(results->se), tj, w, h);
		if (y < h - 1) append_triangle_normal(data, &(results->se), tk, w, h);
		append_triangle_normal(data, &(results->se), tone, w, h);
		append_triangle_normal(data, &(results->se), ttwo, w, h);
		
		// southwest
		if (y < h - 1) append_triangle_normal(data, &(results->sw), tk, w, h);
		if (y < h - 1) append_triangle_normal(data, &(results->sw), tl, w, h);
		if (x > 0 && y < h - 1) append_triangle_normal(data, &(results->sw), tm, w, h);
		if (x > 0) append_triangle_normal(data, &(results->sw), tn, w, h);
		if (x > 0) append_triangle_normal(data, &(results->sw), ta, w, h);
		append_triangle_normal(data, &(results->sw), ttwo, w, h);

		NORMALIZE(results->nw);
		NORMALIZE(results->ne);
		NORMALIZE(results->se);
		NORMALIZE(results->sw);
	}

	inline void get_texcoord(unsigned int* texture_data, Vector2* results, int x, int y, int w, int h, bool swap_uvs) {
		x = std::min(x, w - 1);
		y = std::min(y, h - 1);

		unsigned int tex = texture_data[GET_INDEX(x + 0, y + 0, h)];

		results->x = (tex & 0xff) / 256.0f;
		results->y = ((tex >> 8) & 0xff) / 256.0f;
		if (swap_uvs)
			results->y = 1.0f - results->y;
	}

	inline unsigned int get_colour(unsigned int* colour_data, int x, int y, int w, int h, float scale) {
		return spriteops::sample_unfiltered(colour_data, (int)(w * scale), (int)(h * scale), ((float)x) / w, ((float)y) / h) | 0xff000000;
	}

	inline unsigned int get_vertex_index(int cell_size, int x, int y, int w, int h, int vertex) {
		int column_size = cell_size * h;
		Vector2 base_chunk{}, local_coordinates{};
		base_chunk.a = x / cell_size;
		base_chunk.b = y / cell_size;
		local_coordinates.a = x % cell_size;
		local_coordinates.b = y % cell_size;
		int local_chunk_width = std::min(cell_size, w - base_chunk.a * cell_size);
		int local_chunk_height = std::min(cell_size, h - base_chunk.b * cell_size);
		int column_address = base_chunk.a * column_size;
		int chunk_address = column_address + base_chunk.b * cell_size /* dont use the local chunk height here */ * local_chunk_width;
		int base_address = chunk_address + local_coordinates.a * local_chunk_height + local_coordinates.b;
		return (base_address * 6 + vertex) * 3;
	}

	inline bool ray_tri(Vector3* start, Vector3* direction, Vector3* a, Vector3* b, Vector3* c) {
		Vector3 edge1{}, edge2{}, tvec{}, pvec{}, qvec{};
		float det, inv_det;

		/* find vectors for two edges sharing vert0 */
		SUB(edge1, (*b), (*a));
		SUB(edge2, (*c), (*a));

		/* begin calculating determinant - also used to calculate U parameter */
		CROSS(pvec, (*direction), edge2);

		/* if determinant is near zero, ray lies in plane of triangle */
		det = DOT(edge1, pvec);

		/* calculate distance from vert0 to ray origin */
		SUB(tvec, (*start), (*a));
		inv_det = 1.0f / det;

		Vector3 out{};

		if (det > 0) {
			/* calculate U parameter and test bounds */
			out.y = DOT(tvec, pvec);
			if (out.y < 0.0 || out.y > det)
				return 0;

			/* prepare to test V parameter */
			CROSS(qvec, tvec, edge1);

			/* calculate V parameter and test bounds */
			out.z = DOT((*direction), qvec);
			if (out.z < 0.0 || out.y + out.z > det)
				return 0;

		} else if (det < 0) {
			/* calculate U parameter and test bounds */
			out.y = DOT(tvec, pvec);
			if (out.y > 0.0 || out.y < det)
				return 0;

			/* prepare to test V parameter */
			CROSS(qvec, tvec, edge1);

			/* calculate V parameter and test bounds */
			out.z = DOT((*direction), qvec);
			if (out.z > 0.0 || out.y + out.z < det)
				return 0;
		} else return 0;  /* ray is parallell to the plane of the triangle */

		/* calculate t, ray intersects triangle */
		terrainops::cursor_output[0] = DOT(edge2, qvec) * inv_det;
		terrainops::cursor_output[1] = out.y * inv_det;
		terrainops::cursor_output[2] = out.z * inv_det;

		return 1;
	}
}

#endif