namespace sprite_atlas {
	int pack_atlas(int* sprite_data, int length, int padding);
	bool place_sprite(int* sprite_data, int length, int index, int maxx, int maxy);
	bool collide_sprite(int* sprite_data, int length, int index, int x, int y);
}