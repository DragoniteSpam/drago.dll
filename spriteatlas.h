namespace sprite_atlas {
	void pack_atlas(short* sprite_data, int length, short padding);
	bool place_sprite(short* sprite_data, int length, int index, short maxx, short maxy);
	bool collide_sprite(short* sprite_data, int length, int index, short x, short y);
}