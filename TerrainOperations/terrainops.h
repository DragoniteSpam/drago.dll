#ifndef __DRAGO_TERRAIN_OP
#define __DRAGO_TERRAIN_OP "1.0.2"

#include "main/core.h"
#include "SpriteOperations/spriteops.h"
#include <cmath>
#include <sstream>
#include <format>

#include <iostream>

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
	void build_settings(bool, bool, bool, bool, int, float, float, float, unsigned int, float);
	void build_texture(unsigned int*);
	void build_vertex_colour(unsigned int*);
	void build_bounds(int, int, int, int);
	void build(float*, std::stringstream*, long long*, int*, void(float*, std::stringstream*, unsigned int, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float));
	void build_obj(float*, std::stringstream*, long long*, int*);
	void generate_internal(float*);
	void generate_lod_internal(float*);

	void build_write_vertex_vbuff(float*, std::stringstream*, unsigned int, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float);
	void build_write_vertex_d3d(float*, std::stringstream*, unsigned int, long long*, float, float, float, float, float, float, float, float, unsigned int, float, float, float, float, float, float, float, float, float);

	void build_setup_vbuff(float*);
	void build_cleanup_vbuff(float*, long long*, int);
	void build_setup_d3d(float*, std::stringstream*);
	void build_cleanup_d3d(float*, std::stringstream*, long long*, int);
	void build_setup_obj(float*, std::stringstream*);
	void build_cleanup_obj(float*, std::stringstream*, long long*, int);

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

	inline void get_normal_smooth(float* data, TerrainCell* results, int x, int y, int originx, int originy, int corner, int w, int h) {
		Vector3 norm00{ }, norm10{ }, norm01{ }, norm11{ };

		Triangle ta{ }, tb{ }, tc{ }, td{ }, te{ }, tf{ }, tg{ }, th{ }, ti{ }, tj{ }, tk{ }, tl{ }, tm{ }, tn{ }, tone{ }, ttwo{ };
		if (originx > 0) {
			tn.a.a = originx - 1;
			tn.a.b = originy;
			tn.b.a = originx;
			tn.b.b = originy + 1;
			tn.c.a = originx - 1;
			tn.c.b = originy + 1;

			ta.a.a = originx - 1;
			ta.a.b = originy;
			ta.b.a = originx;
			ta.b.b = originy;
			ta.c.a = originx;
			ta.c.b = originy + 1;
		}

		if (originx > 0 && originy > 0) {
			tb.a.a = originx - 1;
			tb.a.b = originy - 1;
			tb.b.a = originx;
			tb.b.b = originy;
			tb.c.a = originx - 1;
			tb.c.b = originy;

			tc.a.a = originx - 1;
			tc.a.b = originy - 1;
			tc.b.a = originx;
			tc.b.b = originy - 1;
			tc.c.a = originx;
			tc.c.b = originy;
		}

		if (originy > 0) {
			td.a.a = originx;
			td.a.b = originy - 1;
			td.b.a = originx + 1;
			td.b.b = originy;
			td.c.a = originx;
			td.c.b = originy;

			te.a.a = originx;
			te.a.b = originy - 1;
			te.b.a = originx + 1;
			te.b.b = originy - 1;
			te.c.a = originx + 1;
			te.c.b = originy;
		}

		if (originx < w - 1 && y > 0) {
			tf.a.a = originx + 1;
			tf.a.b = originy - 1;
			tf.b.a = originx + 2;
			tf.b.b = originy;
			tf.c.a = originx + 1;
			tf.c.b = originy;
		}

		if (originx < w - 1) {
			tg.a.a = originx + 1;
			tg.a.b = originy;
			tg.b.a = originx + 2;
			tg.b.b = originy;
			tg.c.a = originx + 2;
			tg.c.b = originy + 1;

			th.a.a = originx + 1;
			th.a.b = originy;
			th.b.a = originx + 2;
			th.b.b = originy + 1;
			th.c.a = originx + 1;
			th.c.b = originy + 1;
		}

		if (originx < w - 1 && originy < h - 1) {
			ti.a.a = originx + 1;
			ti.a.b = originy + 1;
			ti.b.a = originx + 2;
			ti.b.b = originy + 1;
			ti.c.a = originx + 2;
			ti.c.b = originy + 2;

			tj.a.a = originx + 1;
			tj.a.b = originy + 1;
			tj.b.a = originx + 2;
			tj.b.b = originy + 2;
			tj.c.a = originx + 1;
			tj.c.b = originy + 2;
		}

		if (originy < h - 1) {
			tk.a.a = originx;
			tk.a.b = originy + 1;
			tk.b.a = originx + 1;
			tk.b.b = originy + 1;
			tk.c.a = originx + 1;
			tk.c.b = originy + 2;

			tl.a.a = originx;
			tl.a.b = originy + 1;
			tl.b.a = originx + 1;
			tl.b.b = originy + 2;
			tl.c.a = originx;
			tl.c.b = originy + 2;
		}

		if (originx > 0 && originy < h - 1) {
			tm.a.a = originx;
			tm.a.b = originy + 2;
			tm.b.a = originx - 1;
			tm.b.b = originy + 1;
			tm.c.a = originx;
			tm.c.b = originy + 1;
		}

		tone.a.a = originx;
		tone.a.b = originy;
		tone.b.a = originx + 1;
		tone.b.b = originy;
		tone.c.a = originx + 1;
		tone.c.b = originy + 1;

		ttwo.a.a = originx + 1;
		ttwo.a.b = originy + 1;
		ttwo.b.a = originx;
		ttwo.b.b = originy + 1;
		ttwo.c.a = originx;
		ttwo.c.b = originy;

		// northwest
		if (originx > 0) append_triangle_normal(data, &norm00, ta, w, h);
		if (originx > 0 && originy > 0) append_triangle_normal(data, &norm00, tb, w, h);
		if (originx > 0 && originy > 0) append_triangle_normal(data, &norm00, tc, w, h);
		if (originy > 0) append_triangle_normal(data, &norm00, td, w, h);
		append_triangle_normal(data, &norm00, tone, w, h);
		append_triangle_normal(data, &norm00, ttwo, w, h);

		// northeast
		if (originy > 0) append_triangle_normal(data, &norm10, td, w, h);
		if (originy > 0) append_triangle_normal(data, &norm10, te, w, h);
		if (originx < w - 1 && y > 0) append_triangle_normal(data, &norm10, tf, w, h);
		if (originx < w - 1) append_triangle_normal(data, &norm10, tg, w, h);
		if (originx < w - 1) append_triangle_normal(data, &norm10, th, w, h);
		append_triangle_normal(data, &norm10, tone, w, h);
		
		// southeast
		if (originx < w - 1) append_triangle_normal(data, &norm11, th, w, h);
		if (originx < w - 1 && originy < h - 1) append_triangle_normal(data, &norm11, ti, w, h);
		if (originx < w - 1 && originy < h - 1) append_triangle_normal(data, &norm11, tj, w, h);
		if (originy < h - 1) append_triangle_normal(data, &norm11, tk, w, h);
		append_triangle_normal(data, &norm11, tone, w, h);
		append_triangle_normal(data, &norm11, ttwo, w, h);
		
		// southwest
		if (originy < h - 1) append_triangle_normal(data, &norm01, tk, w, h);
		if (originy < h - 1) append_triangle_normal(data, &norm01, tl, w, h);
		if (originx > 0 && originy < h - 1) append_triangle_normal(data, &norm01, tm, w, h);
		if (originx > 0) append_triangle_normal(data, &norm01, tn, w, h);
		if (originx > 0) append_triangle_normal(data, &norm01, ta, w, h);
		append_triangle_normal(data, &norm01, ttwo, w, h);

		NORMALIZE(norm00);
		NORMALIZE(norm10);
		NORMALIZE(norm11);
		NORMALIZE(norm01);

		results->nw.x = norm00.x;
		results->nw.y = norm00.y;
		results->nw.z = norm00.z;

		results->ne.x = norm10.x;
		results->ne.y = norm10.y;
		results->ne.z = norm10.z;

		results->se.x = norm11.x;
		results->se.y = norm11.y;
		results->se.z = norm11.z;

		results->sw.x = norm01.x;
		results->sw.y = norm01.y;
		results->sw.z = norm01.z;
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